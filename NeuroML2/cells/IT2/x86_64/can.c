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
 
#define nrn_init _nrn_init__can
#define _nrn_initial _nrn_initial__can
#define nrn_cur _nrn_cur__can
#define _nrn_current _nrn_current__can
#define nrn_jacob _nrn_jacob__can
#define nrn_state _nrn_state__can
#define _net_receive _net_receive__can 
#define rates rates__can 
#define states states__can 
 
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
#define ConductanceScalingCaDependent_CONC_SCALE _p[2]
#define ConductanceScalingCaDependent_CONC_SCALE_columnindex 2
#define ConductanceScalingCaDependent_ki _p[3]
#define ConductanceScalingCaDependent_ki_columnindex 3
#define m_instances _p[4]
#define m_instances_columnindex 4
#define m_forwardRate_rate _p[5]
#define m_forwardRate_rate_columnindex 5
#define m_forwardRate_midpoint _p[6]
#define m_forwardRate_midpoint_columnindex 6
#define m_forwardRate_scale _p[7]
#define m_forwardRate_scale_columnindex 7
#define m_reverseRate_rate _p[8]
#define m_reverseRate_rate_columnindex 8
#define m_reverseRate_midpoint _p[9]
#define m_reverseRate_midpoint_columnindex 9
#define m_reverseRate_scale _p[10]
#define m_reverseRate_scale_columnindex 10
#define m_timeCourse_TIME_SCALE _p[11]
#define m_timeCourse_TIME_SCALE_columnindex 11
#define m_timeCourse_VOLT_SCALE _p[12]
#define m_timeCourse_VOLT_SCALE_columnindex 12
#define m_timeCourse_mmin _p[13]
#define m_timeCourse_mmin_columnindex 13
#define m_timeCourse_a0m _p[14]
#define m_timeCourse_a0m_columnindex 14
#define m_timeCourse_zetam _p[15]
#define m_timeCourse_zetam_columnindex 15
#define m_timeCourse_gmm _p[16]
#define m_timeCourse_gmm_columnindex 16
#define m_timeCourse_vhalfm _p[17]
#define m_timeCourse_vhalfm_columnindex 17
#define m_q10Settings_q10Factor _p[18]
#define m_q10Settings_q10Factor_columnindex 18
#define m_q10Settings_experimentalTemp _p[19]
#define m_q10Settings_experimentalTemp_columnindex 19
#define m_q10Settings_TENDEGREES _p[20]
#define m_q10Settings_TENDEGREES_columnindex 20
#define h_instances _p[21]
#define h_instances_columnindex 21
#define h_forwardRate_rate _p[22]
#define h_forwardRate_rate_columnindex 22
#define h_forwardRate_midpoint _p[23]
#define h_forwardRate_midpoint_columnindex 23
#define h_forwardRate_scale _p[24]
#define h_forwardRate_scale_columnindex 24
#define h_reverseRate_rate _p[25]
#define h_reverseRate_rate_columnindex 25
#define h_reverseRate_midpoint _p[26]
#define h_reverseRate_midpoint_columnindex 26
#define h_reverseRate_scale _p[27]
#define h_reverseRate_scale_columnindex 27
#define h_timeCourse_TIME_SCALE _p[28]
#define h_timeCourse_TIME_SCALE_columnindex 28
#define h_q10Settings_q10Factor _p[29]
#define h_q10Settings_q10Factor_columnindex 29
#define h_q10Settings_experimentalTemp _p[30]
#define h_q10Settings_experimentalTemp_columnindex 30
#define h_q10Settings_TENDEGREES _p[31]
#define h_q10Settings_TENDEGREES_columnindex 31
#define gion _p[32]
#define gion_columnindex 32
#define i__can _p[33]
#define i__can_columnindex 33
#define ConductanceScalingCaDependent_ca_conc _p[34]
#define ConductanceScalingCaDependent_ca_conc_columnindex 34
#define ConductanceScalingCaDependent_factor _p[35]
#define ConductanceScalingCaDependent_factor_columnindex 35
#define m_forwardRate_x _p[36]
#define m_forwardRate_x_columnindex 36
#define m_forwardRate_r _p[37]
#define m_forwardRate_r_columnindex 37
#define m_reverseRate_r _p[38]
#define m_reverseRate_r_columnindex 38
#define m_timeCourse_V _p[39]
#define m_timeCourse_V_columnindex 39
#define m_timeCourse_t _p[40]
#define m_timeCourse_t_columnindex 40
#define m_q10Settings_q10 _p[41]
#define m_q10Settings_q10_columnindex 41
#define m_rateScale _p[42]
#define m_rateScale_columnindex 42
#define m_alpha _p[43]
#define m_alpha_columnindex 43
#define m_beta _p[44]
#define m_beta_columnindex 44
#define m_fcond _p[45]
#define m_fcond_columnindex 45
#define m_inf _p[46]
#define m_inf_columnindex 46
#define m_tauUnscaled _p[47]
#define m_tauUnscaled_columnindex 47
#define m_tau _p[48]
#define m_tau_columnindex 48
#define h_forwardRate_r _p[49]
#define h_forwardRate_r_columnindex 49
#define h_reverseRate_r _p[50]
#define h_reverseRate_r_columnindex 50
#define h_timeCourse_t _p[51]
#define h_timeCourse_t_columnindex 51
#define h_q10Settings_q10 _p[52]
#define h_q10Settings_q10_columnindex 52
#define h_rateScale _p[53]
#define h_rateScale_columnindex 53
#define h_alpha _p[54]
#define h_alpha_columnindex 54
#define h_beta _p[55]
#define h_beta_columnindex 55
#define h_fcond _p[56]
#define h_fcond_columnindex 56
#define h_inf _p[57]
#define h_inf_columnindex 57
#define h_tauUnscaled _p[58]
#define h_tauUnscaled_columnindex 58
#define h_tau _p[59]
#define h_tau_columnindex 59
#define conductanceScale _p[60]
#define conductanceScale_columnindex 60
#define fopen0 _p[61]
#define fopen0_columnindex 61
#define fopen _p[62]
#define fopen_columnindex 62
#define g _p[63]
#define g_columnindex 63
#define m_q _p[64]
#define m_q_columnindex 64
#define h_q _p[65]
#define h_q_columnindex 65
#define temperature _p[66]
#define temperature_columnindex 66
#define eca _p[67]
#define eca_columnindex 67
#define ica _p[68]
#define ica_columnindex 68
#define cai _p[69]
#define cai_columnindex 69
#define cao _p[70]
#define cao_columnindex 70
#define rate_m_q _p[71]
#define rate_m_q_columnindex 71
#define rate_h_q _p[72]
#define rate_h_q_columnindex 72
#define Dm_q _p[73]
#define Dm_q_columnindex 73
#define Dh_q _p[74]
#define Dh_q_columnindex 74
#define v _p[75]
#define v_columnindex 75
#define _g _p[76]
#define _g_columnindex 76
#define _ion_eca	*_ppvar[0]._pval
#define _ion_ica	*_ppvar[1]._pval
#define _ion_dicadv	*_ppvar[2]._pval
 
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
 "setdata_can", _hoc_setdata,
 "rates_can", _hoc_rates,
 0, 0
};
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gmax_can", "S/cm2",
 "conductance_can", "uS",
 "ConductanceScalingCaDependent_CONC_SCALE_can", "mM",
 "m_forwardRate_rate_can", "kHz",
 "m_forwardRate_midpoint_can", "mV",
 "m_forwardRate_scale_can", "mV",
 "m_reverseRate_rate_can", "kHz",
 "m_reverseRate_midpoint_can", "mV",
 "m_reverseRate_scale_can", "mV",
 "m_timeCourse_TIME_SCALE_can", "ms",
 "m_timeCourse_VOLT_SCALE_can", "mV",
 "m_timeCourse_mmin_can", "ms",
 "m_q10Settings_experimentalTemp_can", "K",
 "m_q10Settings_TENDEGREES_can", "K",
 "h_forwardRate_rate_can", "kHz",
 "h_forwardRate_midpoint_can", "mV",
 "h_forwardRate_scale_can", "mV",
 "h_reverseRate_rate_can", "kHz",
 "h_reverseRate_midpoint_can", "mV",
 "h_reverseRate_scale_can", "mV",
 "h_timeCourse_TIME_SCALE_can", "ms",
 "h_q10Settings_experimentalTemp_can", "K",
 "h_q10Settings_TENDEGREES_can", "K",
 "gion_can", "S/cm2",
 "i__can_can", "mA/cm2",
 "m_forwardRate_r_can", "kHz",
 "m_reverseRate_r_can", "kHz",
 "m_timeCourse_t_can", "ms",
 "m_alpha_can", "kHz",
 "m_beta_can", "kHz",
 "m_tauUnscaled_can", "ms",
 "m_tau_can", "ms",
 "h_forwardRate_r_can", "kHz",
 "h_reverseRate_r_can", "kHz",
 "h_timeCourse_t_can", "ms",
 "h_alpha_can", "kHz",
 "h_beta_can", "kHz",
 "h_tauUnscaled_can", "ms",
 "h_tau_can", "ms",
 "g_can", "uS",
 0,0
};
 static double delta_t = 0.01;
 static double h_q0 = 0;
 static double m_q0 = 0;
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
 
#define _cvode_ieq _ppvar[3]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"can",
 "gmax_can",
 "conductance_can",
 "ConductanceScalingCaDependent_CONC_SCALE_can",
 "ConductanceScalingCaDependent_ki_can",
 "m_instances_can",
 "m_forwardRate_rate_can",
 "m_forwardRate_midpoint_can",
 "m_forwardRate_scale_can",
 "m_reverseRate_rate_can",
 "m_reverseRate_midpoint_can",
 "m_reverseRate_scale_can",
 "m_timeCourse_TIME_SCALE_can",
 "m_timeCourse_VOLT_SCALE_can",
 "m_timeCourse_mmin_can",
 "m_timeCourse_a0m_can",
 "m_timeCourse_zetam_can",
 "m_timeCourse_gmm_can",
 "m_timeCourse_vhalfm_can",
 "m_q10Settings_q10Factor_can",
 "m_q10Settings_experimentalTemp_can",
 "m_q10Settings_TENDEGREES_can",
 "h_instances_can",
 "h_forwardRate_rate_can",
 "h_forwardRate_midpoint_can",
 "h_forwardRate_scale_can",
 "h_reverseRate_rate_can",
 "h_reverseRate_midpoint_can",
 "h_reverseRate_scale_can",
 "h_timeCourse_TIME_SCALE_can",
 "h_q10Settings_q10Factor_can",
 "h_q10Settings_experimentalTemp_can",
 "h_q10Settings_TENDEGREES_can",
 0,
 "gion_can",
 "i__can_can",
 "ConductanceScalingCaDependent_ca_conc_can",
 "ConductanceScalingCaDependent_factor_can",
 "m_forwardRate_x_can",
 "m_forwardRate_r_can",
 "m_reverseRate_r_can",
 "m_timeCourse_V_can",
 "m_timeCourse_t_can",
 "m_q10Settings_q10_can",
 "m_rateScale_can",
 "m_alpha_can",
 "m_beta_can",
 "m_fcond_can",
 "m_inf_can",
 "m_tauUnscaled_can",
 "m_tau_can",
 "h_forwardRate_r_can",
 "h_reverseRate_r_can",
 "h_timeCourse_t_can",
 "h_q10Settings_q10_can",
 "h_rateScale_can",
 "h_alpha_can",
 "h_beta_can",
 "h_fcond_can",
 "h_inf_can",
 "h_tauUnscaled_can",
 "h_tau_can",
 "conductanceScale_can",
 "fopen0_can",
 "fopen_can",
 "g_can",
 0,
 "m_q_can",
 "h_q_can",
 0,
 0};
 static Symbol* _ca_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 77, _prop);
 	/*initialize range parameters*/
 	gmax = 0;
 	conductance = 1e-05;
 	ConductanceScalingCaDependent_CONC_SCALE = 1;
 	ConductanceScalingCaDependent_ki = 0.001;
 	m_instances = 2;
 	m_forwardRate_rate = 1.967;
 	m_forwardRate_midpoint = 19.88;
 	m_forwardRate_scale = 10;
 	m_reverseRate_rate = 0.046;
 	m_reverseRate_midpoint = 0;
 	m_reverseRate_scale = -20.73;
 	m_timeCourse_TIME_SCALE = 1;
 	m_timeCourse_VOLT_SCALE = 1;
 	m_timeCourse_mmin = 0.2;
 	m_timeCourse_a0m = 0.03;
 	m_timeCourse_zetam = 2;
 	m_timeCourse_gmm = 0.1;
 	m_timeCourse_vhalfm = -14;
 	m_q10Settings_q10Factor = 5;
 	m_q10Settings_experimentalTemp = 298.15;
 	m_q10Settings_TENDEGREES = 10;
 	h_instances = 1;
 	h_forwardRate_rate = 0.00016;
 	h_forwardRate_midpoint = 0;
 	h_forwardRate_scale = -48.4;
 	h_reverseRate_rate = 1;
 	h_reverseRate_midpoint = 39;
 	h_reverseRate_scale = 10;
 	h_timeCourse_TIME_SCALE = 1;
 	h_q10Settings_q10Factor = 5;
 	h_q10Settings_experimentalTemp = 298.15;
 	h_q10Settings_TENDEGREES = 10;
 	_prop->param = _p;
 	_prop->param_size = 77;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0]._pval = &prop_ion->param[0]; /* eca */
 	_ppvar[1]._pval = &prop_ion->param[3]; /* ica */
 	_ppvar[2]._pval = &prop_ion->param[4]; /* _ion_dicadv */
 
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

 void _can_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("ca", 2.0);
 	_ca_sym = hoc_lookup("ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 77, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 can /home/gluciferd/Macaque_auditory_thalamocortical_model_data/NeuroML2/cells/IT2/can.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "Mod file for component: Component(id=can type=ionChannelHH)";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rates(_threadargsproto_);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[2], _dlist1[2];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset = 0; {
   rates ( _threadargs_ ) ;
   Dm_q = rate_m_q ;
   Dh_q = rate_h_q ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
 rates ( _threadargs_ ) ;
 Dm_q = Dm_q  / (1. - dt*( 0.0 )) ;
 Dh_q = Dh_q  / (1. - dt*( 0.0 )) ;
  return 0;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) { {
   rates ( _threadargs_ ) ;
    m_q = m_q - dt*(- ( rate_m_q ) ) ;
    h_q = h_q - dt*(- ( rate_h_q ) ) ;
   }
  return 0;
}
 
static int  rates ( _threadargsproto_ ) {
   double _lcaConc ;
 _lcaConc = cai ;
   ConductanceScalingCaDependent_ca_conc = _lcaConc / ConductanceScalingCaDependent_CONC_SCALE ;
   ConductanceScalingCaDependent_factor = ConductanceScalingCaDependent_ki / ( ConductanceScalingCaDependent_ki + ConductanceScalingCaDependent_ca_conc ) ;
   m_forwardRate_x = ( v - m_forwardRate_midpoint ) / m_forwardRate_scale ;
   if ( m_forwardRate_x  != 0.0 ) {
     m_forwardRate_r = m_forwardRate_rate * m_forwardRate_x / ( 1.0 - exp ( 0.0 - m_forwardRate_x ) ) ;
     }
   else if ( m_forwardRate_x  == 0.0 ) {
     m_forwardRate_r = m_forwardRate_rate ;
     }
   m_reverseRate_r = m_reverseRate_rate * exp ( ( v - m_reverseRate_midpoint ) / m_reverseRate_scale ) ;
   m_timeCourse_V = v / m_timeCourse_VOLT_SCALE ;
   if ( exp ( 0.0378 * m_timeCourse_zetam * m_timeCourse_gmm * ( m_timeCourse_V - m_timeCourse_vhalfm ) ) / ( m_timeCourse_a0m * ( 1.0 + exp ( 0.0378 * m_timeCourse_zetam * ( m_timeCourse_V - m_timeCourse_vhalfm ) ) ) ) * m_timeCourse_TIME_SCALE < m_timeCourse_mmin ) {
     m_timeCourse_t = m_timeCourse_mmin ;
     }
   else {
     m_timeCourse_t = exp ( 0.0378 * m_timeCourse_zetam * m_timeCourse_gmm * ( m_timeCourse_V - m_timeCourse_vhalfm ) ) / ( m_timeCourse_a0m * ( 1.0 + exp ( 0.0378 * m_timeCourse_zetam * ( m_timeCourse_V - m_timeCourse_vhalfm ) ) ) ) * m_timeCourse_TIME_SCALE ;
     }
   m_q10Settings_q10 = pow( m_q10Settings_q10Factor , ( ( temperature - m_q10Settings_experimentalTemp ) / m_q10Settings_TENDEGREES ) ) ;
   m_rateScale = m_q10Settings_q10 ;
   m_alpha = m_forwardRate_r ;
   m_beta = m_reverseRate_r ;
   m_fcond = pow( m_q , m_instances ) ;
   m_inf = m_alpha / ( m_alpha + m_beta ) ;
   m_tauUnscaled = m_timeCourse_t ;
   m_tau = m_tauUnscaled / m_rateScale ;
   h_forwardRate_r = h_forwardRate_rate * exp ( ( v - h_forwardRate_midpoint ) / h_forwardRate_scale ) ;
   h_reverseRate_r = h_reverseRate_rate / ( 1.0 + exp ( 0.0 - ( v - h_reverseRate_midpoint ) / h_reverseRate_scale ) ) ;
   h_timeCourse_t = 80.0 * h_timeCourse_TIME_SCALE ;
   h_q10Settings_q10 = pow( h_q10Settings_q10Factor , ( ( temperature - h_q10Settings_experimentalTemp ) / h_q10Settings_TENDEGREES ) ) ;
   h_rateScale = h_q10Settings_q10 ;
   h_alpha = h_forwardRate_r ;
   h_beta = h_reverseRate_r ;
   h_fcond = pow( h_q , h_instances ) ;
   h_inf = h_alpha / ( h_alpha + h_beta ) ;
   h_tauUnscaled = h_timeCourse_t ;
   h_tau = h_tauUnscaled / h_rateScale ;
   rate_m_q = ( m_inf - m_q ) / m_tau ;
   rate_h_q = ( h_inf - h_q ) / h_tau ;
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
 
static int _ode_count(int _type){ return 2;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  eca = _ion_eca;
     _ode_spec1 (_p, _ppvar, _thread, _nt);
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 2; ++_i) {
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
  eca = _ion_eca;
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_ca_sym, _ppvar, 0, 0);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 2, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
  h_q = h_q0;
  m_q = m_q0;
 {
   temperature = celsius + 273.15 ;
   rates ( _threadargs_ ) ;
   rates ( _threadargs_ ) ;
   m_q = m_inf ;
   h_q = h_inf ;
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
  eca = _ion_eca;
 initmodel(_p, _ppvar, _thread, _nt);
 }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   conductanceScale = ConductanceScalingCaDependent_factor ;
   fopen0 = m_fcond * h_fcond ;
   fopen = conductanceScale * fopen0 ;
   g = conductance * fopen ;
   gion = gmax * fopen ;
   ica = gion * ( v - eca ) ;
   i__can = - 1.0 * ica ;
   }
 _current += ica;

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
  eca = _ion_eca;
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _dica;
  _dica = ica;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dicadv += (_dica - ica)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ica += ica ;
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
  eca = _ion_eca;
 {   states(_p, _ppvar, _thread, _nt);
  } }}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = m_q_columnindex;  _dlist1[0] = Dm_q_columnindex;
 _slist1[1] = h_q_columnindex;  _dlist1[1] = Dh_q_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/gluciferd/Macaque_auditory_thalamocortical_model_data/NeuroML2/cells/IT2/can.mod";
static const char* nmodl_file_text = 
  "TITLE Mod file for component: Component(id=can type=ionChannelHH)\n"
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
  "    SUFFIX can\n"
  "    USEION ca READ eca WRITE ica VALENCE 2 ? Assuming valence = 2 (Ca ion); TODO check this!!\n"
  "    \n"
  "    RANGE gion\n"
  "    RANGE i__can : a copy of the variable for current which makes it easier to access from outside the mod file\n"
  "    RANGE gmax                              : Will be changed when ion channel mechanism placed on cell!\n"
  "    RANGE conductance                       : parameter\n"
  "    RANGE g                                 : exposure\n"
  "    RANGE fopen                             : exposure\n"
  "    RANGE ConductanceScalingCaDependent_CONC_SCALE: parameter\n"
  "    RANGE ConductanceScalingCaDependent_ki  : parameter\n"
  "    RANGE ConductanceScalingCaDependent_factor: exposure\n"
  "    RANGE m_instances                       : parameter\n"
  "    RANGE m_alpha                           : exposure\n"
  "    RANGE m_beta                            : exposure\n"
  "    RANGE m_tau                             : exposure\n"
  "    RANGE m_inf                             : exposure\n"
  "    RANGE m_rateScale                       : exposure\n"
  "    RANGE m_fcond                           : exposure\n"
  "    RANGE m_forwardRate_rate                : parameter\n"
  "    RANGE m_forwardRate_midpoint            : parameter\n"
  "    RANGE m_forwardRate_scale               : parameter\n"
  "    RANGE m_forwardRate_r                   : exposure\n"
  "    RANGE m_reverseRate_rate                : parameter\n"
  "    RANGE m_reverseRate_midpoint            : parameter\n"
  "    RANGE m_reverseRate_scale               : parameter\n"
  "    RANGE m_reverseRate_r                   : exposure\n"
  "    RANGE m_timeCourse_TIME_SCALE           : parameter\n"
  "    RANGE m_timeCourse_VOLT_SCALE           : parameter\n"
  "    RANGE m_timeCourse_mmin                 : parameter\n"
  "    RANGE m_timeCourse_a0m                  : parameter\n"
  "    RANGE m_timeCourse_zetam                : parameter\n"
  "    RANGE m_timeCourse_gmm                  : parameter\n"
  "    RANGE m_timeCourse_vhalfm               : parameter\n"
  "    RANGE m_timeCourse_t                    : exposure\n"
  "    RANGE m_q10Settings_q10Factor           : parameter\n"
  "    RANGE m_q10Settings_experimentalTemp    : parameter\n"
  "    RANGE m_q10Settings_TENDEGREES          : parameter\n"
  "    RANGE m_q10Settings_q10                 : exposure\n"
  "    RANGE h_instances                       : parameter\n"
  "    RANGE h_alpha                           : exposure\n"
  "    RANGE h_beta                            : exposure\n"
  "    RANGE h_tau                             : exposure\n"
  "    RANGE h_inf                             : exposure\n"
  "    RANGE h_rateScale                       : exposure\n"
  "    RANGE h_fcond                           : exposure\n"
  "    RANGE h_forwardRate_rate                : parameter\n"
  "    RANGE h_forwardRate_midpoint            : parameter\n"
  "    RANGE h_forwardRate_scale               : parameter\n"
  "    RANGE h_forwardRate_r                   : exposure\n"
  "    RANGE h_reverseRate_rate                : parameter\n"
  "    RANGE h_reverseRate_midpoint            : parameter\n"
  "    RANGE h_reverseRate_scale               : parameter\n"
  "    RANGE h_reverseRate_r                   : exposure\n"
  "    RANGE h_timeCourse_TIME_SCALE           : parameter\n"
  "    RANGE h_timeCourse_t                    : exposure\n"
  "    RANGE h_q10Settings_q10Factor           : parameter\n"
  "    RANGE h_q10Settings_experimentalTemp    : parameter\n"
  "    RANGE h_q10Settings_TENDEGREES          : parameter\n"
  "    RANGE h_q10Settings_q10                 : exposure\n"
  "    RANGE ConductanceScalingCaDependent_ca_conc: derived variable\n"
  "    RANGE m_forwardRate_x                   : derived variable\n"
  "    RANGE m_timeCourse_V                    : derived variable\n"
  "    RANGE m_tauUnscaled                     : derived variable\n"
  "    RANGE h_tauUnscaled                     : derived variable\n"
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
  "    ConductanceScalingCaDependent_CONC_SCALE = 1 (mM): was: 1.0 (concentration)\n"
  "    ConductanceScalingCaDependent_ki = 0.001 : was: 0.001 (none)\n"
  "    m_instances = 2                        : was: 2.0 (none)\n"
  "    m_forwardRate_rate = 1.9670001 (kHz)   : was: 1967.0 (per_time)\n"
  "    m_forwardRate_midpoint = 19.88 (mV)    : was: 0.01988 (voltage)\n"
  "    m_forwardRate_scale = 10 (mV)          : was: 0.01 (voltage)\n"
  "    m_reverseRate_rate = 0.046000004 (kHz) : was: 46.0 (per_time)\n"
  "    m_reverseRate_midpoint = 0 (mV)        : was: 0.0 (voltage)\n"
  "    m_reverseRate_scale = -20.73 (mV)      : was: -0.020730000000000002 (voltage)\n"
  "    m_timeCourse_TIME_SCALE = 1 (ms)       : was: 0.001 (time)\n"
  "    m_timeCourse_VOLT_SCALE = 1 (mV)       : was: 0.001 (voltage)\n"
  "    m_timeCourse_mmin = 0.2 (ms)           : was: 2.0E-4 (time)\n"
  "    m_timeCourse_a0m = 0.03                : was: 0.03 (none)\n"
  "    m_timeCourse_zetam = 2                 : was: 2.0 (none)\n"
  "    m_timeCourse_gmm = 0.1                 : was: 0.1 (none)\n"
  "    m_timeCourse_vhalfm = -14              : was: -14.0 (none)\n"
  "    m_q10Settings_q10Factor = 5            : was: 5.0 (none)\n"
  "    m_q10Settings_experimentalTemp = 298.15 (K): was: 298.15 (temperature)\n"
  "    m_q10Settings_TENDEGREES = 10 (K)      : was: 10.0 (temperature)\n"
  "    h_instances = 1                        : was: 1.0 (none)\n"
  "    h_forwardRate_rate = 1.6000001E-4 (kHz): was: 0.16 (per_time)\n"
  "    h_forwardRate_midpoint = 0 (mV)        : was: 0.0 (voltage)\n"
  "    h_forwardRate_scale = -48.4 (mV)       : was: -0.0484 (voltage)\n"
  "    h_reverseRate_rate = 1 (kHz)           : was: 1000.0 (per_time)\n"
  "    h_reverseRate_midpoint = 39 (mV)       : was: 0.039 (voltage)\n"
  "    h_reverseRate_scale = 10 (mV)          : was: 0.01 (voltage)\n"
  "    h_timeCourse_TIME_SCALE = 1 (ms)       : was: 0.001 (time)\n"
  "    h_q10Settings_q10Factor = 5            : was: 5.0 (none)\n"
  "    h_q10Settings_experimentalTemp = 298.15 (K): was: 298.15 (temperature)\n"
  "    h_q10Settings_TENDEGREES = 10 (K)      : was: 10.0 (temperature)\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "    \n"
  "    gion   (S/cm2)                          : Transient conductance density of the channel? Standard Assigned variables with ionChannel\n"
  "    v (mV)\n"
  "    celsius (degC)\n"
  "    temperature (K)\n"
  "    eca (mV)\n"
  "    ica (mA/cm2)\n"
  "    i__can (mA/cm2)\n"
  "    \n"
  "    cai (mM)\n"
  "    \n"
  "    cao (mM)\n"
  "    \n"
  "    ConductanceScalingCaDependent_ca_conc   : derived variable\n"
  "    ConductanceScalingCaDependent_factor    : derived variable\n"
  "    m_forwardRate_x                         : derived variable\n"
  "    \n"
  "    m_forwardRate_r (kHz)                   : conditional derived var...\n"
  "    m_reverseRate_r (kHz)                   : derived variable\n"
  "    m_timeCourse_V                          : derived variable\n"
  "    \n"
  "    m_timeCourse_t (ms)                     : conditional derived var...\n"
  "    m_q10Settings_q10                       : derived variable\n"
  "    m_rateScale                             : derived variable\n"
  "    m_alpha (kHz)                           : derived variable\n"
  "    m_beta (kHz)                            : derived variable\n"
  "    m_fcond                                 : derived variable\n"
  "    m_inf                                   : derived variable\n"
  "    m_tauUnscaled (ms)                      : derived variable\n"
  "    m_tau (ms)                              : derived variable\n"
  "    h_forwardRate_r (kHz)                   : derived variable\n"
  "    h_reverseRate_r (kHz)                   : derived variable\n"
  "    h_timeCourse_t (ms)                     : derived variable\n"
  "    h_q10Settings_q10                       : derived variable\n"
  "    h_rateScale                             : derived variable\n"
  "    h_alpha (kHz)                           : derived variable\n"
  "    h_beta (kHz)                            : derived variable\n"
  "    h_fcond                                 : derived variable\n"
  "    h_inf                                   : derived variable\n"
  "    h_tauUnscaled (ms)                      : derived variable\n"
  "    h_tau (ms)                              : derived variable\n"
  "    conductanceScale                        : derived variable\n"
  "    fopen0                                  : derived variable\n"
  "    fopen                                   : derived variable\n"
  "    g (uS)                                  : derived variable\n"
  "    rate_m_q (/ms)\n"
  "    rate_h_q (/ms)\n"
  "    \n"
  "}\n"
  "\n"
  "STATE {\n"
  "    m_q  : dimension: none\n"
  "    h_q  : dimension: none\n"
  "    \n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "    temperature = celsius + 273.15\n"
  "    \n"
  "    rates()\n"
  "    rates() ? To ensure correct initialisation.\n"
  "    \n"
  "    m_q = m_inf\n"
  "    \n"
  "    h_q = h_inf\n"
  "    \n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "    \n"
  "    SOLVE states METHOD cnexp\n"
  "    \n"
  "    ? DerivedVariable is based on path: conductanceScaling[*]/factor, on: Component(id=can type=ionChannelHH), from conductanceScaling; Component(id=null type=can_scale)\n"
  "    ? multiply applied to all instances of factor in: <conductanceScaling> ([Component(id=null type=can_scale)]))\n"
  "    conductanceScale = ConductanceScalingCaDependent_factor ? path based, prefix = \n"
  "    \n"
  "    ? DerivedVariable is based on path: gates[*]/fcond, on: Component(id=can type=ionChannelHH), from gates; Component(id=m type=gateHHratesTau)\n"
  "    ? multiply applied to all instances of fcond in: <gates> ([Component(id=m type=gateHHratesTau), Component(id=h type=gateHHratesTau)]))\n"
  "    fopen0 = m_fcond * h_fcond ? path based, prefix = \n"
  "    \n"
  "    fopen = conductanceScale  *  fopen0 ? evaluable\n"
  "    g = conductance  *  fopen ? evaluable\n"
  "    gion = gmax * fopen \n"
  "    \n"
  "    ica = gion * (v - eca)\n"
  "    i__can =  -1 * ica : set this variable to the current also - note -1 as channel current convention for LEMS used!\n"
  "    \n"
  "}\n"
  "\n"
  "DERIVATIVE states {\n"
  "    rates()\n"
  "    m_q' = rate_m_q \n"
  "    h_q' = rate_h_q \n"
  "    \n"
  "}\n"
  "\n"
  "PROCEDURE rates() {\n"
  "    LOCAL caConc\n"
  "    \n"
  "    caConc = cai\n"
  "    \n"
  "    ConductanceScalingCaDependent_ca_conc = caConc /  ConductanceScalingCaDependent_CONC_SCALE ? evaluable\n"
  "    ConductanceScalingCaDependent_factor = ConductanceScalingCaDependent_ki  / ( ConductanceScalingCaDependent_ki  +  ConductanceScalingCaDependent_ca_conc ) ? evaluable\n"
  "    m_forwardRate_x = (v -  m_forwardRate_midpoint ) /  m_forwardRate_scale ? evaluable\n"
  "    if (m_forwardRate_x  != 0)  { \n"
  "        m_forwardRate_r = m_forwardRate_rate  *  m_forwardRate_x  / (1 - exp(0 -  m_forwardRate_x )) ? evaluable cdv\n"
  "    } else if (m_forwardRate_x  == 0)  { \n"
  "        m_forwardRate_r = m_forwardRate_rate ? evaluable cdv\n"
  "    }\n"
  "    \n"
  "    m_reverseRate_r = m_reverseRate_rate  * exp((v -  m_reverseRate_midpoint )/ m_reverseRate_scale ) ? evaluable\n"
  "    m_timeCourse_V = v /  m_timeCourse_VOLT_SCALE ? evaluable\n"
  "    if (exp(0.0378 *  m_timeCourse_zetam  *  m_timeCourse_gmm  * ( m_timeCourse_V  -  m_timeCourse_vhalfm )) / ( m_timeCourse_a0m  * (1 + exp(0.0378 *  m_timeCourse_zetam  * ( m_timeCourse_V  -  m_timeCourse_vhalfm )))) *  m_timeCourse_TIME_SCALE  <  m_timeCourse_mmin)  { \n"
  "        m_timeCourse_t = m_timeCourse_mmin ? evaluable cdv\n"
  "    } else  { \n"
  "        m_timeCourse_t = exp(0.0378 *  m_timeCourse_zetam  *  m_timeCourse_gmm  * ( m_timeCourse_V  -  m_timeCourse_vhalfm )) / ( m_timeCourse_a0m  * (1 + exp(0.0378 *  m_timeCourse_zetam  * ( m_timeCourse_V  -  m_timeCourse_vhalfm )))) *  m_timeCourse_TIME_SCALE ? evaluable cdv\n"
  "    }\n"
  "    \n"
  "    m_q10Settings_q10 = m_q10Settings_q10Factor ^((temperature -  m_q10Settings_experimentalTemp )/ m_q10Settings_TENDEGREES ) ? evaluable\n"
  "    ? DerivedVariable is based on path: q10Settings[*]/q10, on: Component(id=m type=gateHHratesTau), from q10Settings; Component(id=null type=q10ExpTemp)\n"
  "    ? multiply applied to all instances of q10 in: <q10Settings> ([Component(id=null type=q10ExpTemp)]))\n"
  "    m_rateScale = m_q10Settings_q10 ? path based, prefix = m_\n"
  "    \n"
  "    ? DerivedVariable is based on path: forwardRate/r, on: Component(id=m type=gateHHratesTau), from forwardRate; Component(id=null type=HHExpLinearRate)\n"
  "    m_alpha = m_forwardRate_r ? path based, prefix = m_\n"
  "    \n"
  "    ? DerivedVariable is based on path: reverseRate/r, on: Component(id=m type=gateHHratesTau), from reverseRate; Component(id=null type=HHExpRate)\n"
  "    m_beta = m_reverseRate_r ? path based, prefix = m_\n"
  "    \n"
  "    m_fcond = m_q ^ m_instances ? evaluable\n"
  "    m_inf = m_alpha /( m_alpha + m_beta ) ? evaluable\n"
  "    ? DerivedVariable is based on path: timeCourse/t, on: Component(id=m type=gateHHratesTau), from timeCourse; Component(id=null type=can_m_tau)\n"
  "    m_tauUnscaled = m_timeCourse_t ? path based, prefix = m_\n"
  "    \n"
  "    m_tau = m_tauUnscaled  /  m_rateScale ? evaluable\n"
  "    h_forwardRate_r = h_forwardRate_rate  * exp((v -  h_forwardRate_midpoint )/ h_forwardRate_scale ) ? evaluable\n"
  "    h_reverseRate_r = h_reverseRate_rate  / (1 + exp(0 - (v -  h_reverseRate_midpoint )/ h_reverseRate_scale )) ? evaluable\n"
  "    h_timeCourse_t = 80 *  h_timeCourse_TIME_SCALE ? evaluable\n"
  "    h_q10Settings_q10 = h_q10Settings_q10Factor ^((temperature -  h_q10Settings_experimentalTemp )/ h_q10Settings_TENDEGREES ) ? evaluable\n"
  "    ? DerivedVariable is based on path: q10Settings[*]/q10, on: Component(id=h type=gateHHratesTau), from q10Settings; Component(id=null type=q10ExpTemp)\n"
  "    ? multiply applied to all instances of q10 in: <q10Settings> ([Component(id=null type=q10ExpTemp)]))\n"
  "    h_rateScale = h_q10Settings_q10 ? path based, prefix = h_\n"
  "    \n"
  "    ? DerivedVariable is based on path: forwardRate/r, on: Component(id=h type=gateHHratesTau), from forwardRate; Component(id=null type=HHExpRate)\n"
  "    h_alpha = h_forwardRate_r ? path based, prefix = h_\n"
  "    \n"
  "    ? DerivedVariable is based on path: reverseRate/r, on: Component(id=h type=gateHHratesTau), from reverseRate; Component(id=null type=HHSigmoidRate)\n"
  "    h_beta = h_reverseRate_r ? path based, prefix = h_\n"
  "    \n"
  "    h_fcond = h_q ^ h_instances ? evaluable\n"
  "    h_inf = h_alpha /( h_alpha + h_beta ) ? evaluable\n"
  "    ? DerivedVariable is based on path: timeCourse/t, on: Component(id=h type=gateHHratesTau), from timeCourse; Component(id=null type=can_h_tau)\n"
  "    h_tauUnscaled = h_timeCourse_t ? path based, prefix = h_\n"
  "    \n"
  "    h_tau = h_tauUnscaled  /  h_rateScale ? evaluable\n"
  "    \n"
  "     \n"
  "    \n"
  "     \n"
  "    rate_m_q = ( m_inf  -  m_q ) /  m_tau ? Note units of all quantities used here need to be consistent!\n"
  "    \n"
  "     \n"
  "    \n"
  "     \n"
  "    \n"
  "     \n"
  "    \n"
  "     \n"
  "    \n"
  "     \n"
  "    rate_h_q = ( h_inf  -  h_q ) /  h_tau ? Note units of all quantities used here need to be consistent!\n"
  "    \n"
  "     \n"
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
