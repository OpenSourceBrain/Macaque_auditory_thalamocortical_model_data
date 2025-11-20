# Difference Between Gate Multipliers in HH2_magic and HH2_reason

This note compares `HH2_magic` and `HH2_reason` with respect to **when the gate multipliers `m_fcond / h_fcond / n_fcond` are updated**, and shows the corresponding auto-generated C++ code and the time-stepping order.  

We use the following notation:

- Gating variables: `m(t), h(t), n(t)`  
- Gate multipliers:  
  - `m_fcond(t) = m(t)^3`  
  - `h_fcond(t) = h(t)`  
  - `n_fcond(t) = n(t)^4`  
- Sodium and potassium currents:  
  - `inahh2(t) = gnabar * m_fcond(t) * h_fcond(t) * (v(t) - ena)`  
  - `ikhh2(t)  = gkbar  * n_fcond(t)             * (v(t) - ek)`

Key question: in a discrete time step `t_n → t_{n+1}`, at which time point (`t_n` or `t_{n+1}`) are `m_fcond / h_fcond / n_fcond` computed from `m,h,n`?

---

## 1. MOD-Level Comparison

### 1.1 HH2_magic.mod (gate multipliers computed in BREAKPOINT)

Key fragment (simplified):

```nmodl
BREAKPOINT {
  SOLVE state METHOD cnexp

  : gate fcond factors (similar to HH2_nondiff style)
  m_fcond = m*m*m
  h_fcond = h
  n_fcond = n*n*n*n

  : Use precomputed fcond factors (set in evaluate_fct)
  inahh2 = gnabar * m_fcond * h_fcond * (v - ena)
  ikhh2  = gkbar * n_fcond * (v - ek)
  ina =   inahh2
  ik  =    ikhh2
}

DERIVATIVE state {
  evaluate_fct(v)
  m' = (m_inf - m) / tau_m
  h' = (h_inf - h) / tau_h
  n' = (n_inf - n) / tau_n
}

PROCEDURE evaluate_fct(v(mV)) {
  ...
  tau_m, tau_h, tau_n, m_inf, h_inf, n_inf, m_exp, h_exp, n_exp
  are computed from v
  ...
}
```

Properties:

- In `BREAKPOINT`, after `state` has updated `m,h,n`, the code **immediately recomputes `m_fcond, h_fcond, n_fcond` from the updated `m,h,n`**.
- `evaluate_fct` only computes time constants and steady-state values from `v`, and does not touch `m_fcond / h_fcond / n_fcond`.

### 1.2 HH2_reason.mod (gate multipliers computed in evaluate_fct)

Key fragment:

```nmodl
BREAKPOINT {
  SOLVE state METHOD cnexp

  : Use precomputed fcond factors (set in evaluate_fct)
  inahh2 = gnabar * m_fcond * h_fcond * (v - ena)
  ikhh2  = gkbar * n_fcond * (v - ek)
  ina =   inahh2
  ik  =    ikhh2
}

DERIVATIVE state {
  evaluate_fct(v)
  m' = (m_inf - m) / tau_m
  h' = (h_inf - h) / tau_h
  n' = (n_inf - n) / tau_n
}

PROCEDURE evaluate_fct(v(mV)) {
  ...
  tau_m, tau_h, tau_n, m_inf, h_inf, n_inf, m_exp, h_exp, n_exp
  are computed from v
  ...
  m_exp = 1 - Exp(-dt/tau_m)
  h_exp = 1 - Exp(-dt/tau_h)
  n_exp = 1 - Exp(-dt/tau_n)

  : gate fcond factors (similar to HH2_nondiff style)
  m_fcond = m*m*m
  h_fcond = h
  n_fcond = n*n*n*n
}
```

Properties:

- `BREAKPOINT` no longer updates `m_fcond / h_fcond / n_fcond`; it only uses them.  
- `evaluate_fct(v)` computes `tau_*` and `*_inf` and then **updates the gate multipliers from the current `m,h,n`**.

---

## 2. Time Ordering in the Auto-Generated C++ Code

Assume fixed time step and `cnexp` method. For one step `t_n → t_{n+1}`:

- `m_n = m(t_n), m_{n+1} = m(t_{n+1})`  
- `v_n = v(t_n)` (voltage is determined by solving the cable equation; here we focus only on `m,h,n` vs gate multipliers).

### 2.1 Call Order in HH2_magic.cpp

Key functions (irrelevant parts omitted):

```cpp
// state: call evaluate_fct(v) first, then update m,h,n with cnexp
static int state (_internalthreadargsproto_) { {
  evaluate_fct ( _threadargscomma_ v ) ;
   m = m + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_m)))*(- ( ( ( m_inf ) ) / tau_m ) / ( ( ( ( - 1.0 ) ) ) / tau_m ) - m) ;
   h = h + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_h)))*(- ( ( ( h_inf ) ) / tau_h ) / ( ( ( ( - 1.0 ) ) ) / tau_h ) - h) ;
   n = n + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_n)))*(- ( ( ( n_inf ) ) / tau_n ) / ( ( ( ( - 1.0 ) ) ) / tau_n ) - n) ;
  }
 return 0;
}

// evaluate_fct: updates *_inf, tau_*, *_exp, but NOT m_fcond/h_fcond/n_fcond
static int  evaluate_fct ( _internalthreadargsprotocomma_ double _lv ) {
  ...
  tau_m = 1.0 / ( _la + _lb ) / tadj ;
  m_inf = _la / ( _la + _lb ) ;
  ...
  tau_h = ...
  h_inf = ...
  ...
  tau_n = ...
  n_inf = ...
  m_exp = 1.0 - Exp ( _threadargscomma_ - dt / tau_m ) ;
  h_exp = 1.0 - Exp ( _threadargscomma_ - dt / tau_h ) ;
  n_exp = 1.0 - Exp ( _threadargscomma_ - dt / tau_n ) ;
   return 0;
}

// _nrn_current: recompute gate multipliers from CURRENT m,h,n
static double _nrn_current(_internalthreadargsprotocomma_ double _v) {
double _current=0.; v=_v;
{ {
   m_fcond = m * m * m ;
   h_fcond = h ;
   n_fcond = n * n * n * n ;
   inahh2 = gnabar * m_fcond * h_fcond * ( v - ena ) ;
   ikhh2 = gkbar * n_fcond * ( v - ek ) ;
   ina = inahh2 ;
   ik = ikhh2 ;
   }
 _current += ina;
 _current += ik;

} return _current;
}
```

For `t_n → t_{n+1}`:

1. At the beginning of the step: `m = m_n`.  
2. Call `state()`:
   - `evaluate_fct(v_n)` computes `tau_m, tau_h, tau_n, m_inf, ...`; it does **not** touch `m_fcond / h_fcond / n_fcond`;
   - cnexp updates `m,h,n` to `m_{n+1}, h_{n+1}, n_{n+1}`.
3. Call `_nrn_current()`:
   - recompute the gate multipliers from **updated** `m_{n+1}, h_{n+1}, n_{n+1}`;
   - compute `inahh2, ikhh2` from these multipliers.

Conclusion: **in `HH2_magic`, the gate multipliers used in the current are aligned with `m,h,n` at time `t_{n+1}`.**

### 2.2 Call Order in HH2_reason.cpp

Key functions:

```cpp
// state: also calls evaluate_fct(v) first, then updates m,h,n
static int state (_internalthreadargsproto_) { {
  evaluate_fct ( _threadargscomma_ v ) ;
   m = m + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_m)))*(- ( ( ( m_inf ) ) / tau_m ) / ( ( ( ( - 1.0 ) ) ) / tau_m ) - m) ;
   h = h + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_h)))*(- ( ( ( h_inf ) ) / tau_h ) / ( ( ( ( - 1.0 ) ) ) / tau_h ) - h) ;
   n = n + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_n)))*(- ( ( ( n_inf ) ) / tau_n ) / ( ( ( ( - 1.0 ) ) ) / tau_n ) - n) ;
  }
 return 0;
}

// evaluate_fct: at the END, update gate multipliers from CURRENT m,h,n
static int  evaluate_fct ( _internalthreadargsprotocomma_ double _lv ) {
  ...
  tau_m = ...
  m_inf = ...
  ...
  tau_h = ...
  h_inf = ...
  ...
  tau_n = ...
  n_inf = ...
  m_exp = 1.0 - Exp ( _threadargscomma_ - dt / tau_m ) ;
  h_exp = 1.0 - Exp ( _threadargscomma_ - dt / tau_h ) ;
  n_exp = 1.0 - Exp ( _threadargscomma_ - dt / tau_n ) ;
  m_fcond = m * m * m ;
  h_fcond = h ;
  n_fcond = n * n * n * n ;
   return 0;
}

// _nrn_current: just uses the precomputed gate multipliers
static double _nrn_current(_internalthreadargsprotocomma_ double _v) {
double _current=0.; v=_v;
{ {
   inahh2 = gnabar * m_fcond * h_fcond * ( v - ena ) ;
   ikhh2 = gkbar * n_fcond * ( v - ek ) ;
   ina = inahh2 ;
   ik = ikhh2 ;
   }
 _current += ina;
 _current += ik;

} return _current;
}
```

For `t_n → t_{n+1}`:

1. At the beginning of the step: `m = m_n`.  
2. Call `state()`:
   - `evaluate_fct(v_n)`:
     - computes `tau_m, tau_h, tau_n, m_inf, ...` from `v_n`;
     - uses the **current** `m_n, h_n, n_n` to write `m_fcond, h_fcond, n_fcond`;
   - cnexp then updates `m,h,n` to `m_{n+1}, h_{n+1}, n_{n+1}`.
3. Call `_nrn_current()`:
   - uses the precomputed `m_fcond, h_fcond, n_fcond` from step 2;
   - at this moment `m,h,n` are already `m_{n+1}, h_{n+1}, n_{n+1}`, but the gate multipliers still correspond to `m_n, h_n, n_n`.

Conclusion: **in `HH2_reason`, the gate multipliers used in the current correspond to the gating state at time `t_n`, while `m,h,n` themselves have advanced to `t_{n+1}`. The gate multipliers lag one time step behind the gating variables.**

---

# Difference Between cadad and cadad_RE_soma_nml

This note compares the classic Destexhe-style Ca pump `cadad` (`mod/cadad.mod`) with the NeuroML-exported Ca concentration mechanism `cadad_RE_soma_nml` (`mod/cadad_RE_soma_nml.mod`), focusing on why the **NML-fix vs NRN native** runs diverged once `cadad` was included, and how we made the two behaviors match.

We use the following notation:

- Ionic Ca concentration used by NEURON: `cai(t)` (the `ca_ion` concentration)
- NML-exported internal state: `concentration(t)` (in `cadad_RE_soma_nml`)
- Ca current density: `ica(t)` (mA/cm²)
- Pump parameters: `cainf`, `taur`, `depth`, `Faraday`

Key question: **for the same `ica(t)` and parameters, and with fixed time step / `cnexp`, do `cadad` and `cadad_RE_soma_nml` integrate `cai(t)` in exactly the same way, including how `cai` is initialised at `t = 0`?**

---

## 1. MOD-Level Equations

### 1.1 `cadad.mod` (Destexhe pump)

Key fragment (simplified, see `mod/cadad.mod`):

```nmodl
NEURON {
  SUFFIX cadad
  USEION ca READ ica, cai WRITE cai
  RANGE depth, kt, kd, cainf, taur
}

CONSTANT {
  FARADAY = 96489 (coul)
}

PARAMETER {
  depth = 1 (um)
  taur  = 5 (ms)
  cainf = 2.4e-4 (mM)
  kt    = 0   (mM/ms)  : dummy
  kd    = 0   (mM)     : dummy
}

STATE {
  cai (mM)
}

INITIAL {
  cai = cainf
}

DERIVATIVE state {
  drive_channel = - (10000) * ica / (2 * FARADAY * depth)
  cai' = drive_channel + (cainf - cai)/taur
}
```

So, in continuous time:

\[
\frac{dcai}{dt} = - \frac{10000}{2 \cdot FARADAY \cdot depth} \, ica
                  + \frac{cainf - cai}{\tau_r}
\]

and at `t = 0`, `cai` is explicitly set to `cainf` (overwriting any earlier `seg.cai` assigned from Python).

### 1.2 `cadad_RE_soma_nml.mod` (NeuroML export)

Key fragment (simplified, see `mod/cadad_RE_soma_nml.mod`):

```nmodl
NEURON {
    SUFFIX cadad_RE_soma
    USEION ca READ cai, cao, ica WRITE cai VALENCE 2
    RANGE cai, cao
    GLOBAL initialConcentration, initialExtConcentration
    RANGE cainf, taur, depth, Faraday
    RANGE currDensCa
}

PARAMETER {
    surfaceArea (cm2)
    iCa (nA)
    initialConcentration (mM)
    initialExtConcentration (mM)

    cainf = 2.4E-4 (mM)
    taur  = 5     (ms)
    depth = 1.0E-4 (cm)
    Faraday = 9.6488997E10 (pC / umol)
}

ASSIGNED {
    cai (mM)
    cao (mM)
    ica (mA/cm2)
    currDensCa (nA / cm2)
}

STATE {
    concentration    (mM)
    extConcentration (mM)
}

INITIAL {
    cai = cainf               : ADDED to align with cadad.mod
    initialConcentration    = cai
    initialExtConcentration = cao
    rates()
    rates()                   : ensure internal variables initialised
    concentration    = initialConcentration
    extConcentration = initialExtConcentration
}

DERIVATIVE states {
    rates()
    concentration' = ( currDensCa /(2* Faraday * depth))
                     - ((concentration - cainf) / taur)
    cai = concentration
}

PROCEDURE rates() {
    surfaceArea = (1e-08) * area
    iCa         = (1e6) * (-1 * ica * surfaceArea)
    currDensCa  = iCa / surfaceArea    : = -1e6 * ica
}
```

Here the true ODE state is `concentration`; `cai` is an alias that is updated each step from `concentration`. The NeuroML exporter also uses explicit `area` and a different choice of units for `depth` and `Faraday`.

---

## 2. Are the ODEs Numerically Equivalent?

Ignoring initialisation for the moment, and substituting the definitions in `rates()`:

- `currDensCa = iCa / surfaceArea = -1e6 * ica` (since `surfaceArea` cancels out),
- so the NML ODE is:

\[
\frac{d\,concentration}{dt}
  = \frac{-10^6}{2 \cdot Faraday \cdot depth} \, ica
    + \frac{cainf - concentration}{\tau_r}
\]

Using the default parameter values from the NML-exported MOD:

- `Faraday = 9.6488997e10 (pC/umol)`
- `depth   = 1.0e-4 (cm)` ( = 1 µm)

the effective coefficient in front of `ica` is:

\[
k_{\text{NML}} = -\frac{10^6}{2 \cdot 9.6488997 \times 10^{10} \cdot 10^{-4}}
\]

For the original `cadad.mod` with:

- `FARADAY = 96489 (coul)`
- `depth   = 1 (um)`

the coefficient is:

\[
k_{\text{orig}} = -\frac{10000}{2 \cdot 96489 \cdot 1}
\]

Numerically (see quick check in the repo):

- `k_orig ≈ -0.0518193784`
- `k_NML ≈ -0.0518193800`
- `k_NML / k_orig ≈ 1.00000003`

So up to floating-point rounding, **both mechanisms implement the same continuous-time ODE for Ca concentration**, provided the parameters are set as in:

- `run_neuron_full.py` for `cadad` (depth = 1.0 (µm)),
- `run_neuron_full_nml_fix.py` for `cadad_RE_soma_nml` (depth = 1e-4 (cm), Faraday as above).

This means the source of the discrepancy is **not** a missing / extra factor of 10 or 10000 in the ODE itself.

---

## 3. The Real Difference: Initialisation of `cai` at t = 0

### 3.1 `cadad.mod` initialisation

For `cadad.mod` (see `x86_64/cadad.cpp`), the generated `nrn_init` does roughly:

1. Read the existing ionic Ca concentration into the mechanism:
   - `cai = _ion_cai`
2. Call `initmodel()` (which implements the `INITIAL` block):
   - `cai = cainf`
3. Write back to the ion:
   - `_ion_cai = cai`

Thus, **at `t = 0`, the pump forces `ca_ion.cai` to `cainf`**, regardless of what Python set `seg.cai` to before `finitialize`. In `run_neuron_full.py`:

```python
for seg in soma:
    seg.cai = 5.0e-5
    seg.cao = 2.0
...
soma.insert("cadad")
soma.depth_cadad = 1.0
soma.taur_cadad  = 5.0
soma.cainf_cadad = 2.4e-4
...
h.finitialize(h.v_init)
```

the `seg.cai = 5e-5` assignment is **overridden at initialisation**; the simulation actually starts from `cai = 2.4e-4` due to the `INITIAL { cai = cainf }` in `cadad.mod`.

### 3.2 Original `cadad_RE_soma_nml.mod` initialisation

Before our change, the NML-exported `INITIAL` block was:

```nmodl
INITIAL {
    initialConcentration = cai
    initialExtConcentration = cao
    rates()
    rates() ? To ensure correct initialisation.

    concentration = initialConcentration
    extConcentration = initialExtConcentration
}
```

The generated C++ `nrn_init` for `cadad_RE_soma_nml` (`x86_64/cadad_RE_soma_nml.cpp`) did:

1. Read the ionic concentrations:
   - `cai = _ion_cai`
   - `cao = _ion_cao`
2. Call `initmodel()`:
   - `initialConcentration` and `concentration` are set based on the existing `cai` / `cao`,
   - **but `cai` itself is not modified** in the `INITIAL` block.
3. Write back:
   - `_ion_cai = cai`

Therefore, unlike `cadad.mod`, the NML mechanism **did not override `cai` at `t = 0`**. It started with the Python-assigned value (`5e-5`), even though its internal state `concentration` was set consistently.

Combined with the fact that `run_neuron_full_nml_fix.py` explicitly sets:

```python
for seg in soma:
    seg.cai = 5.0e-5
    seg.cao = 2.0
...
soma.insert("cadad_RE_soma")
...
soma.cainf_cadad_RE_soma = 0.00024
...
```

this means:

- **NRN native + `cadad`**: starts from `cai = 2.4e-4` (overrides 5e-5).
- **NML-fix + `cadad_RE_soma_nml` (original)**: starts from `cai = 5e-5`, only later relaxing towards `cainf`.

Given the strong nonlinearity of T-type Ca currents and Ca-dependent dynamics, this different initial `cai` is enough to produce the observed divergence in the voltage traces when `cadad` is present, while the `noCadad` runs match almost exactly.

---

## 4. Fix: Make `cadad_RE_soma_nml` Initialise `cai` Like `cadad`

To align the behavior of the NML-exported mechanism with the original `cadad.mod`, we changed the `INITIAL` block in `mod/cadad_RE_soma_nml.mod` to explicitly set `cai` to `cainf` before setting up the internal state:

```nmodl
INITIAL {
    : Align with cadad.mod: force cai to start at cainf
    cai = cainf

    initialConcentration    = cai
    initialExtConcentration = cao
    rates()
    rates() ? To ensure correct initialisation.

    concentration    = initialConcentration
    extConcentration = initialExtConcentration
}
```

Conceptually, this makes the two mechanisms agree on:

- The continuous-time ODE for Ca concentration (`dcai/dt`),
- The effective scaling from `ica` to `dcai/dt` (via `depth`, `Faraday`, and unit conversions),
- **And crucially, the initial condition `cai(t=0) = cainf`**, matching what `cadad.mod` has always done.

After recompiling the mechanisms (e.g. `nrnivmodl mod`) and rerunning:

- `run_neuron_full.py` (NRN native, `cadad`),
- `run_neuron_full_nml_fix.py` (NML-fix, `cadad_RE_soma_nml`),

the Ca dynamics and voltage traces now agree up to numerical precision, just as they did when directly using `cadad.mod` in the NML pipeline.
