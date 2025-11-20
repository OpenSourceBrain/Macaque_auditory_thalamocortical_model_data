# RE Cell / NeuroML Export – Guidelines and Workflow

This document collects design decisions and “fixes” that must be enforced when exporting mechanisms to NeuroML and back to NMODL, with a focus on:

- RE-cell mechanisms (especially HH2 and `cadad`–type calcium pumps), and  
- IT2-cell mechanisms (e.g. `nax`, `kap`).

The emphasis is on **per–ion-channel numerical equivalence** between:

- original hand-written NEURON NMODL mechanisms, and  
- NeuroML–generated NMODL code.

All recommendations below are based on explicit code comparison (original `.mod` vs exported `.mod` vs compiled C++) and on quantitative waveform comparisons.

---

## 1. Logic that must be enforced in the exporter

### 1.1 HH2 / hh2\_na / hh2\_k

#### 1.1.1 Time–step alignment: gate multipliers must use \(t_{n+1}\)

As detailed in `REASON.md`, the key point for HH2–style mechanisms is **when** the “gate multipliers” (e.g. `m_fcond`, `h_fcond`, `n_fcond`) are updated.

- **Correct pattern (e.g. `HH2_magic`)**
  - In NMODL:
    ```nmodl
    BREAKPOINT {
        SOLVE states METHOD cnexp
        m_fcond = f(m)
        h_fcond = f(h)
        n_fcond = f(n)
        i = gbar * m_fcond * h_fcond * n_fcond * (v - erev)
    }
    ```
  - The `states` block is integrated first (`cnexp`), giving updated gating variables at time \(t_{n+1}\).  
    The multipliers are then computed from these updated states and used immediately to compute current.  
    Currents therefore depend on **\(t_{n+1}\) gates**, which matches the usual semi–implicit scheme.

- **Incorrect pattern (e.g. `HH2_reason`)**
  - In NMODL:
    ```nmodl
    DERIVATIVE states {
        rates(v)
        m' = ...
        h' = ...
        n' = ...
    }

    PROCEDURE rates(v) {
        m_fcond = f(m)
        h_fcond = f(h)
        n_fcond = f(n)
        ...
    }
    ```
  - Here, `m_fcond/h_fcond/n_fcond` are updated **before** integrating the states.  
    The current computed in `BREAKPOINT` then uses multipliers evaluated from **\(t_n\) gates**, while the ODE step advances gates to \(t_{n+1}\).  
    This introduces a systematic one–step delay in the gate multipliers.

**Exporter requirement**

For all HH2–like channels (Na, K, Ca, etc.):

- Do **not** update gate multipliers inside `rates()` or inside the `DERIVATIVE` block.
- Always follow this pattern:
  1. In `DERIVATIVE` (or `states`): update only the gating states with:
     ```nmodl
     x' = (x_inf - x) / x_tau
     ```
  2. In `BREAKPOINT`, after `SOLVE states METHOD cnexp`, recompute gating multipliers from the updated states and then compute current.

This guarantees that the exported mechanisms use the same temporal alignment as the original HH2 implementations.

#### 1.1.2 Ensuring `cnexp` recognition: avoid intermediate `rate_*_q`

The original NeuroML exports often used intermediate “rate” variables, e.g.:

```nmodl
rate_m_q = (m_inf - m_q) / m_tau
m_q' = rate_m_q
```

This prevents NEURON from recognizing the ODE as the canonical linear form required for `METHOD cnexp`, and can force a fallback to Euler integration.

For HH2–like gates the desired form is:

```nmodl
DERIVATIVE states {
    m_q' = (m_inf - m_q) / m_tau
    h_q' = (h_inf - h_q) / h_tau
    n_q' = (n_inf - n_q) / n_tau
}
```

**Exporter requirement**

- For any first–order gate whose dynamics are of the form “exponential relaxation to steady state,” the exporter must emit:
  ```nmodl
  x_q' = (x_inf - x_q) / x_tau
  ```
  directly, with no intermediate `rate_x_q`.
- This ensures NEURON can apply the `cnexp` method, preserving numerical equivalence with hand–written HH mechanisms.

#### 1.1.3 Combined HH2 vs split Na/K channels

The current workflow for RE cells compares:

- a combined HH2 channel (`HH2.mod`, e.g. `hh2ad`), and  
.- its split counterparts (`hh2_na` + `hh2_k`).

**Exporter requirement**

If NeuroML needs to support both formulations simultaneously, gate updates and gate multipliers must be implemented with **identical numerical semantics** in both versions:

- Same ODE form `(x_inf - x)/tau`,  
- Same use of `cnexp`, and  
- Same “multipliers are computed after `SOLVE`” rule.

---

### 1.2 `cadad` / `cadad_RE_soma_nml` (calcium pump–like mechanisms)

#### 1.2.1 ODE equivalence

`REASON.md` shows that the ODEs for `dcai/dt` in:

- the original `cadad.mod`, and  
- the NeuroML–generated `cadad_RE_soma_nml.mod`

are numerically equivalent once:

- `ica` is correctly mapped to `currDensCa`, and  
- unit conversions (`depth`, Faraday, etc.) are applied consistently.

The remaining differences are at the \(\sim10^{-8}\) relative level and are not physiologically relevant.  
Therefore, the **ODE form and units are not the source of the discrepancy**.

#### 1.2.2 Key difference: initial `cai` at \(t=0\)

The actual discrepancy comes from how the two mechanisms handle calcium concentration at initialization.

- In the original `cadad.mod` (see `x86_64/cadad.cpp`):
  1. `nrn_init` first reads `seg.cai` into internal state.
  2. In `INITIAL { cai = cainf }`, the mechanism **overwrites** that value.
  3. The new `cai` is then written back to `ca_ion`.

  As a result, **the simulation always starts with `cai = cainf`**, regardless of any Python–side initialization of `seg.cai`.

- In the early NeuroML export `cadad_RE_soma_nml.mod`:
  - `INITIAL` only copies `cai/cao` into internal variables (`concentration/extConcentration`) and **does not reset `cai`** to `cainf`.
  - In an RE full–cell simulation, this means:
    - NEURON native + `cadad` starts from `cai = cainf`.  
    - NML–fix + `cadad_RE_soma_nml` starts from whatever the Python code set (e.g. `5e-5`), producing systematic differences in both Ca and voltage trajectories.

#### 1.2.3 Fix and exporter requirement

Current patch (documented in `REASON.md`):

- In `cadad_RE_soma_nml.mod`, `INITIAL` is modified to:
  1. Explicitly set `cai = cainf` (and the analogous behavior for `cao` if needed).
  2. Then initialize internal state from this reset value.

**Exporter requirement**

For “Destexhe pump–style” Ca concentration mechanisms:

- Automatically generate an `INITIAL` block that:
  - sets `cai` (and `cao`, if relevant) to the mechanism’s steady–state value (e.g. `cainf`), and  
  - reflects these values in internal state variables.
- Ensure that the **ordering of reads/writes to `cai`** matches the original mechanism (read, overwrite with `cainf`, write back).

---

### 1.3 General export rules (RE mechanisms)

#### 1.3.1 Gate variables

For any gate (Na, K, Ca, etc.):

- Represent the state as a dimensionless variable `x_q` (or equivalent).
- In `INITIAL`: set `x_q = x_inf` evaluated at the initial membrane potential.
- In `DERIVATIVE` or `states`:
  ```nmodl
  x_q' = (x_inf - x_q) / x_tau
  ```
  and use `SOLVE states METHOD cnexp`.
- All Q10, forward rates, reverse rates, steady–state curves, and time courses should be computed in `rates()`.  
  **`rates()` must not update gate multipliers or conductances directly.**

#### 1.3.2 Conductance and current

In `BREAKPOINT`:

1. Call `SOLVE states METHOD cnexp`.
2. Compute gate multipliers (e.g. `m_fcond`, `h_fcond`, `n_fcond`) from the updated gates.
3. Compute `fopen`, `g`, `gion`, and then current:
   ```nmodl
   fopen = product_of_gate_fconds
   gion  = gmax * fopen      : or density-scaled variant
   i     = gion * (v - erev) : or ik/ina/ica depending on ion
   ```

Some NeuroML exports emit both ion currents and an auxiliary current with opposite sign, e.g.:

```nmodl
ina    : current added to Na ion
i__hh2_na = -1 * ina
```

This is acceptable as long as all comparisons use the same convention.  
In this repository, the comparison scripts operate on membrane voltage, so the internal sign conventions are already implicit in the dynamics.

#### 1.3.3 Ion concentration mechanisms

If a mechanism:

- has a `STATE` that represents a concentration (e.g. `cai`), and  
- uses `USEION ca READ cai WRITE cai`,

then:

- The ODE for the state must be derived consistently from the ionic current, including all geometry and Faraday constants.
- `INITIAL` must explicitly define the starting concentration (either from a parameter or from the ion mechanism), and any writes back to the ion pool (`WRITE cai`) must follow the same order as in the original mechanism.

---

## 2. Verification strategy

### 2.1 Single–channel verification (per mechanism)

For each channel mechanism (HH2, Na, K, Ca, pumps, etc.), the workflow is:

1. **Prepare single–channel test scripts**
   - For RE: place the channel on a simple test geometry (typically a reduced morphology or a single compartment), with:
     - only this mechanism + passive leak,  
     - standard temperature (e.g. 34 °C), and  
     - a simple current clamp.
   - For IT2: use the existing `run_neuron_*_native.py` / `run_neuron_*_nml.py` scripts (see Section 5 and 6).

2. **Run NEURON native vs NeuroML–exported mechanisms**
   - Simulations:
     - native `.mod` only,  
     - NeuroML–exported `.mod` only.
   - Use identical geometry, passive parameters, reversal potentials, and clamp waveforms.

3. **Compare waveforms quantitatively**
   - Post–process the two traces:
     - align in time,  
     - compute `ΔV(t) = V_native(t) - V_nml(t)`,  
     - report `max |ΔV|`, mean `ΔV`, and possibly the correlation between `V_native` and `ΔV`.
   - Inspect the difference trace:
     - If `ΔV` shows systematic time shifts (e.g. changes sign around spikes in a way that suggests phase lag), suspect gate multiplier timing issues.
     - If `ΔV` is essentially flat at the \(10^{-5}\)–\(10^{-4}\) mV level, differences are within double-precision rounding noise.

4. **Acceptance criterion**
   - A channel is considered numerically matched when the single–channel test yields:
     - `max |ΔV|` on the order of \(10^{-4}\) mV or smaller, and  
     - no systematic bias in spike timing or amplitude beyond that level.

### 2.2 Layered integration for RE cell

Once per–channel equivalence is obtained, integrate mechanisms stepwise into the RE cell model:

1. **Step 0: passive leak only (already done)**
   - Use `./auto_compare.sh --pas-nrn`.  
   - Confirm that NEURON vs NeuroML leak–only models agree (current result: `diff ≈ 0`, considered a pass).

2. **Step 1: HH2 only**
   - Use `./auto_compare.sh --hh2-hh2ad-vs-split`:  
     - Compare `HH2.mod` (combined) vs `hh2_na + hh2_k` (split) on a reduced HH2–only RE cell.
     - If there is any noticeable timing shift or extra spikes, go back to single–channel HH2 analysis and fix the export.

3. **Step 2: RE full cell without `cadad`**
   - Disable `cadad` in the Python scripts (use `run_neuron_full_noCadad.py` / `run_neuron_full_nml_fix_noCadad.py`), leaving only:
     - passive leak,  
     - HH2, and  
     - other voltage–gated channels (e.g. IT2, `kl`, etc.).
   - Run: `./auto_compare.sh --re-nml-fix-vs-nrn-noCadad`.  
   - If differences are still non–negligible, some non–HH2 channel has not yet been aligned and must be revisited at the single–channel level.

4. **Step 3: RE full cell with `cadad`**
   - Re–enable `cadad`, using the corrected `cadad_RE_soma_nml.mod` (with `cai = cainf` in `INITIAL`).
   - Run: `./auto_compare.sh --re-nml-fix-vs-nrn`.  
   - Verify that full–cell voltage traces for NML–fix vs NEURON native converge to numerical–error levels.

5. **Step 4: Cross–validation with NetPyNE (optional but recommended)**
   - Once RE cell NML–fix vs NEURON native are aligned, compare against the NetPyNE implementation:
     - `./auto_compare.sh --re-nml-fix-vs-netpyne`  
     - `./auto_compare.sh --re-native-vs-netpyne`
   - If both NEURON native and NML–fix match closely at the full–cell level, any remaining differences with NetPyNE are more likely due to NetPyNE–specific modeling choices rather than NeuroML export.

---

## 3. Suggested development order (per ion channel)

To keep the debugging surface manageable, channels should be handled one at a time.

1. **Select a channel**  
   e.g. HH2 → IT2 Na/K → `kl` → Ca channels → pumps.

2. **Analyze the original `.mod`**
   - Identify gate ODE form and integration method (`cnexp` vs others).
   - Determine where gate multipliers are computed.
   - Check whether the mechanism reads/writes ion concentrations and how `INITIAL` behaves.

3. **Analyze the current NeuroML–generated `.mod`**
   - Look for `rate_*_q` intermediates that might prevent `cnexp` recognition.
   - Check if gate multipliers are updated in `rates()` instead of `BREAKPOINT`.
   - Confirm that `INITIAL` matches the original mechanism’s behavior (e.g., resetting `cai`).

4. **Modify export logic (or hand–patch NML–fix)**
   - Apply the rules in Sections 1.1–1.3 to bring the exported mechanism into strict numerical alignment with the original.

5. **Run single–channel verification**
   - Use the appropriate `run_neuron_*_native.py` / `run_neuron_*_nml.py` pair and the comparison script to confirm per–channel alignment.

6. **Integrate into the full cell**
   - Once a channel passes single–channel tests, add it to the RE cell and repeat the layered checks in Section 2.2.

7. **Only after a channel is confirmed at the full–cell level, move on to the next channel.**
   - Avoid modifying multiple channels simultaneously, as this makes attribution of differences difficult.

> In short: **first guarantee NEURON vs NeuroML numerical equivalence at the single–channel level, then progressively integrate channels into the full cell.** The passive leak has already been validated; all other ion channels should be treated individually following this procedure.

---

## 4. IT2: `nax_nml` vs `nax_BS` – consistency fix

### 4.1 Observed behavior

Location: `IT2` directory.

- Native mechanism: `nax_BS.mod` (`SUFFIX nax`)  
- NeuroML export: `nax_nml.mod` (`SUFFIX nax_nml`)

Test scripts:

- `IT2/run_neuron_nax_native.py` (native `nax` only)  
- `IT2/run_neuron_nax_nml.py` (NML `nax_nml` only)  
- `IT2/compare/compare_nax_native_vs_nml.py` (compares `NEURON_nax_native.json` vs `NEURON_nax_nml.json`)

Before the fix:

- Voltage traces were very similar but exhibited a systematic deviation around spike peaks, with:
  - `max |ΔV| ≈ 1.1 mV`.
- All gating parameters, Q10 settings, conductance density (`gbar` vs `gmax`), and reversal potential (`erev = 42 mV`) had already been checked and matched.
  - Therefore the discrepancy was not due to parameter or unit mismatch but arose from differences in implementation.

### 4.2 Root cause: ordering inside `nax_nml` `rates()`

In the original `nax_BS.mod`, the `PROCEDURE trates(vm, sh2)`:

- For a given voltage `vm`, computes rates `a` and `b` and then **consistently** updates:
  - `mtau = 1/(a+b)/qt`, `minf = a/(a+b)`  
  - `htau = 1/(a+b)/qt`, `hinf = ...`

At each time step, `tau` and `inf` are computed from the **same** underlying rates.

In the early `nax_nml.mod` export, the `PROCEDURE rates()` used a different sequence (simplified):

1. Compute `m_forwardRate_r` and `m_reverseRate_r` from the current voltage.
2. Use **old** `m_alpha/m_beta` to compute `m_timeCourse_*` and `m_timeCourse_t`.
3. Only then update:
   - `m_alpha = m_forwardRate_r`  
   - `m_beta  = m_reverseRate_r`  
   - `m_inf   = m_alpha/(m_alpha + m_beta)`  
   - `m_tauUnscaled = m_timeCourse_t / m_rateScale` → `m_tau`.

The h gate had the same structure.  
This meant:

- `m_inf/h_inf` were computed from **current** rates,  
- while `m_tau/h_tau` were computed from a `timeCourse` based on **previous** rates.

Numerically, this is equivalent to a small “off–by–one” time–step mismatch between `inf` and `tau`, which amplifies into a ~1 mV systematic difference at the IT2 morphology level.

### 4.3 Fix: reordering `nax_nml.mod` `rates()`

In `IT2/mod/nax_nml.mod`, `PROCEDURE rates()` was reordered.

For the m gate:

- **Before** (logical order):
  1. Compute `m_forwardRate_r`, `m_reverseRate_r`.  
  2. Use old `m_alpha/m_beta` to compute `m_timeCourse_*` → `m_timeCourse_t`.  
  3. Update `m_alpha/m_beta`, then compute `m_inf` and `m_tau`.

- **After** (correct order):
  1. Compute `m_forwardRate_r`, `m_reverseRate_r`.  
  2. Immediately set:
     ```nmodl
     m_alpha = m_forwardRate_r
     m_beta  = m_reverseRate_r
     ```
  3. Use these updated `m_alpha/m_beta` to compute:
     - time course (including any minimum enforcement) → `m_timeCourse_t`,  
     - steady state `m_inf`,  
     - and `m_tauUnscaled = m_timeCourse_t / m_rateScale`, followed by any `mmin` enforcement.

The same reordering was applied to the h gate.

Additionally, some `trap0`–style conditional branches were updated to use inclusive comparisons (`<=`, `>=`) to better match the behavior of the original `fabs(v-th) > 1e-6` logic.  
These boundary tweaks have negligible impact on the waveform but improve exact consistency.

### 4.4 Post–fix validation

After modifying `nax_nml.mod`:

1. Recompile mechanisms: `nrnivmodl mod` in `IT2/`.  
2. Rerun:
   - `python3 run_neuron_nax_native.py`  
   - `python3 run_neuron_nax_nml.py`  
   - `python3 compare/compare_nax_native_vs_nml.py`.

Result (user–side verification):

- The `nax` and `nax_nml` membrane voltage traces are now indistinguishable at plotting resolution, with:
  - `max |ΔV|` reduced to numerical–noise levels (`“completely identical”` in practice).

Therefore the discrepancy was indeed caused by the `rates()` ordering, not by floating–point roundoff or parameter mismatch.

### 4.5 Exporter requirement for HHtauInf–style gates

For any gate reconstructed as a `gateHHtauInf`–like structure from a legacy HH mechanism (e.g. IT2 `nax`):

- The exported `rates()` must:
  1. compute forward and reverse rates,  
  2. update `alpha/beta` immediately, and  
  3. only then compute time course and steady state (`tau/inf`) from these updated rates.

This rule ensures that future exports of `nax`–like channels are numerically equivalent to the original HH mechanisms and that NEURON vs NeuroML comparisons converge to floating–point noise.

---

## 5. IT2: `kap_nml` vs `kap_BS` – consistency fix

### 5.1 n gate `taun`: Q10 and minimum enforcement

In the native `kap_BS.mod` (see `IT2/mod/kap_BS.mod`), the n gate time constant is:

```nmodl
qt   = q10^((celsius-24)/10)
taun = betn(v) / (qt*a0n*(1+a))
if (taun < nmin) {
    taun = nmin
}
```

Thus the minimum `nmin` is applied **after** Q10 scaling.

In the original NeuroML export `kap_nml.mod`, the n–gate logic comprised:

1. `n_timeCourse_t` (a base time constant) computed from voltage and parameters, including one min operation inside the `timeCourse` component.
2. `n_tau = n_timeCourse_t / n_rateScale`, where `n_rateScale = n_q10Settings_q10` represents Q10 scaling.

This corresponds to applying a minimum **before** Q10 scaling and then dividing by Q10, which can effectively reduce the minimum time constant to `nmin/q10`.  
This behavior is not equivalent to `kap_BS.mod` when Q10 > 1.

### 5.2 Fix in `kap_nml.mod`

In `IT2/mod/kap_nml.mod`, inside `PROCEDURE rates()` for n:

- The logic was changed from:

  ```nmodl
  n_tauUnscaled = n_timeCourse_t
  n_tau = n_tauUnscaled / n_rateScale
  ```

- to:

  ```nmodl
  n_tauUnscaled = n_timeCourse_t

  ? Apply Q10 scaling first, then enforce minimum, to match kap_BS.mod semantics:
  ? original: taun = betn(v)/(qt*a0n*(1+a)); if (taun < nmin) { taun = nmin }
  n_tauUnscaled = n_tauUnscaled / n_rateScale
  if (n_tauUnscaled < n_timeCourse_nmin) {
      n_tauUnscaled = n_timeCourse_nmin
  }
  n_tau = n_tauUnscaled
  ```

Given:

- `n_timeCourse_t` encodes the base time constant (already including any internal minimum applied by the timeCourse component), and  
- `n_rateScale` corresponds to `qt`,

this ensures that:

```text
taun = max( base_tau / qt, nmin )
```

which matches the original `kap_BS.mod` behavior.

### 5.3 l gate logic

For the l gate, `kap_BS.mod` defines:

```nmodl
taul = 0.26*(v+50-sh)/qtl
if (taul < lmin/qtl) {
    taul = lmin/qtl
}
```

The export `kap_nml.mod` encodes this as:

```nmodl
if (0.26*(V+50-sh)*TIME_SCALE < l_timeCourse_lmin) {
    l_timeCourse_t = l_timeCourse_lmin
} else {
    l_timeCourse_t = 0.26*(V+50-sh)*TIME_SCALE
}

l_q10Settings_q10Factor = 1   ; no Q10 for l gate
l_tauUnscaled = l_timeCourse_t
l_tau = l_tauUnscaled / l_rateScale   ; l_rateScale = 1
```

Thus, for l:

```text
l_tau = max( 0.26*(v+50-sh)/qtl, lmin/qtl )
```

which is already consistent with the original mechanism; no additional changes were required beyond documenting the intentional choice `l_q10Settings_q10Factor = 1`.

### 5.4 Post–fix validation

After adjusting the n–gate Q10/minimum ordering:

1. Recompile the mechanisms: `nrnivmodl mod`.  
2. Run:
   - `python3 run_neuron_kap_native.py`  
   - `python3 run_neuron_kap_nml.py`  
   - `python3 compare/compare_kap_native_vs_nml.py`.

Observed statistics:

- `max |ΔV| ≈ 4×10⁻⁵ mV`  
- `mean ΔV ≈ 2×10⁻⁵ mV`

The difference trace exhibits structure (because it is a deterministic roundoff effect in a nonlinear system), but its amplitude is deep in the double–precision noise regime.  
This is consistent with the two implementations being numerically equivalent modulo floating–point evaluation order.

### 5.5 Exporter requirement

For channels of the `gateHHtauInf` type (such as IT2 `kap`):

- Q10 scaling must be applied in the same order as in the original mechanism:
  - Compute a base `tau` (including any local minimum enforcement),  
  - divide by Q10,  
  - then compare to the global minimum `nmin`/`lmin`.
- Any timeCourse/steadyState decomposition introduced by NeuroML must be combined such that the final `(x_inf, x_tau)` pair matches the original HH implementation at each time step.

Implementing these constraints at the exporter level ensures that future exports of `kap`–like mechanisms match their original NMODL counterparts to within floating–point error.

