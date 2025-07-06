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
 
#define nrn_init _nrn_init__NafPyrKop
#define _nrn_initial _nrn_initial__NafPyrKop
#define nrn_cur _nrn_cur__NafPyrKop
#define _nrn_current _nrn_current__NafPyrKop
#define nrn_jacob _nrn_jacob__NafPyrKop
#define nrn_state _nrn_state__NafPyrKop
#define _net_receive _net_receive__NafPyrKop 
#define rates rates__NafPyrKop 
#define states states__NafPyrKop 
 
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
#define bk _p[1]
#define bk_columnindex 1
#define minf _p[2]
#define minf_columnindex 2
#define hinf _p[3]
#define hinf_columnindex 3
#define iinf _p[4]
#define iinf_columnindex 4
#define taom _p[5]
#define taom_columnindex 5
#define taoh _p[6]
#define taoh_columnindex 6
#define taoi _p[7]
#define taoi_columnindex 7
#define m _p[8]
#define m_columnindex 8
#define h _p[9]
#define h_columnindex 9
#define ii _p[10]
#define ii_columnindex 10
#define ina _p[11]
#define ina_columnindex 11
#define Dm _p[12]
#define Dm_columnindex 12
#define Dh _p[13]
#define Dh_columnindex 13
#define Dii _p[14]
#define Dii_columnindex 14
#define v _p[15]
#define v_columnindex 15
#define _g _p[16]
#define _g_columnindex 16
#define _ion_ina	*_ppvar[0]._pval
#define _ion_dinadv	*_ppvar[1]._pval
 
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
 /* declaration of user functions */
 static void _hoc_fun1(void);
 static void _hoc_fun2(void);
 static void _hoc_fun3(void);
 static void _hoc_min(void);
 static void _hoc_max(void);
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
 "setdata_NafPyrKop", _hoc_setdata,
 "fun1_NafPyrKop", _hoc_fun1,
 "fun2_NafPyrKop", _hoc_fun2,
 "fun3_NafPyrKop", _hoc_fun3,
 "min_NafPyrKop", _hoc_min,
 "max_NafPyrKop", _hoc_max,
 "rates_NafPyrKop", _hoc_rates,
 0, 0
};
#define fun1 fun1_NafPyrKop
#define fun2 fun2_NafPyrKop
#define fun3 fun3_NafPyrKop
#define min min_NafPyrKop
#define max max_NafPyrKop
 extern double fun1( _threadargsprotocomma_ double , double , double , double );
 extern double fun2( _threadargsprotocomma_ double , double , double , double );
 extern double fun3( _threadargsprotocomma_ double , double , double , double );
 extern double min( _threadargsprotocomma_ double , double );
 extern double max( _threadargsprotocomma_ double , double );
 /* declare global and static user variables */
#define ena ena_NafPyrKop
 double ena = 55;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "ena_NafPyrKop", "mV",
 "gmax_NafPyrKop", "mS/cm2",
 "bk_NafPyrKop", "1",
 "minf_NafPyrKop", "1",
 "hinf_NafPyrKop", "1",
 "iinf_NafPyrKop", "1",
 "taom_NafPyrKop", "ms",
 "taoh_NafPyrKop", "ms",
 "taoi_NafPyrKop", "ms",
 0,0
};
 static double delta_t = 0.01;
 static double h0 = 0;
 static double ii0 = 0;
 static double m0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "ena_NafPyrKop", &ena_NafPyrKop,
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
"NafPyrKop",
 "gmax_NafPyrKop",
 "bk_NafPyrKop",
 0,
 "minf_NafPyrKop",
 "hinf_NafPyrKop",
 "iinf_NafPyrKop",
 "taom_NafPyrKop",
 "taoh_NafPyrKop",
 "taoi_NafPyrKop",
 0,
 "m_NafPyrKop",
 "h_NafPyrKop",
 "ii_NafPyrKop",
 0,
 0};
 static Symbol* _na_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 17, _prop);
 	/*initialize range parameters*/
 	gmax = 32;
 	bk = 0;
 	_prop->param = _p;
 	_prop->param_size = 17;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 3, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_na_sym);
 	_ppvar[0]._pval = &prop_ion->param[3]; /* ina */
 	_ppvar[1]._pval = &prop_ion->param[4]; /* _ion_dinadv */
 
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

 void _nafpyrkop_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("na", -10000.);
 	_na_sym = hoc_lookup("na_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 17, 3);
  hoc_register_dparam_semantics(_mechtype, 0, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 NafPyrKop /home/gluciferd/Macaque_auditory_thalamocortical_model_data/model/mod/nafpyrkop.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rates(_threadargsprotocomma_ double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[3], _dlist1[3];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset = 0; {
   rates ( _threadargscomma_ v ) ;
   Dm = ( minf - m ) / taom ;
   Dh = ( hinf - h ) / taoh ;
   Dii = ( iinf - ii ) / taoi ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
 rates ( _threadargscomma_ v ) ;
 Dm = Dm  / (1. - dt*( ( ( ( - 1.0 ) ) ) / taom )) ;
 Dh = Dh  / (1. - dt*( ( ( ( - 1.0 ) ) ) / taoh )) ;
 Dii = Dii  / (1. - dt*( ( ( ( - 1.0 ) ) ) / taoi )) ;
  return 0;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) { {
   rates ( _threadargscomma_ v ) ;
    m = m + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / taom)))*(- ( ( ( minf ) ) / taom ) / ( ( ( ( - 1.0 ) ) ) / taom ) - m) ;
    h = h + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / taoh)))*(- ( ( ( hinf ) ) / taoh ) / ( ( ( ( - 1.0 ) ) ) / taoh ) - h) ;
    ii = ii + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / taoi)))*(- ( ( ( iinf ) ) / taoi ) / ( ( ( ( - 1.0 ) ) ) / taoi ) - ii) ;
   }
  return 0;
}
 
static int  rates ( _threadargsprotocomma_ double _lv ) {
   double _lam , _lbm , _lah , _lbh , _lai , _lbi ;
 _lam = fun3 ( _threadargscomma_ _lv , - 30.0 , - 0.4 , - 7.2 ) ;
   _lbm = fun3 ( _threadargscomma_ _lv , - 30.0 , 0.124 , 7.2 ) ;
   minf = _lam / ( _lam + _lbm ) ;
   taom = max ( _threadargscomma_ 0.02 , 0.5 / ( _lam + _lbm ) ) * 1.0 ;
   _lah = fun3 ( _threadargscomma_ _lv , - 45.0 , - 0.03 , - 1.5 ) ;
   _lbh = fun3 ( _threadargscomma_ _lv , - 45.0 , 0.01 , 1.5 ) ;
   taoh = max ( _threadargscomma_ 0.5 , 0.5 / ( _lah + _lbh ) ) * 1.0 ;
   hinf = fun2 ( _threadargscomma_ _lv , - 50.0 , 1.0 , 4.0 ) * 1.0 ;
   _lai = exp ( 0.45 * ( _lv + 66.0 ) ) ;
   _lbi = exp ( 0.09 * ( _lv + 66.0 ) ) ;
   taoi = max ( _threadargscomma_ 10.0 , 3000.0 * _lbi / ( 1.0 + _lai ) ) * 1.0 ;
   iinf = ( 1.0 + bk * exp ( ( _lv + 60.0 ) / 2.0 ) ) / ( 1.0 + exp ( ( _lv + 60.0 ) / 2.0 ) ) ;
    return 0; }
 
static void _hoc_rates(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 rates ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double fun1 ( _threadargsprotocomma_ double _lv , double _lV0 , double _lA , double _lB ) {
   double _lfun1;
 _lfun1 = _lA * exp ( ( _lv - _lV0 ) / _lB ) ;
   
return _lfun1;
 }
 
static void _hoc_fun1(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  fun1 ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) );
 hoc_retpushx(_r);
}
 
double fun2 ( _threadargsprotocomma_ double _lv , double _lV0 , double _lA , double _lB ) {
   double _lfun2;
 _lfun2 = _lA / ( exp ( ( _lv - _lV0 ) / _lB ) + 1.0 ) ;
   
return _lfun2;
 }
 
static void _hoc_fun2(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  fun2 ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) );
 hoc_retpushx(_r);
}
 
double fun3 ( _threadargsprotocomma_ double _lv , double _lV0 , double _lA , double _lB ) {
   double _lfun3;
 if ( fabs ( ( _lv - _lV0 ) / _lB ) < 1e-6 ) {
     _lfun3 = _lA * _lB / 1.0 * ( 1.0 - 0.5 * ( _lv - _lV0 ) / _lB ) ;
     }
   else {
     _lfun3 = _lA / 1.0 * ( _lv - _lV0 ) / ( exp ( ( _lv - _lV0 ) / _lB ) - 1.0 ) ;
     }
   
return _lfun3;
 }
 
static void _hoc_fun3(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  fun3 ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) );
 hoc_retpushx(_r);
}
 
double min ( _threadargsprotocomma_ double _lx , double _ly ) {
   double _lmin;
 if ( _lx <= _ly ) {
     _lmin = _lx ;
     }
   else {
     _lmin = _ly ;
     }
   
return _lmin;
 }
 
static void _hoc_min(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  min ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
double max ( _threadargsprotocomma_ double _lx , double _ly ) {
   double _lmax;
 if ( _lx >= _ly ) {
     _lmax = _lx ;
     }
   else {
     _lmax = _ly ;
     }
   
return _lmax;
 }
 
static void _hoc_max(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  max ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 3;}
 
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
	for (_i=0; _i < 3; ++_i) {
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
   nrn_update_ion_pointer(_na_sym, _ppvar, 0, 3);
   nrn_update_ion_pointer(_na_sym, _ppvar, 1, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
  h = h0;
  ii = ii0;
  m = m0;
 {
   rates ( _threadargscomma_ v ) ;
   m = minf ;
   h = hinf ;
   ii = iinf ;
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
   ina = ( 1e-3 ) * gmax * pow( m , 3.0 ) * h * ii * ( v - ena ) ;
   }
 _current += ina;

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
 	{ double _dina;
  _dina = ina;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dinadv += (_dina - ina)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ina += ina ;
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
 _slist1[0] = m_columnindex;  _dlist1[0] = Dm_columnindex;
 _slist1[1] = h_columnindex;  _dlist1[1] = Dh_columnindex;
 _slist1[2] = ii_columnindex;  _dlist1[2] = Dii_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/gluciferd/Macaque_auditory_thalamocortical_model_data/model/mod/nafpyrkop.mod";
static const char* nmodl_file_text = 
  ": $Id: nafpyrkop.mod,v 1.1 2009/11/05 15:09:03 samn Exp $ \n"
  "COMMENT\n"
  "\n"
  "//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
  "//\n"
  "// NOTICE OF COPYRIGHT AND OWNERSHIP OF SOFTWARE\n"
  "//\n"
  "// Copyright 2007, The University Of Pennsylvania\n"
  "// 	School of Engineering & Applied Science.\n"
  "//   All rights reserved.\n"
  "//   For research use only; commercial use prohibited.\n"
  "//   Distribution without permission of Maciej T. Lazarewicz not permitted.\n"
  "//   mlazarew@seas.upenn.edu\n"
  "//\n"
  "//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
  "\n"
  "This mode file is based on the paper:\n"
  "\n"
  "Tort, A. B., Rotstein, H. G., Dugladze, T., et al. (2007). On the formation of gamma-coherent cell\n"
  "assemblies by oriens lacunosum-moleculare interneurons in the hippocampus. Proc Natl Acad Sci U S A.\n"
  "\n"
  "ENDCOMMENT\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX NafPyrKop\n"
  "	USEION na WRITE ina\n"
  "	RANGE  bk, gmax, taom, taoh, taoi, minf, hinf, iinf\n"
  "}\n"
  "	\n"
  "UNITS {\n"
  "	(mA) = (milliamp)\n"
  "	(mV) = (millivolt)\n"
  "	(mS) = (millisiemens)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "    gmax = 32.0 (mS/cm2)\n"
  "    ena  = 55.0 (mV)\n"
  "    bk   =  0.0  (1)\n"
  "}\n"
  "    \n"
  "ASSIGNED {\n"
  "    v       (mV)\n"
  "    ina     (mA/cm2)\n"
  "    minf    (1)\n"
  "    hinf    (1)\n"
  "    iinf    (1)\n"
  "    taom    (ms)\n"
  "    taoh    (ms)\n"
  "    taoi    (ms)\n"
  "}\n"
  "\n"
  "STATE { m h ii }\n"
  "\n"
  "INITIAL {\n"
  "    rates(v)\n"
  "    m    = minf\n"
  "    h    = hinf\n"
  "    ii   = iinf\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "\n"
  "	SOLVE states METHOD cnexp\n"
  "	\n"
  "	ina = (1e-3) * gmax * m^3 * h * ii * (v-ena)\n"
  "}\n"
  "\n"
  "DERIVATIVE states { \n"
  "    rates(v)\n"
  "    m'  = (minf-m)/taom\n"
  "    h'  = (hinf-h)/taoh\n"
  "    ii' = (iinf-ii)/taoi\n"
  "}\n"
  "\n"
  "PROCEDURE rates(v(mV)) { LOCAL am, bm, ah, bh, ai, bi\n"
  "    \n"
  "    am   = fun3(v,  -30.0, -0.4,   -7.2)\n"
  "    bm   = fun3(v,  -30.0,  0.124,  7.2)\n"
  "    minf = am/(am+bm)\n"
  "    taom = max( 0.02, 0.5(/ms)/(am+bm) )*1.0(ms)\n"
  " \n"
  "    ah   = fun3(v,  -45.0,   -0.03, -1.5)\n"
  "    bh   = fun3(v,  -45.0,    0.01,  1.5)\n"
  "    taoh = max( 0.5, 0.5(/ms)/(ah+bh) )*1.0(ms)        \n"
  "    hinf = fun2(v, -50.0, 1.0, 4.0)*1.0(ms)\n"
  "    \n"
  "    ai   = exp(0.45(/mV)*(v+66.0))\n"
  "    bi   = exp(0.09(/mV)*(v+66.0))\n"
  "    taoi = max( 10.0, 3000.0*bi/(1.0+ai) )*1.0(ms)\n"
  "    iinf = (1.0+bk*exp((v+60.0)/2.0(mV))) / (1.0+exp((v+60.0)/2.0(mV)))\n"
  "}\n"
  "\n"
  ":::INCLUDE \"aux_fun.inc\"\n"
  ":::realpath /home/gluciferd/Macaque_auditory_thalamocortical_model_data/model/mod/aux_fun.inc\n"
  ": $Id: aux_fun.inc,v 1.1 2009/11/04 01:24:52 samn Exp $ \n"
  "COMMENT\n"
  "\n"
  "//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
  "//\n"
  "// NOTICE OF COPYRIGHT AND OWNERSHIP OF SOFTWARE\n"
  "//\n"
  "// Copyright 2007, The University Of Pennsylvania\n"
  "// 	School of Engineering & Applied Science.\n"
  "//   All rights reserved.\n"
  "//   For research use only; commercial use prohibited.\n"
  "//   Distribution without permission of Maciej T. Lazarewicz not permitted.\n"
  "//   mlazarew@seas.upenn.edu\n"
  "//\n"
  "//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
  "\n"
  "ENDCOMMENT\n"
  "\n"
  "\n"
  "\n"
  ":-------------------------------------------------------------------\n"
  "FUNCTION fun1(v(mV),V0(mV),A(/ms),B(mV))(/ms) {\n"
  "\n"
  "	 fun1 = A*exp((v-V0)/B)\n"
  "}\n"
  "\n"
  "FUNCTION fun2(v(mV),V0(mV),A(/ms),B(mV))(/ms) {\n"
  "\n"
  "	 fun2 = A/(exp((v-V0)/B)+1)\n"
  "}\n"
  "\n"
  "FUNCTION fun3(v(mV),V0(mV),A(/ms),B(mV))(/ms) {\n"
  "\n"
  "    if(fabs((v-V0)/B)<1e-6) {\n"
  "    :if(v==V0) {\n"
  "        fun3 = A*B/1(mV) * (1- 0.5 * (v-V0)/B)\n"
  "    } else {\n"
  "        fun3 = A/1(mV)*(v-V0)/(exp((v-V0)/B)-1)\n"
  "    }\n"
  "}\n"
  "\n"
  "FUNCTION min(x,y) { if (x<=y){ min = x }else{ min = y } }\n"
  "FUNCTION max(x,y) { if (x>=y){ max = x }else{ max = y } }\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  ":::end INCLUDE aux_fun.inc\n"
  ;
#endif
