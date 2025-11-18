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

