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
 
#define nrn_init _nrn_init__kdr2orig
#define _nrn_initial _nrn_initial__kdr2orig
#define nrn_cur _nrn_cur__kdr2orig
#define _nrn_current _nrn_current__kdr2orig
#define nrn_jacob _nrn_jacob__kdr2orig
#define nrn_state _nrn_state__kdr2orig
#define _net_receive _net_receive__kdr2orig 
#define iassign iassign__kdr2orig 
#define mh mh__kdr2orig 
#define states states__kdr2orig 
 
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
#define gmax _p[0]
#define gmax_columnindex 0
#define mvalence _p[1]
#define mvalence_columnindex 1
#define mvhalf _p[2]
#define mvhalf_columnindex 2
#define hvalence _p[3]
#define hvalence_columnindex 3
#define hvhalf _p[4]
#define hvhalf_columnindex 4
#define i _p[5]
#define i_columnindex 5
#define g _p[6]
#define g_columnindex 6
#define m _p[7]
#define m_columnindex 7
#define h _p[8]
#define h_columnindex 8
#define ik _p[9]
#define ik_columnindex 9
#define mexp_val _p[10]
#define mexp_val_columnindex 10
#define hexp_val _p[11]
#define hexp_val_columnindex 11
#define Dm _p[12]
#define Dm_columnindex 12
#define Dh _p[13]
#define Dh_columnindex 13
#define _g _p[14]
#define _g_columnindex 14
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
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_FRT(void);
 static void _hoc_alpha(void);
 static void _hoc_beta(void);
 static void _hoc_faco(void);
 static void _hoc_ghkca(void);
 static void _hoc_iassign(void);
 static void _hoc_mh(void);
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
 "setdata_kdr2orig", _hoc_setdata,
 "FRT_kdr2orig", _hoc_FRT,
 "alpha_kdr2orig", _hoc_alpha,
 "beta_kdr2orig", _hoc_beta,
 "faco_kdr2orig", _hoc_faco,
 "ghkca_kdr2orig", _hoc_ghkca,
 "iassign_kdr2orig", _hoc_iassign,
 "mh_kdr2orig", _hoc_mh,
 0, 0
};
#define FRT FRT_kdr2orig
#define alpha alpha_kdr2orig
#define beta beta_kdr2orig
#define faco faco_kdr2orig
#define ghkca ghkca_kdr2orig
 extern double FRT( double );
 extern double alpha( double , double );
 extern double beta( double , double );
 extern double faco( );
 extern double ghkca( double );
 /* declare global and static user variables */
#define Inf Inf_kdr2orig
 double Inf[2];
#define Tau Tau_kdr2orig
 double Tau[2];
#define cai cai_kdr2orig
 double cai = 0;
#define cao cao_kdr2orig
 double cao = 0;
#define erev erev_kdr2orig
 double erev = -95;
#define hexp hexp_kdr2orig
 double hexp = 0;
#define hq10 hq10_kdr2orig
 double hq10 = 3;
#define htemp htemp_kdr2orig
 double htemp = 36;
#define hbasetau hbasetau_kdr2orig
 double hbasetau = 0.25;
#define hbaserate hbaserate_kdr2orig
 double hbaserate = 0.095;
#define hgamma hgamma_kdr2orig
 double hgamma = 0.3;
#define ki ki_kdr2orig
 double ki = 0.001;
#define mininf mininf_kdr2orig
 double mininf = 0.0001;
#define mexp mexp_kdr2orig
 double mexp = 3;
#define mq10 mq10_kdr2orig
 double mq10 = 3;
#define mtemp mtemp_kdr2orig
 double mtemp = 36;
#define mbasetau mbasetau_kdr2orig
 double mbasetau = 0.3;
#define mbaserate mbaserate_kdr2orig
 double mbaserate = 0.13;
#define mgamma mgamma_kdr2orig
 double mgamma = 0.5;
#define vmin vmin_kdr2orig
 double vmin = -100;
#define vmax vmax_kdr2orig
 double vmax = 100;
#define vrest vrest_kdr2orig
 double vrest = 0;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "erev_kdr2orig", "mV",
 "vmax_kdr2orig", "mV",
 "vmin_kdr2orig", "mV",
 "ki_kdr2orig", "mM",
 "cao_kdr2orig", "mM",
 "cai_kdr2orig", "mM",
 "gmax_kdr2orig", "umho",
 "i_kdr2orig", "mA/cm^2",
 "g_kdr2orig", "mho/cm^2",
 0,0
};
 static double delta_t = 1;
 static double h0 = 0;
 static double m0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "erev_kdr2orig", &erev_kdr2orig,
 "vrest_kdr2orig", &vrest_kdr2orig,
 "mgamma_kdr2orig", &mgamma_kdr2orig,
 "mbaserate_kdr2orig", &mbaserate_kdr2orig,
 "mbasetau_kdr2orig", &mbasetau_kdr2orig,
 "mtemp_kdr2orig", &mtemp_kdr2orig,
 "mq10_kdr2orig", &mq10_kdr2orig,
 "mexp_kdr2orig", &mexp_kdr2orig,
 "hgamma_kdr2orig", &hgamma_kdr2orig,
 "hbaserate_kdr2orig", &hbaserate_kdr2orig,
 "hbasetau_kdr2orig", &hbasetau_kdr2orig,
 "htemp_kdr2orig", &htemp_kdr2orig,
 "hq10_kdr2orig", &hq10_kdr2orig,
 "hexp_kdr2orig", &hexp_kdr2orig,
 "vmax_kdr2orig", &vmax_kdr2orig,
 "vmin_kdr2orig", &vmin_kdr2orig,
 "ki_kdr2orig", &ki_kdr2orig,
 "mininf_kdr2orig", &mininf_kdr2orig,
 "cao_kdr2orig", &cao_kdr2orig,
 "cai_kdr2orig", &cai_kdr2orig,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 "Inf_kdr2orig", Inf_kdr2orig, 2,
 "Tau_kdr2orig", Tau_kdr2orig, 2,
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
"kdr2orig",
 "gmax_kdr2orig",
 "mvalence_kdr2orig",
 "mvhalf_kdr2orig",
 "hvalence_kdr2orig",
 "hvhalf_kdr2orig",
 0,
 "i_kdr2orig",
 "g_kdr2orig",
 0,
 "m_kdr2orig",
 "h_kdr2orig",
 0,
 0};
 static Symbol* _k_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 15, _prop);
 	/*initialize range parameters*/
 	gmax = 0.005;
 	mvalence = 2.8;
 	mvhalf = -18;
 	hvalence = -6;
 	hvhalf = -39;
 	_prop->param = _p;
 	_prop->param_size = 15;
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

 void _kdr2_orig_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("k", -10000.);
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 15, 3);
  hoc_register_dparam_semantics(_mechtype, 0, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 kdr2orig /home/gluciferd/Macaque_auditory_thalamocortical_model_data/model/mod/kdr2_orig.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 96489.0;
 static double R = 8.31441;
static int _reset;
static char *modelname = "Kevin's Cvode modification to Borg Graham Channel Model";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int iassign();
static int mh(double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[2], _dlist1[2];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   mh ( _threadargscomma_ v ) ;
   Dm = ( - m + Inf [ 0 ] ) / Tau [ 0 ] ;
   Dh = ( - h + Inf [ 1 ] ) / Tau [ 1 ] ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 mh ( _threadargscomma_ v ) ;
 Dm = Dm  / (1. - dt*( ( ( - 1.0 ) ) / Tau[0] )) ;
 Dh = Dh  / (1. - dt*( ( ( - 1.0 ) ) / Tau[1] )) ;
  return 0;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   mh ( _threadargscomma_ v ) ;
    m = m + (1. - exp(dt*(( ( - 1.0 ) ) / Tau[0])))*(- ( ( ( Inf[0] ) ) / Tau[0] ) / ( ( ( - 1.0 ) ) / Tau[0] ) - m) ;
    h = h + (1. - exp(dt*(( ( - 1.0 ) ) / Tau[1])))*(- ( ( ( Inf[1] ) ) / Tau[1] ) / ( ( ( - 1.0 ) ) / Tau[1] ) - h) ;
   }
  return 0;
}
 
static int  mh (  double _lv ) {
   double _la , _lb , _lj , _lmqq10 , _lhqq10 ;
 _lmqq10 = pow( mq10 , ( ( celsius - mtemp ) / 10. ) ) ;
   _lhqq10 = pow( hq10 , ( ( celsius - htemp ) / 10. ) ) ;
   {int  _lj ;for ( _lj = 0 ; _lj <= 1 ; _lj ++ ) {
     _la = alpha ( _threadargscomma_ _lv , ((double) _lj ) ) ;
     _lb = beta ( _threadargscomma_ _lv , ((double) _lj ) ) ;
     Inf [ _lj ] = _la / ( _la + _lb ) ;
     if ( Inf [ _lj ] < mininf ) {
       Inf [ _lj ] = 0.0 ;
       }
     
/*VERBATIM*/
    switch (_lj) {
      case 0:
      /* Make sure Tau is not less than the base Tau */
if ((Tau[_lj] = 1 / (_la + _lb)) < mbasetau) {
  Tau[_lj] = mbasetau;
}
Tau[_lj] = Tau[_lj] / _lmqq10;
break;
case 1:
if ((Tau[_lj] = 1 / (_la + _lb)) < hbasetau) {
  Tau[_lj] = hbasetau;
}
Tau[_lj] = Tau[_lj] / _lhqq10;
if (hexp==0) {
  Tau[_lj] = 1.; }
  break;
    }

 } }
    return 0; }
 
static void _hoc_mh(void) {
  double _r;
   _r = 1.;
 mh (  *getarg(1) );
 hoc_retpushx(_r);
}
 
double alpha (  double _lv , double _lj ) {
   double _lalpha;
 if ( _lj  == 1.0 ) {
     if ( hexp  == 0.0 ) {
       _lalpha = 1.0 ;
       }
     else {
       _lalpha = hbaserate * exp ( ( _lv - ( hvhalf + vrest ) ) * hvalence * hgamma * FRT ( _threadargscomma_ htemp ) ) ;
       }
     }
   else {
     _lalpha = mbaserate * exp ( ( _lv - ( mvhalf + vrest ) ) * mvalence * mgamma * FRT ( _threadargscomma_ mtemp ) ) ;
     }
   
return _lalpha;
 }
 
static void _hoc_alpha(void) {
  double _r;
   _r =  alpha (  *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
double beta (  double _lv , double _lj ) {
   double _lbeta;
 if ( _lj  == 1.0 ) {
     if ( hexp  == 0.0 ) {
       _lbeta = 1.0 ;
       }
     else {
       _lbeta = hbaserate * exp ( ( - _lv + ( hvhalf + vrest ) ) * hvalence * ( 1.0 - hgamma ) * FRT ( _threadargscomma_ htemp ) ) ;
       }
     }
   else {
     _lbeta = mbaserate * exp ( ( - _lv + ( mvhalf + vrest ) ) * mvalence * ( 1.0 - mgamma ) * FRT ( _threadargscomma_ mtemp ) ) ;
     }
   
return _lbeta;
 }
 
static void _hoc_beta(void) {
  double _r;
   _r =  beta (  *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
double FRT (  double _ltemperature ) {
   double _lFRT;
 _lFRT = FARADAY * 0.001 / R / ( _ltemperature + 273.15 ) ;
   
return _lFRT;
 }
 
static void _hoc_FRT(void) {
  double _r;
   _r =  FRT (  *getarg(1) );
 hoc_retpushx(_r);
}
 
double ghkca (  double _lv ) {
   double _lghkca;
 double _lnu , _lefun ;
 _lnu = _lv * 2.0 * FRT ( _threadargscomma_ celsius ) ;
   if ( fabs ( _lnu ) < 1.e-6 ) {
     _lefun = 1. - _lnu / 2. ;
     }
   else {
     _lefun = _lnu / ( exp ( _lnu ) - 1. ) ;
     }
   _lghkca = - FARADAY * 2.e-3 * _lefun * ( cao - cai * exp ( _lnu ) ) ;
   
return _lghkca;
 }
 
static void _hoc_ghkca(void) {
  double _r;
   _r =  ghkca (  *getarg(1) );
 hoc_retpushx(_r);
}
 
double faco (  ) {
   double _lfaco;
 _lfaco = ki / ( ki + cai ) ;
   
return _lfaco;
 }
 
static void _hoc_faco(void) {
  double _r;
   _r =  faco (  );
 hoc_retpushx(_r);
}
 
static int  iassign (  ) {
   i = g * ( v - erev ) ;
   ik = i ;
    return 0; }
 
static void _hoc_iassign(void) {
  double _r;
   _r = 1.;
 iassign (  );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 2;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
     _ode_spec1 ();
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 2; ++_i) {
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
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_k_sym, _ppvar, 0, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 1, 4);
 }

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  h = h0;
  m = m0;
 {
   mh ( _threadargscomma_ v ) ;
   m = Inf [ 0 ] ;
   h = Inf [ 1 ] ;
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
 initmodel();
 }}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   if ( gmax  == 0.0 ) {
     g = 0. ;
     }
   else {
     hexp_val = 1.0 ;
     mexp_val = 1.0 ;
     if ( hexp > 0.0 ) {
       {int  _lindex ;for ( _lindex = 1 ; _lindex <= ((int) hexp ) ; _lindex ++ ) {
         hexp_val = h * hexp_val ;
         } }
       }
     if ( mexp > 0.0 ) {
       {int  _lindex ;for ( _lindex = 1 ; _lindex <= ((int) mexp ) ; _lindex ++ ) {
         mexp_val = m * mexp_val ;
         } }
       }
     g = gmax * mexp_val * hexp_val ;
     }
   iassign ( _threadargs_ ) ;
   }
 _current += ik;

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
 _g = _nrn_current(_v + .001);
 	{ double _dik;
  _dik = ik;
 _rhs = _nrn_current(_v);
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
 { error =  states();
 if(error){fprintf(stderr,"at line 110 in file bg_cvode.inc:\n\n"); nrn_complain(_p); abort_run(error);}
 } }}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = m_columnindex;  _dlist1[0] = Dm_columnindex;
 _slist1[1] = h_columnindex;  _dlist1[1] = Dh_columnindex;
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "/home/gluciferd/Macaque_auditory_thalamocortical_model_data/model/mod/kdr2_orig.mod";
static const char* nmodl_file_text = 
  "NEURON { SUFFIX kdr2orig }\n"
  "  \n"
  "NEURON { USEION k WRITE ik }         \n"
  "\n"
  "ASSIGNED { ik }\n"
  "\n"
  "PARAMETER {\n"
  "	erev 		= -95        (mV)\n"
  "	gmax 		= 0.005     (umho)\n"
  "\n"
  "        vrest           = 0.0\n"
  "	mvalence 	= 2.8\n"
  "	mgamma 		= 0.5			: 0.7\n"
  "	mbaserate 	= .13 \n"
  "	mvhalf 		=  -18\n"
  "	mbasetau 	= 0.3\n"
  "	mtemp 		=  36\n"
  "	mq10		=  3.0\n"
  "	mexp 		= 3\n"
  "\n"
  "	hvalence 	= -6\n"
  "	hgamma		=  0.3\n"
  "	hbaserate 	=  0.095\n"
  "	hvhalf 		=  -39\n"
  "	hbasetau 	=  0.25\n"
  "	htemp 		=  36\n"
  "	hq10        =  3.\n"
  "	hexp 		=  0\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "	celsius			     (degC)\n"
  "	dt 				     (ms)\n"
  "	v 			         (mV)\n"
  "\n"
  "	vmax 		= 100     (mV)\n"
  "	vmin 		= -100   (mV)\n"
  "\n"
  "} : end PARAMETER\n"
  "\n"
  ":::INCLUDE \"bg_cvode.inc\"\n"
  ":::realpath /home/gluciferd/Macaque_auditory_thalamocortical_model_data/model/mod/bg_cvode.inc\n"
  ": $Id: bg_cvode.inc,v 1.19 2009/01/13 13:59:48 billl Exp $\n"
  "TITLE Kevin's Cvode modification to Borg Graham Channel Model\n"
  ": EDITED BY ERICA Y GRIFFITH FEB 2020 FOR USE IN THALAMIC INTERNEURON MODEL \n"
  "COMMENT\n"
  "\n"
  "Modeling the somatic electrical response of hippocampal pyramidal neurons, \n"
  "MS thesis, MIT, May 1987.\n"
  "\n"
  "Each channel has activation and inactivation particles as in the original\n"
  "Hodgkin Huxley formulation.  The activation particle mm and inactivation\n"
  "particle hh go from on to off states according to kinetic variables alpha\n"
  "and beta which are voltage dependent.  The form of the alpha and beta\n"
  "functions were dissimilar in the HH study.  The BG formulae are:\n"
  "	alpha = base_rate * Exp[(v - v_half)*valence*gamma*F/RT]\n"
  "	beta = base_rate * Exp[(-v + v_half)*valence*(1-gamma)*F/RT]\n"
  "where,\n"
  "	baserate : no affect on Inf.  Lowering this increases the maximum\n"
  "		    value of Tau\n"
  "	basetau : (in msec) minimum Tau value.\n"
  "	chanexp : number for exponentiating the state variable; e.g.\n"
  "		  original HH Na channel use m^3, note that chanexp = 0\n"
  "		  will turn off this state variable\n"
  "	erev : reversal potential for the channel\n"
  "	gamma : (between 0 and 1) does not affect the Inf but makes the\n"
  "		Tau more asymetric with increasing deviation from 0.5\n"
  "	celsius : temperature at which experiment was done (Tau will\n"
  "		      will be adjusted using a q10 of 3.0)\n"
  "	valence : determines the steepness of the Inf sigmoid.  Higher\n"
  "		  valence gives steeper sigmoid.\n"
  "	vhalf : (a voltage) determines the voltage at which the value\n"
  "		 of the sigmoid function for Inf is 1/2\n"
  "        vrest : (a voltage) voltage shift for vhalf\n"
  "\n"
  "ENDCOMMENT\n"
  "\n"
  "INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}\n"
  "\n"
  "NEURON {\n"
  "  RANGE gmax, mvhalf, mvalence, hvhalf, hvalence, g, i\n"
  "  GLOBAL erev, Inf, Tau, vrest, ki, mininf\n"
  "} : end NEURON\n"
  "\n"
  "CONSTANT {\n"
  "  FARADAY = 96489.0	: Faraday's constant\n"
  "  R= 8.31441		: Gas constant\n"
  "} : end CONSTANT\n"
  "\n"
  "UNITS {\n"
  "  (mA) = (milliamp)\n"
  "  (mV) = (millivolt)\n"
  "  (umho) = (micromho)\n"
  "} : end UNITS\n"
  "\n"
  "\n"
  "COMMENT\n"
  "** Parameter values should come from files specific to particular channels\n"
  "PARAMETER {\n"
  "	erev 		= 0    (mV)\n"
  "	gmax 		= 0    (mho/cm^2)\n"
  "        vrest           = 0    (mV)\n"
  "\n"
  "	mvalence 	= 0\n"
  "	mgamma 		= 0\n"
  "	mbaserate 	= 0\n"
  "	mvhalf 		= 0\n"
  "	mbasetau 	= 0\n"
  "	mtemp 		= 0\n"
  "	mq10		= 3\n"
  "	mexp 		= 0\n"
  "\n"
  "	hvalence 	= 0\n"
  "	hgamma		= 0\n"
  "	hbaserate 	= 0\n"
  "	hvhalf 		= 0\n"
  "	hbasetau 	= 0\n"
  "	htemp 		= 0\n"
  "	hq10		= 3\n"
  "	hexp 		= 0\n"
  "\n"
  "} : end PARAMETER\n"
  "ENDCOMMENT\n"
  "\n"
  "PARAMETER {\n"
  "  ki = 1e-3  (mM)\n"
  "  mininf = 1e-4\n"
  "  cao                (mM)\n"
  "  cai                (mM)\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "  i (mA/cm^2)		\n"
  "  g (mho/cm^2)\n"
  "  Inf[2]		: 0 = m and 1 = h\n"
  "  Tau[2]		: 0 = m and 1 = h\n"
  "  mexp_val\n"
  "  hexp_val\n"
  "} : end ASSIGNED \n"
  "\n"
  "STATE { m h }\n"
  "\n"
  "INITIAL { \n"
  "  mh(v)\n"
  "  m = Inf[0] h = Inf[1]\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "  if (gmax==0.0) { g=0. } else {\n"
  "\n"
  "  SOLVE states METHOD cnexp\n"
  "\n"
  "  hexp_val = 1\n"
  "  mexp_val = 1\n"
  "\n"
  "  : Determining h's exponent value\n"
  "  if (hexp > 0) {\n"
  "    FROM index=1 TO hexp {\n"
  "      hexp_val = h * hexp_val\n"
  "    }\n"
  "  }\n"
  "\n"
  "  : Determining m's exponent value\n"
  "  if (mexp > 0) {\n"
  "    FROM index = 1 TO mexp {\n"
  "      mexp_val = m * mexp_val\n"
  "    }\n"
  "  }\n"
  "\n"
  "  :		       	         mexp			      hexp\n"
  "  : Note that mexp_val is now = m      and hexp_val is now = h \n"
  "  g = gmax * mexp_val * hexp_val\n"
  "  }\n"
  "  iassign()\n"
  "} : end BREAKPOINT\n"
  "\n"
  ": ASSIGNMENT PROCEDURES\n"
  ": Must be overwritten by user routines in parameters.multi\n"
  ": PROCEDURE iassign () { i = g*(v-erev) ina=i }\n"
  ": PROCEDURE iassign () { i = g*ghkca(v) ica=i }\n"
  "\n"
  ":-------------------------------------------------------------------\n"
  "\n"
  "DERIVATIVE states {\n"
  "  mh(v)\n"
  "  m' = (-m + Inf[0]) / Tau[0] \n"
  "  h' = (-h + Inf[1]) / Tau[1]\n"
  "}\n"
  ":-------------------------------------------------------------------\n"
  ": NOTE : 0 = m and 1 = h\n"
  "PROCEDURE mh (v) {\n"
  "  LOCAL a, b, j, mqq10, hqq10\n"
  "\n"
  "  mqq10 = mq10^((celsius-mtemp)/10.)	\n"
  "  hqq10 = hq10^((celsius-htemp)/10.)	\n"
  "\n"
  "  : Calculater Inf and Tau values for h and m\n"
  "  FROM j = 0 TO 1 {\n"
  "    a = alpha (v, j)\n"
  "    b = beta (v, j)\n"
  "\n"
  "    Inf[j] = a / (a + b)\n"
  "    if (Inf[j]<mininf) { Inf[j]=0 }\n"
  "\n"
  "    VERBATIM\n"
  "    switch (_lj) {\n"
  "      case 0:\n"
  "      /* Make sure Tau is not less than the base Tau */\n"
  "if ((Tau[_lj] = 1 / (_la + _lb)) < mbasetau) {\n"
  "  Tau[_lj] = mbasetau;\n"
  "}\n"
  "Tau[_lj] = Tau[_lj] / _lmqq10;\n"
  "break;\n"
  "case 1:\n"
  "if ((Tau[_lj] = 1 / (_la + _lb)) < hbasetau) {\n"
  "  Tau[_lj] = hbasetau;\n"
  "}\n"
  "Tau[_lj] = Tau[_lj] / _lhqq10;\n"
  "if (hexp==0) {\n"
  "  Tau[_lj] = 1.; }\n"
  "  break;\n"
  "    }\n"
  "\n"
  "    ENDVERBATIM\n"
  "  }\n"
  "} : end PROCEDURE mh (v)\n"
  ":-------------------------------------------------------------------\n"
  "FUNCTION alpha(v,j) {\n"
  "  if (j == 1) {\n"
  "    if (hexp==0) {\n"
  "      alpha = 1\n"
  "    } else {\n"
  "      alpha = hbaserate * exp((v - (hvhalf+vrest)) * hvalence * hgamma * FRT(htemp)) }\n"
  "  } else {\n"
  "    alpha = mbaserate * exp((v - (mvhalf+vrest)) * mvalence * mgamma * FRT(mtemp))\n"
  "  }\n"
  "} : end FUNCTION alpha (v,j)\n"
  "\n"
  ":-------------------------------------------------------------------\n"
  "FUNCTION beta (v,j) {\n"
  "  if (j == 1) {\n"
  "    if (hexp==0) {\n"
  "      beta = 1\n"
  "    } else {\n"
  "      beta = hbaserate * exp((-v + (hvhalf+vrest)) * hvalence * (1 - hgamma) * FRT(htemp)) }\n"
  "  } else {\n"
  "    beta = mbaserate * exp((-v + (mvhalf+vrest)) * mvalence * (1 - mgamma) * FRT(mtemp))\n"
  "  }\n"
  "} : end FUNCTION beta (v,j)\n"
  "\n"
  ":-------------------------------------------------------------------\n"
  "FUNCTION FRT(temperature) {\n"
  "	FRT = FARADAY * 0.001 / R / (temperature + 273.15)\n"
  "} : end FUNCTION FRT (temperature)\n"
  "\n"
  ":-------------------------------------------------------------------\n"
  "FUNCTION ghkca (v) { : Goldman-Hodgkin-Katz eqn\n"
  "  LOCAL nu, efun\n"
  "\n"
  "  nu = v*2*FRT(celsius)\n"
  "  if(fabs(nu) < 1.e-6) {\n"
  "    efun = 1.- nu/2.\n"
  "  } else {\n"
  "    efun = nu/(exp(nu)-1.) }\n"
  "\n"
  "    ghkca = -FARADAY*2.e-3*efun*(cao - cai*exp(nu))\n"
  "} : end FUNCTION ghkca()\n"
  "\n"
  ": Ca-mediated inactivation of Ca channels, see Hille, Ed2 p179-180\n"
  ": use eg iassign () { i = g*faco()*ghkca(v) ica=i }\n"
  "FUNCTION faco() {\n"
  "  faco = ki/(ki+cai)\n"
  "}\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  ":::end INCLUDE bg_cvode.inc\n"
  "\n"
  "PROCEDURE iassign () { i = g*(v-erev) ik=i }\n"
  ":** kmbg \n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  ;
#endif
