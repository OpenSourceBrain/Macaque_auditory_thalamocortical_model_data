/* Created by Language version: 7.7.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mech_api.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__kdr_soma
#define _nrn_initial _nrn_initial__kdr_soma
#define nrn_cur _nrn_cur__kdr_soma
#define _nrn_current _nrn_current__kdr_soma
#define nrn_jacob _nrn_jacob__kdr_soma
#define nrn_state _nrn_state__kdr_soma
#define _net_receive _net_receive__kdr_soma 
#define rates rates__kdr_soma 
#define states states__kdr_soma 
 
#define _threadargscomma_ _p, _ppvar, _thread, _nt,
#define _threadargsprotocomma_ double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt,
#define _threadargs_ _p, _ppvar, _thread, _nt
#define _threadargsproto_ double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 /* Thread safe. No static _p or _ppvar. */
 
#define t _nt->_t
#define dt _nt->_dt
#define gmax _p[0]
#define gmax_columnindex 0
#define conductance _p[1]
#define conductance_columnindex 1
#define n_instances _p[2]
#define n_instances_columnindex 2
#define n_steadyState_VOLT_SCALE _p[3]
#define n_steadyState_VOLT_SCALE_columnindex 3
#define n_steadyState_Celsius _p[4]
#define n_steadyState_Celsius_columnindex 4
#define n_steadyState_zetan _p[5]
#define n_steadyState_zetan_columnindex 5
#define n_steadyState_sh _p[6]
#define n_steadyState_sh_columnindex 6
#define n_steadyState_vhalfn _p[7]
#define n_steadyState_vhalfn_columnindex 7
#define n_timeCourse_TIME_SCALE _p[8]
#define n_timeCourse_TIME_SCALE_columnindex 8
#define n_timeCourse_VOLT_SCALE _p[9]
#define n_timeCourse_VOLT_SCALE_columnindex 9
#define n_timeCourse_nmax _p[10]
#define n_timeCourse_nmax_columnindex 10
#define n_timeCourse_Celsius _p[11]
#define n_timeCourse_Celsius_columnindex 11
#define n_timeCourse_zetan _p[12]
#define n_timeCourse_zetan_columnindex 12
#define n_timeCourse_sh _p[13]
#define n_timeCourse_sh_columnindex 13
#define n_timeCourse_gmn _p[14]
#define n_timeCourse_gmn_columnindex 14
#define n_timeCourse_a0n _p[15]
#define n_timeCourse_a0n_columnindex 15
#define n_timeCourse_vhalfn _p[16]
#define n_timeCourse_vhalfn_columnindex 16
#define n_q10Settings_q10Factor _p[17]
#define n_q10Settings_q10Factor_columnindex 17
#define n_q10Settings_experimentalTemp _p[18]
#define n_q10Settings_experimentalTemp_columnindex 18
#define n_q10Settings_TENDEGREES _p[19]
#define n_q10Settings_TENDEGREES_columnindex 19
#define gion _p[20]
#define gion_columnindex 20
#define i__kdr_soma _p[21]
#define i__kdr_soma_columnindex 21
#define n_steadyState_V _p[22]
#define n_steadyState_V_columnindex 22
#define n_steadyState_x _p[23]
#define n_steadyState_x_columnindex 23
#define n_timeCourse_V _p[24]
#define n_timeCourse_V_columnindex 24
#define n_timeCourse_t _p[25]
#define n_timeCourse_t_columnindex 25
#define n_q10Settings_q10 _p[26]
#define n_q10Settings_q10_columnindex 26
#define n_rateScale _p[27]
#define n_rateScale_columnindex 27
#define n_fcond _p[28]
#define n_fcond_columnindex 28
#define n_inf _p[29]
#define n_inf_columnindex 29
#define n_tauUnscaled _p[30]
#define n_tauUnscaled_columnindex 30
#define n_tau _p[31]
#define n_tau_columnindex 31
#define conductanceScale _p[32]
#define conductanceScale_columnindex 32
#define fopen0 _p[33]
#define fopen0_columnindex 33
#define fopen _p[34]
#define fopen_columnindex 34
#define g _p[35]
#define g_columnindex 35
#define n_q _p[36]
#define n_q_columnindex 36
#define temperature _p[37]
#define temperature_columnindex 37
#define ek _p[38]
#define ek_columnindex 38
#define ik _p[39]
#define ik_columnindex 39
#define rate_n_q _p[40]
#define rate_n_q_columnindex 40
#define Dn_q _p[41]
#define Dn_q_columnindex 41
#define v _p[42]
#define v_columnindex 42
#define _g _p[43]
#define _g_columnindex 43
#define _ion_ik	*_ppvar[0]._pval
#define _ion_dikdv	*_ppvar[1]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  -1;
 static Datum* _extcall_thread;
 static Prop* _extcall_prop;
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_rates(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
#endif

 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_kdr_soma", _hoc_setdata,
 "rates_kdr_soma", _hoc_rates,
 0, 0
};
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gmax_kdr_soma", "S/cm2",
 "conductance_kdr_soma", "uS",
 "n_steadyState_VOLT_SCALE_kdr_soma", "mV",
 "n_timeCourse_TIME_SCALE_kdr_soma", "ms",
 "n_timeCourse_VOLT_SCALE_kdr_soma", "mV",
 "n_timeCourse_nmax_kdr_soma", "ms",
 "n_q10Settings_experimentalTemp_kdr_soma", "K",
 "n_q10Settings_TENDEGREES_kdr_soma", "K",
 "gion_kdr_soma", "S/cm2",
 "i__kdr_soma_kdr_soma", "mA/cm2",
 "n_timeCourse_t_kdr_soma", "ms",
 "n_tauUnscaled_kdr_soma", "ms",
 "n_tau_kdr_soma", "ms",
 "g_kdr_soma", "uS",
 0,0
};
 static double delta_t = 0.01;
 static double n_q0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(NrnThread*, _Memb_list*, int);
static void nrn_state(NrnThread*, _Memb_list*, int);
 static void nrn_cur(NrnThread*, _Memb_list*, int);
static void  nrn_jacob(NrnThread*, _Memb_list*, int);
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(NrnThread*, _Memb_list*, int);
static void _ode_matsol(NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[2]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"kdr_soma",
 "gmax_kdr_soma",
 "conductance_kdr_soma",
 "n_instances_kdr_soma",
 "n_steadyState_VOLT_SCALE_kdr_soma",
 "n_steadyState_Celsius_kdr_soma",
 "n_steadyState_zetan_kdr_soma",
 "n_steadyState_sh_kdr_soma",
 "n_steadyState_vhalfn_kdr_soma",
 "n_timeCourse_TIME_SCALE_kdr_soma",
 "n_timeCourse_VOLT_SCALE_kdr_soma",
 "n_timeCourse_nmax_kdr_soma",
 "n_timeCourse_Celsius_kdr_soma",
 "n_timeCourse_zetan_kdr_soma",
 "n_timeCourse_sh_kdr_soma",
 "n_timeCourse_gmn_kdr_soma",
 "n_timeCourse_a0n_kdr_soma",
 "n_timeCourse_vhalfn_kdr_soma",
 "n_q10Settings_q10Factor_kdr_soma",
 "n_q10Settings_experimentalTemp_kdr_soma",
 "n_q10Settings_TENDEGREES_kdr_soma",
 0,
 "gion_kdr_soma",
 "i__kdr_soma_kdr_soma",
 "n_steadyState_V_kdr_soma",
 "n_steadyState_x_kdr_soma",
 "n_timeCourse_V_kdr_soma",
 "n_timeCourse_t_kdr_soma",
 "n_q10Settings_q10_kdr_soma",
 "n_rateScale_kdr_soma",
 "n_fcond_kdr_soma",
 "n_inf_kdr_soma",
 "n_tauUnscaled_kdr_soma",
 "n_tau_kdr_soma",
 "conductanceScale_kdr_soma",
 "fopen0_kdr_soma",
 "fopen_kdr_soma",
 "g_kdr_soma",
 0,
 "n_q_kdr_soma",
 0,
 0};
 static Symbol* _k_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 44, _prop);
 	/*initialize range parameters*/
 	gmax = 0;
 	conductance = 1e-05;
 	n_instances = 1;
 	n_steadyState_VOLT_SCALE = 1;
 	n_steadyState_Celsius = 34;
 	n_steadyState_zetan = -3;
 	n_steadyState_sh = 0;
 	n_steadyState_vhalfn = 8;
 	n_timeCourse_TIME_SCALE = 1;
 	n_timeCourse_VOLT_SCALE = 1;
 	n_timeCourse_nmax = 20;
 	n_timeCourse_Celsius = 34;
 	n_timeCourse_zetan = -3;
 	n_timeCourse_sh = 0;
 	n_timeCourse_gmn = 0.7;
 	n_timeCourse_a0n = 0.0075;
 	n_timeCourse_vhalfn = 8;
 	n_q10Settings_q10Factor = 1;
 	n_q10Settings_experimentalTemp = 297.15;
 	n_q10Settings_TENDEGREES = 10;
 	_prop->param = _p;
 	_prop->param_size = 44;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 3, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_k_sym);
 	_ppvar[0]._pval = &prop_ion->param[3]; /* ik */
 	_ppvar[1]._pval = &prop_ion->param[4]; /* _ion_dikdv */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _kdr_soma_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("k", 1.0);
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 44, 3);
  hoc_register_dparam_semantics(_mechtype, 0, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 kdr_soma /home/gluciferd/Macaque_auditory_thalamocortical_model_data/NeuroML2/cells/IT2/kdr_soma.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "Mod file for component: Component(id=kdr_soma type=ionChannelHH)";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rates(_threadargsproto_);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[1], _dlist1[1];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset = 0; {
   rates ( _threadargs_ ) ;
   Dn_q = rate_n_q ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
 rates ( _threadargs_ ) ;
 Dn_q = Dn_q  / (1. - dt*( 0.0 )) ;
  return 0;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) { {
   rates ( _threadargs_ ) ;
    n_q = n_q - dt*(- ( rate_n_q ) ) ;
   }
  return 0;
}
 
static int  rates ( _threadargsproto_ ) {
   n_steadyState_V = v / n_steadyState_VOLT_SCALE ;
   n_steadyState_x = 1.0 / ( 1.0 + exp ( 1.e-3 * n_steadyState_zetan * ( n_steadyState_V - n_steadyState_vhalfn - n_steadyState_sh ) * 9.648e4 / ( 8.315 * ( 273.16 + n_steadyState_Celsius ) ) ) ) ;
   n_timeCourse_V = v / n_timeCourse_VOLT_SCALE ;
   if ( exp ( 1.e-3 * n_timeCourse_zetan * n_timeCourse_gmn * ( n_timeCourse_V - n_timeCourse_vhalfn - n_timeCourse_sh ) * 9.648e4 / ( 8.315 * ( 273.16 + n_timeCourse_Celsius ) ) ) / ( n_timeCourse_a0n * ( 1.0 + exp ( 1.e-3 * n_timeCourse_zetan * ( n_timeCourse_V - n_timeCourse_vhalfn - n_timeCourse_sh ) * 9.648e4 / ( 8.315 * ( 273.16 + n_timeCourse_Celsius ) ) ) ) ) * n_timeCourse_TIME_SCALE < n_timeCourse_nmax ) {
     n_timeCourse_t = n_timeCourse_nmax ;
     }
   else {
     n_timeCourse_t = exp ( 1.e-3 * n_timeCourse_zetan * n_timeCourse_gmn * ( n_timeCourse_V - n_timeCourse_vhalfn - n_timeCourse_sh ) * 9.648e4 / ( 8.315 * ( 273.16 + n_timeCourse_Celsius ) ) ) / ( n_timeCourse_a0n * ( 1.0 + exp ( 1.e-3 * n_timeCourse_zetan * ( n_timeCourse_V - n_timeCourse_vhalfn - n_timeCourse_sh ) * 9.648e4 / ( 8.315 * ( 273.16 + n_timeCourse_Celsius ) ) ) ) ) * n_timeCourse_TIME_SCALE ;
     }
   n_q10Settings_q10 = pow( n_q10Settings_q10Factor , ( ( temperature - n_q10Settings_experimentalTemp ) / n_q10Settings_TENDEGREES ) ) ;
   n_rateScale = n_q10Settings_q10 ;
   n_fcond = pow( n_q , n_instances ) ;
   n_inf = n_steadyState_x ;
   n_tauUnscaled = n_timeCourse_t ;
   n_tau = n_tauUnscaled / n_rateScale ;
   rate_n_q = ( n_inf - n_q ) / n_tau ;
    return 0; }
 
static void _hoc_rates(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 rates ( _p, _ppvar, _thread, _nt );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 1;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
     _ode_spec1 (_p, _ppvar, _thread, _nt);
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 1; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 (_p, _ppvar, _thread, _nt);
 }
 
static void _ode_matsol(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_k_sym, _ppvar, 0, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 1, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
  n_q = n_q0;
 {
   ek = - 104.0 ;
   temperature = celsius + 273.15 ;
   rates ( _threadargs_ ) ;
   rates ( _threadargs_ ) ;
   n_q = n_inf ;
   }
 
}
}

static void nrn_init(NrnThread* _nt, _Memb_list* _ml, int _type){
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
 initmodel(_p, _ppvar, _thread, _nt);
 }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   conductanceScale = 1.0 ;
   fopen0 = n_fcond ;
   fopen = conductanceScale * fopen0 ;
   g = conductance * fopen ;
   gion = gmax * fopen ;
   ik = gion * ( v - ek ) ;
   i__kdr_soma = - 1.0 * ik ;
   }
 _current += ik;

} return _current;
}

static void nrn_cur(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _dik;
  _dik = ik;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dikdv += (_dik - ik)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ik += ik ;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}
 
}

static void nrn_jacob(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}
 
}

static void nrn_state(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v=_v;
{
 {   states(_p, _ppvar, _thread, _nt);
  } }}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = n_q_columnindex;  _dlist1[0] = Dn_q_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/gluciferd/Macaque_auditory_thalamocortical_model_data/NeuroML2/cells/IT2/kdr_soma.mod";
static const char* nmodl_file_text = 
  "TITLE Mod file for component: Component(id=kdr_soma type=ionChannelHH)\n"
  "\n"
  "COMMENT\n"
  "\n"
  "    This NEURON file has been generated by org.neuroml.export (see https://github.com/NeuroML/org.neuroml.export)\n"
  "         org.neuroml.export  v1.11.0\n"
  "         org.neuroml.model   v1.11.0\n"
  "         jLEMS               v0.12.0\n"
  "\n"
  "ENDCOMMENT\n"
  "\n"
  "NEURON {\n"
  "    SUFFIX kdr_soma\n"
  "    USEION k WRITE ik VALENCE 1 ? Assuming valence = 1; TODO check this!!\n"
  "    \n"
  "    RANGE gion\n"
  "    RANGE i__kdr_soma : a copy of the variable for current which makes it easier to access from outside the mod file\n"
  "    RANGE gmax                              : Will be changed when ion channel mechanism placed on cell!\n"
  "    RANGE conductance                       : parameter\n"
  "    RANGE g                                 : exposure\n"
  "    RANGE fopen                             : exposure\n"
  "    RANGE n_instances                       : parameter\n"
  "    RANGE n_tau                             : exposure\n"
  "    RANGE n_inf                             : exposure\n"
  "    RANGE n_rateScale                       : exposure\n"
  "    RANGE n_fcond                           : exposure\n"
  "    RANGE n_steadyState_VOLT_SCALE          : parameter\n"
  "    RANGE n_steadyState_Celsius             : parameter\n"
  "    RANGE n_steadyState_zetan               : parameter\n"
  "    RANGE n_steadyState_sh                  : parameter\n"
  "    RANGE n_steadyState_vhalfn              : parameter\n"
  "    RANGE n_steadyState_x                   : exposure\n"
  "    RANGE n_timeCourse_TIME_SCALE           : parameter\n"
  "    RANGE n_timeCourse_VOLT_SCALE           : parameter\n"
  "    RANGE n_timeCourse_nmax                 : parameter\n"
  "    RANGE n_timeCourse_Celsius              : parameter\n"
  "    RANGE n_timeCourse_zetan                : parameter\n"
  "    RANGE n_timeCourse_sh                   : parameter\n"
  "    RANGE n_timeCourse_gmn                  : parameter\n"
  "    RANGE n_timeCourse_a0n                  : parameter\n"
  "    RANGE n_timeCourse_vhalfn               : parameter\n"
  "    RANGE n_timeCourse_t                    : exposure\n"
  "    RANGE n_q10Settings_q10Factor           : parameter\n"
  "    RANGE n_q10Settings_experimentalTemp    : parameter\n"
  "    RANGE n_q10Settings_TENDEGREES          : parameter\n"
  "    RANGE n_q10Settings_q10                 : exposure\n"
  "    RANGE n_steadyState_V                   : derived variable\n"
  "    RANGE n_timeCourse_V                    : derived variable\n"
  "    RANGE n_tauUnscaled                     : derived variable\n"
  "    RANGE conductanceScale                  : derived variable\n"
  "    RANGE fopen0                            : derived variable\n"
  "    \n"
  "}\n"
  "\n"
  "UNITS {\n"
  "    \n"
  "    (nA) = (nanoamp)\n"
  "    (uA) = (microamp)\n"
  "    (mA) = (milliamp)\n"
  "    (A) = (amp)\n"
  "    (mV) = (millivolt)\n"
  "    (mS) = (millisiemens)\n"
  "    (uS) = (microsiemens)\n"
  "    (nF) = (nanofarad)\n"
  "    (molar) = (1/liter)\n"
  "    (kHz) = (kilohertz)\n"
  "    (mM) = (millimolar)\n"
  "    (um) = (micrometer)\n"
  "    (umol) = (micromole)\n"
  "    (pC) = (picocoulomb)\n"
  "    (S) = (siemens)\n"
  "    \n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "    \n"
  "    gmax = 0  (S/cm2)                       : Will be changed when ion channel mechanism placed on cell!\n"
  "    \n"
  "    conductance = 1.0E-5 (uS)              : was: 1.0E-11 (conductance)\n"
  "    n_instances = 1                        : was: 1.0 (none)\n"
  "    n_steadyState_VOLT_SCALE = 1 (mV)      : was: 0.001 (voltage)\n"
  "    n_steadyState_Celsius = 34             : was: 34.0 (none)\n"
  "    n_steadyState_zetan = -3               : was: -3.0 (none)\n"
  "    n_steadyState_sh = 0                   : was: 0.0 (none)\n"
  "    n_steadyState_vhalfn = 8               : was: 8.0 (none)\n"
  "    n_timeCourse_TIME_SCALE = 1 (ms)       : was: 0.001 (time)\n"
  "    n_timeCourse_VOLT_SCALE = 1 (mV)       : was: 0.001 (voltage)\n"
  "    n_timeCourse_nmax = 20 (ms)            : was: 0.02 (time)\n"
  "    n_timeCourse_Celsius = 34              : was: 34.0 (none)\n"
  "    n_timeCourse_zetan = -3                : was: -3.0 (none)\n"
  "    n_timeCourse_sh = 0                    : was: 0.0 (none)\n"
  "    n_timeCourse_gmn = 0.7                 : was: 0.7 (none)\n"
  "    n_timeCourse_a0n = 0.0075              : was: 0.0075 (none)\n"
  "    n_timeCourse_vhalfn = 8                : was: 8.0 (none)\n"
  "    n_q10Settings_q10Factor = 1            : was: 1.0 (none)\n"
  "    n_q10Settings_experimentalTemp = 297.15 (K): was: 297.15 (temperature)\n"
  "    n_q10Settings_TENDEGREES = 10 (K)      : was: 10.0 (temperature)\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "    \n"
  "    gion   (S/cm2)                          : Transient conductance density of the channel? Standard Assigned variables with ionChannel\n"
  "    v (mV)\n"
  "    celsius (degC)\n"
  "    temperature (K)\n"
  "    ek (mV)\n"
  "    ik (mA/cm2)\n"
  "    i__kdr_soma (mA/cm2)\n"
  "    \n"
  "    n_steadyState_V                         : derived variable\n"
  "    n_steadyState_x                         : derived variable\n"
  "    n_timeCourse_V                          : derived variable\n"
  "    \n"
  "    n_timeCourse_t (ms)                     : conditional derived var...\n"
  "    n_q10Settings_q10                       : derived variable\n"
  "    n_rateScale                             : derived variable\n"
  "    n_fcond                                 : derived variable\n"
  "    n_inf                                   : derived variable\n"
  "    n_tauUnscaled (ms)                      : derived variable\n"
  "    n_tau (ms)                              : derived variable\n"
  "    conductanceScale                        : derived variable\n"
  "    fopen0                                  : derived variable\n"
  "    fopen                                   : derived variable\n"
  "    g (uS)                                  : derived variable\n"
  "    rate_n_q (/ms)\n"
  "    \n"
  "}\n"
  "\n"
  "STATE {\n"
  "    n_q  : dimension: none\n"
  "    \n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "    ek = -104.0\n"
  "    \n"
  "    temperature = celsius + 273.15\n"
  "    \n"
  "    rates()\n"
  "    rates() ? To ensure correct initialisation.\n"
  "    \n"
  "    n_q = n_inf\n"
  "    \n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "    \n"
  "    SOLVE states METHOD cnexp\n"
  "    \n"
  "    ? DerivedVariable is based on path: conductanceScaling[*]/factor, on: Component(id=kdr_soma type=ionChannelHH), from conductanceScaling; null\n"
  "    ? Path not present in component, using factor: 1\n"
  "    \n"
  "    conductanceScale = 1 \n"
  "    \n"
  "    ? DerivedVariable is based on path: gates[*]/fcond, on: Component(id=kdr_soma type=ionChannelHH), from gates; Component(id=n type=gateHHtauInf)\n"
  "    ? multiply applied to all instances of fcond in: <gates> ([Component(id=n type=gateHHtauInf)]))\n"
  "    fopen0 = n_fcond ? path based, prefix = \n"
  "    \n"
  "    fopen = conductanceScale  *  fopen0 ? evaluable\n"
  "    g = conductance  *  fopen ? evaluable\n"
  "    gion = gmax * fopen \n"
  "    \n"
  "    ik = gion * (v - ek)\n"
  "    i__kdr_soma =  -1 * ik : set this variable to the current also - note -1 as channel current convention for LEMS used!\n"
  "    \n"
  "}\n"
  "\n"
  "DERIVATIVE states {\n"
  "    rates()\n"
  "    n_q' = rate_n_q \n"
  "    \n"
  "}\n"
  "\n"
  "PROCEDURE rates() {\n"
  "    \n"
  "    n_steadyState_V = v /  n_steadyState_VOLT_SCALE ? evaluable\n"
  "    n_steadyState_x = 1 / (1 + exp(1.e-3* n_steadyState_zetan *( n_steadyState_V - n_steadyState_vhalfn - n_steadyState_sh )*9.648e4/\n"
  "                (8.315*(273.16+ n_steadyState_Celsius )))) ? evaluable\n"
  "    n_timeCourse_V = v /  n_timeCourse_VOLT_SCALE ? evaluable\n"
  "    if (exp(1.e-3* n_timeCourse_zetan * n_timeCourse_gmn *( n_timeCourse_V - n_timeCourse_vhalfn - n_timeCourse_sh )*9.648e4/(8.315*(273.16+ n_timeCourse_Celsius ))) / \n"
  "                    ( n_timeCourse_a0n  * (1 + exp(1.e-3* n_timeCourse_zetan *( n_timeCourse_V - n_timeCourse_vhalfn - n_timeCourse_sh )*9.648e4/(8.315*(273.16+ n_timeCourse_Celsius ))))) *  n_timeCourse_TIME_SCALE  <  n_timeCourse_nmax)  { \n"
  "        n_timeCourse_t = n_timeCourse_nmax ? evaluable cdv\n"
  "    } else  { \n"
  "        n_timeCourse_t = exp(1.e-3* n_timeCourse_zetan * n_timeCourse_gmn *( n_timeCourse_V - n_timeCourse_vhalfn - n_timeCourse_sh )*9.648e4/(8.315*(273.16+ n_timeCourse_Celsius ))) / \n"
  "                    ( n_timeCourse_a0n  * (1 + exp(1.e-3* n_timeCourse_zetan *( n_timeCourse_V - n_timeCourse_vhalfn - n_timeCourse_sh )*9.648e4/(8.315*(273.16+ n_timeCourse_Celsius ))))) *  n_timeCourse_TIME_SCALE ? evaluable cdv\n"
  "    }\n"
  "    \n"
  "    n_q10Settings_q10 = n_q10Settings_q10Factor ^((temperature -  n_q10Settings_experimentalTemp )/ n_q10Settings_TENDEGREES ) ? evaluable\n"
  "    ? DerivedVariable is based on path: q10Settings[*]/q10, on: Component(id=n type=gateHHtauInf), from q10Settings; Component(id=null type=q10ExpTemp)\n"
  "    ? multiply applied to all instances of q10 in: <q10Settings> ([Component(id=null type=q10ExpTemp)]))\n"
  "    n_rateScale = n_q10Settings_q10 ? path based, prefix = n_\n"
  "    \n"
  "    n_fcond = n_q ^ n_instances ? evaluable\n"
  "    ? DerivedVariable is based on path: steadyState/x, on: Component(id=n type=gateHHtauInf), from steadyState; Component(id=null type=kdr_soma_n_inf)\n"
  "    n_inf = n_steadyState_x ? path based, prefix = n_\n"
  "    \n"
  "    ? DerivedVariable is based on path: timeCourse/t, on: Component(id=n type=gateHHtauInf), from timeCourse; Component(id=null type=kdr_soma_n_tau)\n"
  "    n_tauUnscaled = n_timeCourse_t ? path based, prefix = n_\n"
  "    \n"
  "    n_tau = n_tauUnscaled  /  n_rateScale ? evaluable\n"
  "    \n"
  "     \n"
  "    rate_n_q = ( n_inf  -  n_q ) /  n_tau ? Note units of all quantities used here need to be consistent!\n"
  "    \n"
  "     \n"
  "    \n"
  "     \n"
  "    \n"
  "     \n"
  "    \n"
  "     \n"
  "    \n"
  "}\n"
  "\n"
  ;
#endif
