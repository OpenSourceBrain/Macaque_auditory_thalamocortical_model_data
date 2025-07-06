/* Created by Language version: 7.7.0 */
/* NOT VECTORIZED */
#define NRN_VECTORIZED 0
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
 
#define nrn_init _nrn_init__iahp
#define _nrn_initial _nrn_initial__iahp
#define nrn_cur _nrn_cur__iahp
#define _nrn_current _nrn_current__iahp
#define nrn_jacob _nrn_jacob__iahp
#define nrn_state _nrn_state__iahp
#define _net_receive _net_receive__iahp 
#define evaluate_fct evaluate_fct__iahp 
#define states states__iahp 
 
#define _threadargscomma_ /**/
#define _threadargsprotocomma_ /**/
#define _threadargs_ /**/
#define _threadargsproto_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define gkbar _p[0]
#define gkbar_columnindex 0
#define ratc _p[1]
#define ratc_columnindex 1
#define ratC _p[2]
#define ratC_columnindex 2
#define i _p[3]
#define i_columnindex 3
#define g _p[4]
#define g_columnindex 4
#define minf _p[5]
#define minf_columnindex 5
#define taum _p[6]
#define taum_columnindex 6
#define m _p[7]
#define m_columnindex 7
#define Cai _p[8]
#define Cai_columnindex 8
#define cai _p[9]
#define cai_columnindex 9
#define Dm _p[10]
#define Dm_columnindex 10
#define ik2 _p[11]
#define ik2_columnindex 11
#define tadj _p[12]
#define tadj_columnindex 12
#define _g _p[13]
#define _g_columnindex 13
#define _ion_ik2	*_ppvar[0]._pval
#define _ion_dik2dv	*_ppvar[1]._pval
#define _ion_Cai	*_ppvar[2]._pval
#define _ion_cai	*_ppvar[3]._pval
 
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
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_evaluate_fct(void);
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
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_iahp", _hoc_setdata,
 "evaluate_fct_iahp", _hoc_evaluate_fct,
 0, 0
};
 /* declare global and static user variables */
#define beta beta_iahp
 double beta = 2.5;
#define cac cac_iahp
 double cac = 0.0001;
#define erev erev_iahp
 double erev = -95;
#define m_inf m_inf_iahp
 double m_inf = 0;
#define taumin taumin_iahp
 double taumin = 1;
#define tau_m tau_m_iahp
 double tau_m = 0;
#define x x_iahp
 double x = 2;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "erev_iahp", "mV",
 "beta_iahp", "1/ms",
 "cac_iahp", "mM",
 "taumin_iahp", "ms",
 "tau_m_iahp", "ms",
 "gkbar_iahp", "mho/cm2",
 "i_iahp", "mA/cm2",
 "g_iahp", "mho/cm2",
 0,0
};
 static double delta_t = 1;
 static double m0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "erev_iahp", &erev_iahp,
 "beta_iahp", &beta_iahp,
 "cac_iahp", &cac_iahp,
 "taumin_iahp", &taumin_iahp,
 "x_iahp", &x_iahp,
 "m_inf_iahp", &m_inf_iahp,
 "tau_m_iahp", &tau_m_iahp,
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
 
#define _cvode_ieq _ppvar[4]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"iahp",
 "gkbar_iahp",
 "ratc_iahp",
 "ratC_iahp",
 0,
 "i_iahp",
 "g_iahp",
 "minf_iahp",
 "taum_iahp",
 0,
 "m_iahp",
 0,
 0};
 static Symbol* _k2_sym;
 static Symbol* _Ca_sym;
 static Symbol* _ca_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 14, _prop);
 	/*initialize range parameters*/
 	gkbar = 0.001;
 	ratc = 0;
 	ratC = 0;
 	_prop->param = _p;
 	_prop->param_size = 14;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 5, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_k2_sym);
 	_ppvar[0]._pval = &prop_ion->param[3]; /* ik2 */
 	_ppvar[1]._pval = &prop_ion->param[4]; /* _ion_dik2dv */
 prop_ion = need_memb(_Ca_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[2]._pval = &prop_ion->param[1]; /* Cai */
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[3]._pval = &prop_ion->param[1]; /* cai */
 
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

 void _Iahp_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("k2", 1.0);
 	ion_reg("Ca", 2.0);
 	ion_reg("ca", -10000.);
 	_k2_sym = hoc_lookup("k2_ion");
 	_Ca_sym = hoc_lookup("Ca_ion");
 	_ca_sym = hoc_lookup("ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 14, 5);
  hoc_register_dparam_semantics(_mechtype, 0, "k2_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "k2_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "Ca_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 iahp /home/gluciferd/Macaque_auditory_thalamocortical_model_data/model/mod/Iahp.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "Slow Ca-dependent potassium current";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int evaluate_fct(double, double, double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[1], _dlist1[1];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   evaluate_fct ( _threadargscomma_ v , Cai , cai ) ;
   Dm = ( m_inf - m ) / tau_m ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 evaluate_fct ( _threadargscomma_ v , Cai , cai ) ;
 Dm = Dm  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_m )) ;
  return 0;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   evaluate_fct ( _threadargscomma_ v , Cai , cai ) ;
    m = m + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_m)))*(- ( ( ( m_inf ) ) / tau_m ) / ( ( ( ( - 1.0 ) ) ) / tau_m ) - m) ;
   }
  return 0;
}
 
static int  evaluate_fct (  double _lv , double _lCai , double _lcai ) {
   double _lcar , _ltcar ;
 _ltcar = ratC * _lCai + ratc * _lcai ;
   _lcar = pow( ( _ltcar / cac ) , x ) ;
   m_inf = _lcar / ( 1.0 + _lcar ) ;
   tau_m = 1.0 / beta / ( 1.0 + _lcar ) / tadj ;
   if ( tau_m < taumin ) {
     tau_m = taumin ;
     }
    return 0; }
 
static void _hoc_evaluate_fct(void) {
  double _r;
   _r = 1.;
 evaluate_fct (  *getarg(1) , *getarg(2) , *getarg(3) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 1;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  Cai = _ion_Cai;
  cai = _ion_cai;
     _ode_spec1 ();
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 1; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 ();
 }
 
static void _ode_matsol(NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  Cai = _ion_Cai;
  cai = _ion_cai;
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_k2_sym, _ppvar, 0, 3);
   nrn_update_ion_pointer(_k2_sym, _ppvar, 1, 4);
   nrn_update_ion_pointer(_Ca_sym, _ppvar, 2, 1);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 3, 1);
 }

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  m = m0;
 {
   
/*VERBATIM*/
	cai = _ion_cai;
	Cai = _ion_Cai;
 tadj = pow( 3.0 , ( ( celsius - 22.0 ) / 10.0 ) ) ;
   evaluate_fct ( _threadargscomma_ v , Cai , cai ) ;
   m = m_inf ;
   minf = m_inf ;
   taum = tau_m ;
   }
  _sav_indep = t; t = _save;

}
}

static void nrn_init(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
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
  Cai = _ion_Cai;
  cai = _ion_cai;
 initmodel();
 }}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   minf = m_inf ;
   taum = tau_m ;
   g = gkbar * m * m ;
   i = g * ( v - erev ) ;
   ik2 = i ;
   }
 _current += ik2;

} return _current;
}

static void nrn_cur(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
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
  Cai = _ion_Cai;
  cai = _ion_cai;
 _g = _nrn_current(_v + .001);
 	{ double _dik2;
  _dik2 = ik2;
 _rhs = _nrn_current(_v);
  _ion_dik2dv += (_dik2 - ik2)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ik2 += ik2 ;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}}

static void nrn_jacob(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
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
 
}}

static void nrn_state(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
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
  Cai = _ion_Cai;
  cai = _ion_cai;
 { error =  states();
 if(error){fprintf(stderr,"at line 75 in file Iahp.mod:\n	SOLVE states METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 } }}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = m_columnindex;  _dlist1[0] = Dm_columnindex;
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "/home/gluciferd/Macaque_auditory_thalamocortical_model_data/model/mod/Iahp.mod";
static const char* nmodl_file_text = 
  ": $Id: Iahp.mod,v 1.8 2000/01/05 19:55:19 billl Exp $\n"
  "TITLE Slow Ca-dependent potassium current\n"
  ":\n"
  ":   Ca++ dependent K+ current IC responsible for slow AHP\n"
  ":   Differential equations\n"
  ":\n"
  ":   Model of Destexhe, 1992.  Based on a first order kinetic scheme\n"
  ":      <closed> + n cai <-> <open>	(alpha,beta)\n"
  ":   Following this model, the activation fct will be half-activated at \n"
  ":   a concentration of Cai = (beta/alpha)^(1/n) = cac (parameter)\n"
  ":   The mod file is here written for the case n=2 (2 binding sites)\n"
  ":   ---------------------------------------------\n"
  ":\n"
  ":   This current models the \"slow\" IK[Ca] (IAHP): \n"
  ":      - potassium current\n"
  ":      - activated by intracellular calcium\n"
  ":      - NOT voltage dependent\n"
  ":\n"
  ":   A minimal value for the time constant has been added\n"
  ":\n"
  ":   Written by Alain Destexhe, Salk Institute, Nov 3, 1992\n"
  ":\n"
  "\n"
  "INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX iahp\n"
  "	USEION k2 WRITE ik2 VALENCE 1\n"
  "	USEION Ca READ Cai VALENCE 2\n"
  "	USEION ca READ cai\n"
  "        RANGE gkbar, i, g, ratc, ratC, minf, taum\n"
  "	GLOBAL beta, cac, m_inf, tau_m, x\n"
  "}\n"
  "\n"
  "\n"
  "UNITS {\n"
  "	(mA) = (milliamp)\n"
  "	(mV) = (millivolt)\n"
  "	(molar) = (1/liter)\n"
  "	(mM) = (millimolar)\n"
  "}\n"
  "\n"
  "\n"
  "PARAMETER {\n"
  "	v		(mV)\n"
  "	celsius	= 36	(degC)\n"
  "	erev = -95		(mV)\n"
  "	Cai 	= 5e-5	(mM)		: initial [Ca]i = 50 nM\n"
  "	cai 	= 5e-5	(mM)		: initial [Ca]i = 50 nM\n"
  "	gkbar	= .001	(mho/cm2)\n"
  "	beta	= 2.5	(1/ms)		: backward rate constant\n"
  "	cac	= 1e-4	(mM)		: middle point of activation fct\n"
  "	taumin	= 1	(ms)		: minimal value of the time cst\n"
  "        ratc    = 0\n"
  "        ratC    = 0\n"
  "        x       = 2\n"
  "}\n"
  "\n"
  "\n"
  "STATE {\n"
  "	m\n"
  "}\n"
  "ASSIGNED {\n"
  "	ik2 	(mA/cm2)\n"
  "	i	(mA/cm2)\n"
  "	g       (mho/cm2)\n"
  "	m_inf\n"
  "	tau_m	(ms)\n"
  "	minf\n"
  "        taum\n"
  "	tadj\n"
  "}\n"
  "\n"
  "BREAKPOINT { \n"
  "	SOLVE states METHOD cnexp\n"
  "        minf=m_inf\n"
  "        taum=tau_m\n"
  "	g = gkbar * m*m\n"
  "	i = g * (v - erev)\n"
  "	ik2  = i\n"
  "}\n"
  "\n"
  "DERIVATIVE states { \n"
  "	evaluate_fct(v,Cai,cai)\n"
  "\n"
  "	m' = (m_inf - m) / tau_m\n"
  "}\n"
  "\n"
  "UNITSOFF\n"
  "INITIAL {\n"
  ":\n"
  ":  activation kinetics are assumed to be at 22 deg. C\n"
  ":  Q10 is assumed to be 3\n"
  ":\n"
  "	VERBATIM\n"
  "	cai = _ion_cai;\n"
  "	Cai = _ion_Cai;\n"
  "	ENDVERBATIM\n"
  "\n"
  "	tadj = 3 ^ ((celsius-22.0)/10)\n"
  "\n"
  "	evaluate_fct(v,Cai,cai)\n"
  "	m = m_inf\n"
  "        minf=m_inf\n"
  "        taum=tau_m\n"
  "}\n"
  "\n"
  "PROCEDURE evaluate_fct(v(mV),Cai(mM), cai(mM)) {  LOCAL car, tcar\n"
  "\n"
  "        tcar = ratC*Cai + ratc*cai\n"
  "	car = (tcar/cac)^x\n"
  "\n"
  "	m_inf = car / ( 1 + car )\n"
  "	tau_m = 1 / beta / (1 + car) / tadj\n"
  "\n"
  "        if(tau_m < taumin) { tau_m = taumin } 	: min value of time cst\n"
  "}\n"
  "UNITSON\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  ;
#endif
