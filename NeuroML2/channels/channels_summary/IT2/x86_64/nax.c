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
 
#define nrn_init _nrn_init__nax
#define _nrn_initial _nrn_initial__nax
#define nrn_cur _nrn_cur__nax
#define _nrn_current _nrn_current__nax
#define nrn_jacob _nrn_jacob__nax
#define nrn_state _nrn_state__nax
#define _net_receive _net_receive__nax 
#define rates rates__nax 
#define states states__nax 
 
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
#define m_instances _p[2]
#define m_instances_columnindex 2
#define m_forwardRate_TIME_SCALE _p[3]
#define m_forwardRate_TIME_SCALE_columnindex 3
#define m_forwardRate_VOLT_SCALE _p[4]
#define m_forwardRate_VOLT_SCALE_columnindex 4
#define m_forwardRate_Ra _p[5]
#define m_forwardRate_Ra_columnindex 5
#define m_forwardRate_qa _p[6]
#define m_forwardRate_qa_columnindex 6
#define m_forwardRate_tha _p[7]
#define m_forwardRate_tha_columnindex 7
#define m_forwardRate_sh _p[8]
#define m_forwardRate_sh_columnindex 8
#define m_reverseRate_TIME_SCALE _p[9]
#define m_reverseRate_TIME_SCALE_columnindex 9
#define m_reverseRate_VOLT_SCALE _p[10]
#define m_reverseRate_VOLT_SCALE_columnindex 10
#define m_reverseRate_Rb _p[11]
#define m_reverseRate_Rb_columnindex 11
#define m_reverseRate_qa _p[12]
#define m_reverseRate_qa_columnindex 12
#define m_reverseRate_tha _p[13]
#define m_reverseRate_tha_columnindex 13
#define m_reverseRate_sh _p[14]
#define m_reverseRate_sh_columnindex 14
#define m_timeCourse_TIME_SCALE _p[15]
#define m_timeCourse_TIME_SCALE_columnindex 15
#define m_timeCourse_VOLT_SCALE _p[16]
#define m_timeCourse_VOLT_SCALE_columnindex 16
#define m_timeCourse_mmin _p[17]
#define m_timeCourse_mmin_columnindex 17
#define m_q10Settings_q10Factor _p[18]
#define m_q10Settings_q10Factor_columnindex 18
#define m_q10Settings_experimentalTemp _p[19]
#define m_q10Settings_experimentalTemp_columnindex 19
#define m_q10Settings_TENDEGREES _p[20]
#define m_q10Settings_TENDEGREES_columnindex 20
#define h_instances _p[21]
#define h_instances_columnindex 21
#define h_forwardRate_TIME_SCALE _p[22]
#define h_forwardRate_TIME_SCALE_columnindex 22
#define h_forwardRate_VOLT_SCALE _p[23]
#define h_forwardRate_VOLT_SCALE_columnindex 23
#define h_forwardRate_Rd _p[24]
#define h_forwardRate_Rd_columnindex 24
#define h_forwardRate_qd _p[25]
#define h_forwardRate_qd_columnindex 25
#define h_forwardRate_thi1 _p[26]
#define h_forwardRate_thi1_columnindex 26
#define h_forwardRate_sh _p[27]
#define h_forwardRate_sh_columnindex 27
#define h_reverseRate_TIME_SCALE _p[28]
#define h_reverseRate_TIME_SCALE_columnindex 28
#define h_reverseRate_VOLT_SCALE _p[29]
#define h_reverseRate_VOLT_SCALE_columnindex 29
#define h_reverseRate_Rg _p[30]
#define h_reverseRate_Rg_columnindex 30
#define h_reverseRate_qg _p[31]
#define h_reverseRate_qg_columnindex 31
#define h_reverseRate_thi2 _p[32]
#define h_reverseRate_thi2_columnindex 32
#define h_reverseRate_sh _p[33]
#define h_reverseRate_sh_columnindex 33
#define h_steadyState_rate _p[34]
#define h_steadyState_rate_columnindex 34
#define h_steadyState_midpoint _p[35]
#define h_steadyState_midpoint_columnindex 35
#define h_steadyState_scale _p[36]
#define h_steadyState_scale_columnindex 36
#define h_timeCourse_TIME_SCALE _p[37]
#define h_timeCourse_TIME_SCALE_columnindex 37
#define h_timeCourse_VOLT_SCALE _p[38]
#define h_timeCourse_VOLT_SCALE_columnindex 38
#define h_timeCourse_hmin _p[39]
#define h_timeCourse_hmin_columnindex 39
#define h_q10Settings_q10Factor _p[40]
#define h_q10Settings_q10Factor_columnindex 40
#define h_q10Settings_experimentalTemp _p[41]
#define h_q10Settings_experimentalTemp_columnindex 41
#define h_q10Settings_TENDEGREES _p[42]
#define h_q10Settings_TENDEGREES_columnindex 42
#define gion _p[43]
#define gion_columnindex 43
#define i__nax _p[44]
#define i__nax_columnindex 44
#define m_forwardRate_V _p[45]
#define m_forwardRate_V_columnindex 45
#define m_forwardRate_r _p[46]
#define m_forwardRate_r_columnindex 46
#define m_reverseRate_V _p[47]
#define m_reverseRate_V_columnindex 47
#define m_reverseRate_r _p[48]
#define m_reverseRate_r_columnindex 48
#define m_timeCourse_V _p[49]
#define m_timeCourse_V_columnindex 49
#define m_timeCourse_ALPHA _p[50]
#define m_timeCourse_ALPHA_columnindex 50
#define m_timeCourse_BETA _p[51]
#define m_timeCourse_BETA_columnindex 51
#define m_timeCourse_t _p[52]
#define m_timeCourse_t_columnindex 52
#define m_q10Settings_q10 _p[53]
#define m_q10Settings_q10_columnindex 53
#define m_rateScale _p[54]
#define m_rateScale_columnindex 54
#define m_alpha _p[55]
#define m_alpha_columnindex 55
#define m_beta _p[56]
#define m_beta_columnindex 56
#define m_fcond _p[57]
#define m_fcond_columnindex 57
#define m_inf _p[58]
#define m_inf_columnindex 58
#define m_tauUnscaled _p[59]
#define m_tauUnscaled_columnindex 59
#define m_tau _p[60]
#define m_tau_columnindex 60
#define h_forwardRate_V _p[61]
#define h_forwardRate_V_columnindex 61
#define h_forwardRate_r _p[62]
#define h_forwardRate_r_columnindex 62
#define h_reverseRate_V _p[63]
#define h_reverseRate_V_columnindex 63
#define h_reverseRate_r _p[64]
#define h_reverseRate_r_columnindex 64
#define h_steadyState_x _p[65]
#define h_steadyState_x_columnindex 65
#define h_timeCourse_V _p[66]
#define h_timeCourse_V_columnindex 66
#define h_timeCourse_ALPHA _p[67]
#define h_timeCourse_ALPHA_columnindex 67
#define h_timeCourse_BETA _p[68]
#define h_timeCourse_BETA_columnindex 68
#define h_timeCourse_t _p[69]
#define h_timeCourse_t_columnindex 69
#define h_q10Settings_q10 _p[70]
#define h_q10Settings_q10_columnindex 70
#define h_rateScale _p[71]
#define h_rateScale_columnindex 71
#define h_alpha _p[72]
#define h_alpha_columnindex 72
#define h_beta _p[73]
#define h_beta_columnindex 73
#define h_inf _p[74]
#define h_inf_columnindex 74
#define h_tauUnscaled _p[75]
#define h_tauUnscaled_columnindex 75
#define h_tau _p[76]
#define h_tau_columnindex 76
#define h_fcond _p[77]
#define h_fcond_columnindex 77
#define conductanceScale _p[78]
#define conductanceScale_columnindex 78
#define fopen0 _p[79]
#define fopen0_columnindex 79
#define fopen _p[80]
#define fopen_columnindex 80
#define g _p[81]
#define g_columnindex 81
#define m_q _p[82]
#define m_q_columnindex 82
#define h_q _p[83]
#define h_q_columnindex 83
#define temperature _p[84]
#define temperature_columnindex 84
#define ena _p[85]
#define ena_columnindex 85
#define ina _p[86]
#define ina_columnindex 86
#define rate_m_q _p[87]
#define rate_m_q_columnindex 87
#define rate_h_q _p[88]
#define rate_h_q_columnindex 88
#define Dm_q _p[89]
#define Dm_q_columnindex 89
#define Dh_q _p[90]
#define Dh_q_columnindex 90
#define v _p[91]
#define v_columnindex 91
#define _g _p[92]
#define _g_columnindex 92
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
 "setdata_nax", _hoc_setdata,
 "rates_nax", _hoc_rates,
 0, 0
};
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gmax_nax", "S/cm2",
 "conductance_nax", "uS",
 "m_forwardRate_TIME_SCALE_nax", "ms",
 "m_forwardRate_VOLT_SCALE_nax", "mV",
 "m_reverseRate_TIME_SCALE_nax", "ms",
 "m_reverseRate_VOLT_SCALE_nax", "mV",
 "m_timeCourse_TIME_SCALE_nax", "ms",
 "m_timeCourse_VOLT_SCALE_nax", "mV",
 "m_q10Settings_experimentalTemp_nax", "K",
 "m_q10Settings_TENDEGREES_nax", "K",
 "h_forwardRate_TIME_SCALE_nax", "ms",
 "h_forwardRate_VOLT_SCALE_nax", "mV",
 "h_reverseRate_TIME_SCALE_nax", "ms",
 "h_reverseRate_VOLT_SCALE_nax", "mV",
 "h_steadyState_midpoint_nax", "mV",
 "h_steadyState_scale_nax", "mV",
 "h_timeCourse_TIME_SCALE_nax", "ms",
 "h_timeCourse_VOLT_SCALE_nax", "mV",
 "h_q10Settings_experimentalTemp_nax", "K",
 "h_q10Settings_TENDEGREES_nax", "K",
 "gion_nax", "S/cm2",
 "i__nax_nax", "mA/cm2",
 "m_forwardRate_r_nax", "kHz",
 "m_reverseRate_r_nax", "kHz",
 "m_timeCourse_t_nax", "ms",
 "m_alpha_nax", "kHz",
 "m_beta_nax", "kHz",
 "m_tauUnscaled_nax", "ms",
 "m_tau_nax", "ms",
 "h_forwardRate_r_nax", "kHz",
 "h_reverseRate_r_nax", "kHz",
 "h_timeCourse_t_nax", "ms",
 "h_alpha_nax", "kHz",
 "h_beta_nax", "kHz",
 "h_tauUnscaled_nax", "ms",
 "h_tau_nax", "ms",
 "g_nax", "uS",
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
 
#define _cvode_ieq _ppvar[2]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"nax",
 "gmax_nax",
 "conductance_nax",
 "m_instances_nax",
 "m_forwardRate_TIME_SCALE_nax",
 "m_forwardRate_VOLT_SCALE_nax",
 "m_forwardRate_Ra_nax",
 "m_forwardRate_qa_nax",
 "m_forwardRate_tha_nax",
 "m_forwardRate_sh_nax",
 "m_reverseRate_TIME_SCALE_nax",
 "m_reverseRate_VOLT_SCALE_nax",
 "m_reverseRate_Rb_nax",
 "m_reverseRate_qa_nax",
 "m_reverseRate_tha_nax",
 "m_reverseRate_sh_nax",
 "m_timeCourse_TIME_SCALE_nax",
 "m_timeCourse_VOLT_SCALE_nax",
 "m_timeCourse_mmin_nax",
 "m_q10Settings_q10Factor_nax",
 "m_q10Settings_experimentalTemp_nax",
 "m_q10Settings_TENDEGREES_nax",
 "h_instances_nax",
 "h_forwardRate_TIME_SCALE_nax",
 "h_forwardRate_VOLT_SCALE_nax",
 "h_forwardRate_Rd_nax",
 "h_forwardRate_qd_nax",
 "h_forwardRate_thi1_nax",
 "h_forwardRate_sh_nax",
 "h_reverseRate_TIME_SCALE_nax",
 "h_reverseRate_VOLT_SCALE_nax",
 "h_reverseRate_Rg_nax",
 "h_reverseRate_qg_nax",
 "h_reverseRate_thi2_nax",
 "h_reverseRate_sh_nax",
 "h_steadyState_rate_nax",
 "h_steadyState_midpoint_nax",
 "h_steadyState_scale_nax",
 "h_timeCourse_TIME_SCALE_nax",
 "h_timeCourse_VOLT_SCALE_nax",
 "h_timeCourse_hmin_nax",
 "h_q10Settings_q10Factor_nax",
 "h_q10Settings_experimentalTemp_nax",
 "h_q10Settings_TENDEGREES_nax",
 0,
 "gion_nax",
 "i__nax_nax",
 "m_forwardRate_V_nax",
 "m_forwardRate_r_nax",
 "m_reverseRate_V_nax",
 "m_reverseRate_r_nax",
 "m_timeCourse_V_nax",
 "m_timeCourse_ALPHA_nax",
 "m_timeCourse_BETA_nax",
 "m_timeCourse_t_nax",
 "m_q10Settings_q10_nax",
 "m_rateScale_nax",
 "m_alpha_nax",
 "m_beta_nax",
 "m_fcond_nax",
 "m_inf_nax",
 "m_tauUnscaled_nax",
 "m_tau_nax",
 "h_forwardRate_V_nax",
 "h_forwardRate_r_nax",
 "h_reverseRate_V_nax",
 "h_reverseRate_r_nax",
 "h_steadyState_x_nax",
 "h_timeCourse_V_nax",
 "h_timeCourse_ALPHA_nax",
 "h_timeCourse_BETA_nax",
 "h_timeCourse_t_nax",
 "h_q10Settings_q10_nax",
 "h_rateScale_nax",
 "h_alpha_nax",
 "h_beta_nax",
 "h_inf_nax",
 "h_tauUnscaled_nax",
 "h_tau_nax",
 "h_fcond_nax",
 "conductanceScale_nax",
 "fopen0_nax",
 "fopen_nax",
 "g_nax",
 0,
 "m_q_nax",
 "h_q_nax",
 0,
 0};
 static Symbol* _na_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 93, _prop);
 	/*initialize range parameters*/
 	gmax = 0;
 	conductance = 1e-05;
 	m_instances = 3;
 	m_forwardRate_TIME_SCALE = 1;
 	m_forwardRate_VOLT_SCALE = 1;
 	m_forwardRate_Ra = 0.4;
 	m_forwardRate_qa = 7.2;
 	m_forwardRate_tha = -30;
 	m_forwardRate_sh = 0;
 	m_reverseRate_TIME_SCALE = 1;
 	m_reverseRate_VOLT_SCALE = 1;
 	m_reverseRate_Rb = 0.124;
 	m_reverseRate_qa = 7.2;
 	m_reverseRate_tha = -30;
 	m_reverseRate_sh = 0;
 	m_timeCourse_TIME_SCALE = 1;
 	m_timeCourse_VOLT_SCALE = 1;
 	m_timeCourse_mmin = 0.02;
 	m_q10Settings_q10Factor = 2;
 	m_q10Settings_experimentalTemp = 297.15;
 	m_q10Settings_TENDEGREES = 10;
 	h_instances = 1;
 	h_forwardRate_TIME_SCALE = 1;
 	h_forwardRate_VOLT_SCALE = 1;
 	h_forwardRate_Rd = 0.03;
 	h_forwardRate_qd = 1.5;
 	h_forwardRate_thi1 = -45;
 	h_forwardRate_sh = 0;
 	h_reverseRate_TIME_SCALE = 1;
 	h_reverseRate_VOLT_SCALE = 1;
 	h_reverseRate_Rg = 0.01;
 	h_reverseRate_qg = 1.5;
 	h_reverseRate_thi2 = -45;
 	h_reverseRate_sh = 0;
 	h_steadyState_rate = 1;
 	h_steadyState_midpoint = -50;
 	h_steadyState_scale = -4;
 	h_timeCourse_TIME_SCALE = 1;
 	h_timeCourse_VOLT_SCALE = 1;
 	h_timeCourse_hmin = 0.5;
 	h_q10Settings_q10Factor = 2;
 	h_q10Settings_experimentalTemp = 297.15;
 	h_q10Settings_TENDEGREES = 10;
 	_prop->param = _p;
 	_prop->param_size = 93;
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

 void _nax_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("na", 1.0);
 	_na_sym = hoc_lookup("na_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 93, 3);
  hoc_register_dparam_semantics(_mechtype, 0, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 nax /home/gluciferd/Macaque_auditory_thalamocortical_model_data/NeuroML2/channels/channels_summary/IT2/nax.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "Mod file for component: Component(id=nax type=ionChannelHH)";

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
   m_forwardRate_V = v / m_forwardRate_VOLT_SCALE ;
   if ( ( m_forwardRate_V - ( m_forwardRate_tha + m_forwardRate_sh ) ) < 1.e-06  && ( m_forwardRate_V - ( m_forwardRate_tha + m_forwardRate_sh ) ) > - 1.e-06 ) {
     m_forwardRate_r = m_forwardRate_Ra * m_forwardRate_qa / m_forwardRate_TIME_SCALE ;
     }
   else {
     m_forwardRate_r = m_forwardRate_Ra * ( m_forwardRate_V - ( m_forwardRate_tha + m_forwardRate_sh ) ) / ( 1.0 - exp ( - ( m_forwardRate_V - ( m_forwardRate_tha + m_forwardRate_sh ) ) / m_forwardRate_qa ) ) / m_forwardRate_TIME_SCALE ;
     }
   m_reverseRate_V = v / m_reverseRate_VOLT_SCALE ;
   if ( ( - m_reverseRate_V + m_reverseRate_tha + m_reverseRate_sh ) < 1.e-06  && ( - m_reverseRate_V + m_reverseRate_tha + m_reverseRate_sh ) > - 1.e-06 ) {
     m_reverseRate_r = m_reverseRate_Rb * m_reverseRate_qa / m_reverseRate_TIME_SCALE ;
     }
   else {
     m_reverseRate_r = m_reverseRate_Rb * ( - m_reverseRate_V + m_reverseRate_tha + m_reverseRate_sh ) / ( 1.0 - exp ( - ( - m_reverseRate_V + m_reverseRate_tha + m_reverseRate_sh ) / m_reverseRate_qa ) ) / m_reverseRate_TIME_SCALE ;
     }
   m_timeCourse_V = v / m_timeCourse_VOLT_SCALE ;
   m_timeCourse_ALPHA = m_alpha * m_timeCourse_TIME_SCALE ;
   m_timeCourse_BETA = m_beta * m_timeCourse_TIME_SCALE ;
   if ( ( m_timeCourse_ALPHA + m_timeCourse_BETA )  == 0.0 ) {
     m_timeCourse_t = 0.0 * m_timeCourse_TIME_SCALE ;
     }
   else if ( 1.0 / ( m_timeCourse_ALPHA + m_timeCourse_BETA ) < m_timeCourse_mmin ) {
     m_timeCourse_t = m_timeCourse_mmin * m_timeCourse_TIME_SCALE ;
     }
   else {
     m_timeCourse_t = 1.0 / ( m_timeCourse_ALPHA + m_timeCourse_BETA ) * m_timeCourse_TIME_SCALE ;
     }
   m_q10Settings_q10 = pow( m_q10Settings_q10Factor , ( ( temperature - m_q10Settings_experimentalTemp ) / m_q10Settings_TENDEGREES ) ) ;
   m_rateScale = m_q10Settings_q10 ;
   m_alpha = m_forwardRate_r ;
   m_beta = m_reverseRate_r ;
   m_fcond = pow( m_q , m_instances ) ;
   m_inf = m_alpha / ( m_alpha + m_beta ) ;
   m_tauUnscaled = m_timeCourse_t ;
   m_tau = m_tauUnscaled / m_rateScale ;
   h_forwardRate_V = v / h_forwardRate_VOLT_SCALE ;
   if ( ( h_forwardRate_V - ( h_forwardRate_thi1 + h_forwardRate_sh ) ) < 1.e-06  && ( h_forwardRate_V - ( h_forwardRate_thi1 + h_forwardRate_sh ) ) > - 1.e-06 ) {
     h_forwardRate_r = h_forwardRate_Rd * h_forwardRate_qd / h_forwardRate_TIME_SCALE ;
     }
   else {
     h_forwardRate_r = h_forwardRate_Rd * ( h_forwardRate_V - ( h_forwardRate_thi1 + h_forwardRate_sh ) ) / ( 1.0 - exp ( - ( h_forwardRate_V - ( h_forwardRate_thi1 + h_forwardRate_sh ) ) / h_forwardRate_qd ) ) / h_forwardRate_TIME_SCALE ;
     }
   h_reverseRate_V = v / h_reverseRate_VOLT_SCALE ;
   if ( ( - h_reverseRate_V + h_reverseRate_thi2 + h_reverseRate_sh ) < 1.e-06  && ( - h_reverseRate_V + h_reverseRate_thi2 + h_reverseRate_sh ) > - 1.e-06 ) {
     h_reverseRate_r = h_reverseRate_Rg * h_reverseRate_qg / h_reverseRate_TIME_SCALE ;
     }
   else {
     h_reverseRate_r = h_reverseRate_Rg * ( - h_reverseRate_V + h_reverseRate_thi2 + h_reverseRate_sh ) / ( 1.0 - exp ( - ( - h_reverseRate_V + h_reverseRate_thi2 + h_reverseRate_sh ) / h_reverseRate_qg ) ) / h_reverseRate_TIME_SCALE ;
     }
   h_steadyState_x = h_steadyState_rate / ( 1.0 + exp ( 0.0 - ( v - h_steadyState_midpoint ) / h_steadyState_scale ) ) ;
   h_timeCourse_V = v / h_timeCourse_VOLT_SCALE ;
   h_timeCourse_ALPHA = h_alpha * h_timeCourse_TIME_SCALE ;
   h_timeCourse_BETA = h_beta * h_timeCourse_TIME_SCALE ;
   if ( ( h_timeCourse_ALPHA + h_timeCourse_BETA )  == 0.0 ) {
     h_timeCourse_t = 0.0 * h_timeCourse_TIME_SCALE ;
     }
   else if ( 1.0 / ( h_timeCourse_ALPHA + h_timeCourse_BETA ) < h_timeCourse_hmin ) {
     h_timeCourse_t = h_timeCourse_hmin * h_timeCourse_TIME_SCALE ;
     }
   else {
     h_timeCourse_t = 1.0 / ( h_timeCourse_ALPHA + h_timeCourse_BETA ) * h_timeCourse_TIME_SCALE ;
     }
   h_q10Settings_q10 = pow( h_q10Settings_q10Factor , ( ( temperature - h_q10Settings_experimentalTemp ) / h_q10Settings_TENDEGREES ) ) ;
   h_rateScale = h_q10Settings_q10 ;
   h_alpha = h_forwardRate_r ;
   h_beta = h_reverseRate_r ;
   h_inf = h_steadyState_x ;
   h_tauUnscaled = h_timeCourse_t ;
   h_tau = h_tauUnscaled / h_rateScale ;
   h_fcond = pow( h_q , h_instances ) ;
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
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_na_sym, _ppvar, 0, 3);
   nrn_update_ion_pointer(_na_sym, _ppvar, 1, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
  h_q = h_q0;
  m_q = m_q0;
 {
   ena = 42.0 ;
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
 initmodel(_p, _ppvar, _thread, _nt);
 }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   conductanceScale = 1.0 ;
   fopen0 = m_fcond * h_fcond ;
   fopen = conductanceScale * fopen0 ;
   g = conductance * fopen ;
   gion = gmax * fopen ;
   ina = gion * ( v - ena ) ;
   i__nax = - 1.0 * ina ;
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
 _slist1[0] = m_q_columnindex;  _dlist1[0] = Dm_q_columnindex;
 _slist1[1] = h_q_columnindex;  _dlist1[1] = Dh_q_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/gluciferd/Macaque_auditory_thalamocortical_model_data/NeuroML2/channels/channels_summary/IT2/nax.mod";
static const char* nmodl_file_text = 
  "TITLE Mod file for component: Component(id=nax type=ionChannelHH)\n"
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
  "    SUFFIX nax\n"
  "    USEION na WRITE ina VALENCE 1 ? Assuming valence = 1; TODO check this!!\n"
  "    \n"
  "    RANGE gion\n"
  "    RANGE i__nax : a copy of the variable for current which makes it easier to access from outside the mod file\n"
  "    RANGE gmax                              : Will be changed when ion channel mechanism placed on cell!\n"
  "    RANGE conductance                       : parameter\n"
  "    RANGE g                                 : exposure\n"
  "    RANGE fopen                             : exposure\n"
  "    RANGE m_instances                       : parameter\n"
  "    RANGE m_alpha                           : exposure\n"
  "    RANGE m_beta                            : exposure\n"
  "    RANGE m_tau                             : exposure\n"
  "    RANGE m_inf                             : exposure\n"
  "    RANGE m_rateScale                       : exposure\n"
  "    RANGE m_fcond                           : exposure\n"
  "    RANGE m_forwardRate_TIME_SCALE          : parameter\n"
  "    RANGE m_forwardRate_VOLT_SCALE          : parameter\n"
  "    RANGE m_forwardRate_Ra                  : parameter\n"
  "    RANGE m_forwardRate_qa                  : parameter\n"
  "    RANGE m_forwardRate_tha                 : parameter\n"
  "    RANGE m_forwardRate_sh                  : parameter\n"
  "    RANGE m_forwardRate_r                   : exposure\n"
  "    RANGE m_reverseRate_TIME_SCALE          : parameter\n"
  "    RANGE m_reverseRate_VOLT_SCALE          : parameter\n"
  "    RANGE m_reverseRate_Rb                  : parameter\n"
  "    RANGE m_reverseRate_qa                  : parameter\n"
  "    RANGE m_reverseRate_tha                 : parameter\n"
  "    RANGE m_reverseRate_sh                  : parameter\n"
  "    RANGE m_reverseRate_r                   : exposure\n"
  "    RANGE m_timeCourse_TIME_SCALE           : parameter\n"
  "    RANGE m_timeCourse_VOLT_SCALE           : parameter\n"
  "    RANGE m_timeCourse_mmin                 : parameter\n"
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
  "    RANGE h_forwardRate_TIME_SCALE          : parameter\n"
  "    RANGE h_forwardRate_VOLT_SCALE          : parameter\n"
  "    RANGE h_forwardRate_Rd                  : parameter\n"
  "    RANGE h_forwardRate_qd                  : parameter\n"
  "    RANGE h_forwardRate_thi1                : parameter\n"
  "    RANGE h_forwardRate_sh                  : parameter\n"
  "    RANGE h_forwardRate_r                   : exposure\n"
  "    RANGE h_reverseRate_TIME_SCALE          : parameter\n"
  "    RANGE h_reverseRate_VOLT_SCALE          : parameter\n"
  "    RANGE h_reverseRate_Rg                  : parameter\n"
  "    RANGE h_reverseRate_qg                  : parameter\n"
  "    RANGE h_reverseRate_thi2                : parameter\n"
  "    RANGE h_reverseRate_sh                  : parameter\n"
  "    RANGE h_reverseRate_r                   : exposure\n"
  "    RANGE h_steadyState_rate                : parameter\n"
  "    RANGE h_steadyState_midpoint            : parameter\n"
  "    RANGE h_steadyState_scale               : parameter\n"
  "    RANGE h_steadyState_x                   : exposure\n"
  "    RANGE h_timeCourse_TIME_SCALE           : parameter\n"
  "    RANGE h_timeCourse_VOLT_SCALE           : parameter\n"
  "    RANGE h_timeCourse_hmin                 : parameter\n"
  "    RANGE h_timeCourse_t                    : exposure\n"
  "    RANGE h_q10Settings_q10Factor           : parameter\n"
  "    RANGE h_q10Settings_experimentalTemp    : parameter\n"
  "    RANGE h_q10Settings_TENDEGREES          : parameter\n"
  "    RANGE h_q10Settings_q10                 : exposure\n"
  "    RANGE m_forwardRate_V                   : derived variable\n"
  "    RANGE m_reverseRate_V                   : derived variable\n"
  "    RANGE m_timeCourse_V                    : derived variable\n"
  "    RANGE m_timeCourse_ALPHA                : derived variable\n"
  "    RANGE m_timeCourse_BETA                 : derived variable\n"
  "    RANGE m_tauUnscaled                     : derived variable\n"
  "    RANGE h_forwardRate_V                   : derived variable\n"
  "    RANGE h_reverseRate_V                   : derived variable\n"
  "    RANGE h_timeCourse_V                    : derived variable\n"
  "    RANGE h_timeCourse_ALPHA                : derived variable\n"
  "    RANGE h_timeCourse_BETA                 : derived variable\n"
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
  "    m_instances = 3                        : was: 3.0 (none)\n"
  "    m_forwardRate_TIME_SCALE = 1 (ms)      : was: 0.001 (time)\n"
  "    m_forwardRate_VOLT_SCALE = 1 (mV)      : was: 0.001 (voltage)\n"
  "    m_forwardRate_Ra = 0.4                 : was: 0.4 (none)\n"
  "    m_forwardRate_qa = 7.2                 : was: 7.2 (none)\n"
  "    m_forwardRate_tha = -30                : was: -30.0 (none)\n"
  "    m_forwardRate_sh = 0                   : was: 0.0 (none)\n"
  "    m_reverseRate_TIME_SCALE = 1 (ms)      : was: 0.001 (time)\n"
  "    m_reverseRate_VOLT_SCALE = 1 (mV)      : was: 0.001 (voltage)\n"
  "    m_reverseRate_Rb = 0.124               : was: 0.124 (none)\n"
  "    m_reverseRate_qa = 7.2                 : was: 7.2 (none)\n"
  "    m_reverseRate_tha = -30                : was: -30.0 (none)\n"
  "    m_reverseRate_sh = 0                   : was: 0.0 (none)\n"
  "    m_timeCourse_TIME_SCALE = 1 (ms)       : was: 0.001 (time)\n"
  "    m_timeCourse_VOLT_SCALE = 1 (mV)       : was: 0.001 (voltage)\n"
  "    m_timeCourse_mmin = 0.02               : was: 0.02 (none)\n"
  "    m_q10Settings_q10Factor = 2            : was: 2.0 (none)\n"
  "    m_q10Settings_experimentalTemp = 297.15 (K): was: 297.15 (temperature)\n"
  "    m_q10Settings_TENDEGREES = 10 (K)      : was: 10.0 (temperature)\n"
  "    h_instances = 1                        : was: 1.0 (none)\n"
  "    h_forwardRate_TIME_SCALE = 1 (ms)      : was: 0.001 (time)\n"
  "    h_forwardRate_VOLT_SCALE = 1 (mV)      : was: 0.001 (voltage)\n"
  "    h_forwardRate_Rd = 0.03                : was: 0.03 (none)\n"
  "    h_forwardRate_qd = 1.5                 : was: 1.5 (none)\n"
  "    h_forwardRate_thi1 = -45               : was: -45.0 (none)\n"
  "    h_forwardRate_sh = 0                   : was: 0.0 (none)\n"
  "    h_reverseRate_TIME_SCALE = 1 (ms)      : was: 0.001 (time)\n"
  "    h_reverseRate_VOLT_SCALE = 1 (mV)      : was: 0.001 (voltage)\n"
  "    h_reverseRate_Rg = 0.01                : was: 0.01 (none)\n"
  "    h_reverseRate_qg = 1.5                 : was: 1.5 (none)\n"
  "    h_reverseRate_thi2 = -45               : was: -45.0 (none)\n"
  "    h_reverseRate_sh = 0                   : was: 0.0 (none)\n"
  "    h_steadyState_rate = 1                 : was: 1.0 (none)\n"
  "    h_steadyState_midpoint = -50 (mV)      : was: -0.05 (voltage)\n"
  "    h_steadyState_scale = -4 (mV)          : was: -0.004 (voltage)\n"
  "    h_timeCourse_TIME_SCALE = 1 (ms)       : was: 0.001 (time)\n"
  "    h_timeCourse_VOLT_SCALE = 1 (mV)       : was: 0.001 (voltage)\n"
  "    h_timeCourse_hmin = 0.5                : was: 0.5 (none)\n"
  "    h_q10Settings_q10Factor = 2            : was: 2.0 (none)\n"
  "    h_q10Settings_experimentalTemp = 297.15 (K): was: 297.15 (temperature)\n"
  "    h_q10Settings_TENDEGREES = 10 (K)      : was: 10.0 (temperature)\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "    \n"
  "    gion   (S/cm2)                          : Transient conductance density of the channel? Standard Assigned variables with ionChannel\n"
  "    v (mV)\n"
  "    celsius (degC)\n"
  "    temperature (K)\n"
  "    ena (mV)\n"
  "    ina (mA/cm2)\n"
  "    i__nax (mA/cm2)\n"
  "    \n"
  "    m_forwardRate_V                         : derived variable\n"
  "    \n"
  "    m_forwardRate_r (kHz)                   : conditional derived var...\n"
  "    m_reverseRate_V                         : derived variable\n"
  "    \n"
  "    m_reverseRate_r (kHz)                   : conditional derived var...\n"
  "    m_timeCourse_V                          : derived variable\n"
  "    m_timeCourse_ALPHA                      : derived variable\n"
  "    m_timeCourse_BETA                       : derived variable\n"
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
  "    h_forwardRate_V                         : derived variable\n"
  "    \n"
  "    h_forwardRate_r (kHz)                   : conditional derived var...\n"
  "    h_reverseRate_V                         : derived variable\n"
  "    \n"
  "    h_reverseRate_r (kHz)                   : conditional derived var...\n"
  "    h_steadyState_x                         : derived variable\n"
  "    h_timeCourse_V                          : derived variable\n"
  "    h_timeCourse_ALPHA                      : derived variable\n"
  "    h_timeCourse_BETA                       : derived variable\n"
  "    \n"
  "    h_timeCourse_t (ms)                     : conditional derived var...\n"
  "    h_q10Settings_q10                       : derived variable\n"
  "    h_rateScale                             : derived variable\n"
  "    h_alpha (kHz)                           : derived variable\n"
  "    h_beta (kHz)                            : derived variable\n"
  "    h_inf                                   : derived variable\n"
  "    h_tauUnscaled (ms)                      : derived variable\n"
  "    h_tau (ms)                              : derived variable\n"
  "    h_fcond                                 : derived variable\n"
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
  "    ena = 42.0\n"
  "    \n"
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
  "    ? DerivedVariable is based on path: conductanceScaling[*]/factor, on: Component(id=nax type=ionChannelHH), from conductanceScaling; null\n"
  "    ? Path not present in component, using factor: 1\n"
  "    \n"
  "    conductanceScale = 1 \n"
  "    \n"
  "    ? DerivedVariable is based on path: gates[*]/fcond, on: Component(id=nax type=ionChannelHH), from gates; Component(id=m type=gateHHratesTau)\n"
  "    ? multiply applied to all instances of fcond in: <gates> ([Component(id=m type=gateHHratesTau), Component(id=h type=gateHHratesTauInf)]))\n"
  "    fopen0 = m_fcond * h_fcond ? path based, prefix = \n"
  "    \n"
  "    fopen = conductanceScale  *  fopen0 ? evaluable\n"
  "    g = conductance  *  fopen ? evaluable\n"
  "    gion = gmax * fopen \n"
  "    \n"
  "    ina = gion * (v - ena)\n"
  "    i__nax =  -1 * ina : set this variable to the current also - note -1 as channel current convention for LEMS used!\n"
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
  "    \n"
  "    m_forwardRate_V = v /  m_forwardRate_VOLT_SCALE ? evaluable\n"
  "    if (( m_forwardRate_V  - ( m_forwardRate_tha  +  m_forwardRate_sh )) < 1.e-06 && ( m_forwardRate_V  - ( m_forwardRate_tha  +  m_forwardRate_sh )) > -1.e-06)  { \n"
  "        m_forwardRate_r = m_forwardRate_Ra  *  m_forwardRate_qa   /  m_forwardRate_TIME_SCALE ? evaluable cdv\n"
  "    } else  { \n"
  "        m_forwardRate_r = m_forwardRate_Ra  * ( m_forwardRate_V  - ( m_forwardRate_tha  +  m_forwardRate_sh )) / (1 - exp(-( m_forwardRate_V  - ( m_forwardRate_tha  +  m_forwardRate_sh ))/ m_forwardRate_qa ))  /  m_forwardRate_TIME_SCALE ? evaluable cdv\n"
  "    }\n"
  "    \n"
  "    m_reverseRate_V = v /  m_reverseRate_VOLT_SCALE ? evaluable\n"
  "    if ((- m_reverseRate_V  +  m_reverseRate_tha  +  m_reverseRate_sh ) < 1.e-06 && (- m_reverseRate_V  +  m_reverseRate_tha  +  m_reverseRate_sh ) > -1.e-06)  { \n"
  "        m_reverseRate_r = m_reverseRate_Rb  *  m_reverseRate_qa  /  m_reverseRate_TIME_SCALE ? evaluable cdv\n"
  "    } else  { \n"
  "        m_reverseRate_r = m_reverseRate_Rb  * (- m_reverseRate_V  +  m_reverseRate_tha  +  m_reverseRate_sh ) / (1 - exp(-(- m_reverseRate_V  +  m_reverseRate_tha  +  m_reverseRate_sh )/ m_reverseRate_qa )) /  m_reverseRate_TIME_SCALE ? evaluable cdv\n"
  "    }\n"
  "    \n"
  "    m_timeCourse_V = v /  m_timeCourse_VOLT_SCALE ? evaluable\n"
  "    m_timeCourse_ALPHA = m_alpha  *  m_timeCourse_TIME_SCALE ? evaluable\n"
  "    m_timeCourse_BETA = m_beta  *  m_timeCourse_TIME_SCALE ? evaluable\n"
  "    if (( m_timeCourse_ALPHA  +  m_timeCourse_BETA ) == 0)  { \n"
  "        m_timeCourse_t = 0.0  *  m_timeCourse_TIME_SCALE ? evaluable cdv\n"
  "    } else if (1/( m_timeCourse_ALPHA + m_timeCourse_BETA ) <  m_timeCourse_mmin)  { \n"
  "        m_timeCourse_t = m_timeCourse_mmin  *  m_timeCourse_TIME_SCALE ? evaluable cdv\n"
  "    } else  { \n"
  "        m_timeCourse_t = 1/( m_timeCourse_ALPHA + m_timeCourse_BETA ) *  m_timeCourse_TIME_SCALE ? evaluable cdv\n"
  "    }\n"
  "    \n"
  "    m_q10Settings_q10 = m_q10Settings_q10Factor ^((temperature -  m_q10Settings_experimentalTemp )/ m_q10Settings_TENDEGREES ) ? evaluable\n"
  "    ? DerivedVariable is based on path: q10Settings[*]/q10, on: Component(id=m type=gateHHratesTau), from q10Settings; Component(id=null type=q10ExpTemp)\n"
  "    ? multiply applied to all instances of q10 in: <q10Settings> ([Component(id=null type=q10ExpTemp)]))\n"
  "    m_rateScale = m_q10Settings_q10 ? path based, prefix = m_\n"
  "    \n"
  "    ? DerivedVariable is based on path: forwardRate/r, on: Component(id=m type=gateHHratesTau), from forwardRate; Component(id=null type=nax_m_alpha_rate)\n"
  "    m_alpha = m_forwardRate_r ? path based, prefix = m_\n"
  "    \n"
  "    ? DerivedVariable is based on path: reverseRate/r, on: Component(id=m type=gateHHratesTau), from reverseRate; Component(id=null type=nax_m_beta_rate)\n"
  "    m_beta = m_reverseRate_r ? path based, prefix = m_\n"
  "    \n"
  "    m_fcond = m_q ^ m_instances ? evaluable\n"
  "    m_inf = m_alpha /( m_alpha + m_beta ) ? evaluable\n"
  "    ? DerivedVariable is based on path: timeCourse/t, on: Component(id=m type=gateHHratesTau), from timeCourse; Component(id=null type=nax_m_tau)\n"
  "    m_tauUnscaled = m_timeCourse_t ? path based, prefix = m_\n"
  "    \n"
  "    m_tau = m_tauUnscaled  /  m_rateScale ? evaluable\n"
  "    h_forwardRate_V = v /  h_forwardRate_VOLT_SCALE ? evaluable\n"
  "    if (( h_forwardRate_V  - ( h_forwardRate_thi1  +  h_forwardRate_sh )) < 1.e-06 && ( h_forwardRate_V  - ( h_forwardRate_thi1  +  h_forwardRate_sh )) > -1.e-06)  { \n"
  "        h_forwardRate_r = h_forwardRate_Rd  *  h_forwardRate_qd   /  h_forwardRate_TIME_SCALE ? evaluable cdv\n"
  "    } else  { \n"
  "        h_forwardRate_r = h_forwardRate_Rd  * ( h_forwardRate_V  - ( h_forwardRate_thi1  +  h_forwardRate_sh )) / (1 - exp(-( h_forwardRate_V  - ( h_forwardRate_thi1  +  h_forwardRate_sh ))/ h_forwardRate_qd )) /  h_forwardRate_TIME_SCALE ? evaluable cdv\n"
  "    }\n"
  "    \n"
  "    h_reverseRate_V = v /  h_reverseRate_VOLT_SCALE ? evaluable\n"
  "    if ((- h_reverseRate_V  +  h_reverseRate_thi2  +  h_reverseRate_sh ) < 1.e-06 && (- h_reverseRate_V  +  h_reverseRate_thi2  +  h_reverseRate_sh ) > -1.e-06)  { \n"
  "        h_reverseRate_r = h_reverseRate_Rg  *  h_reverseRate_qg   /  h_reverseRate_TIME_SCALE ? evaluable cdv\n"
  "    } else  { \n"
  "        h_reverseRate_r = h_reverseRate_Rg  * (- h_reverseRate_V  +  h_reverseRate_thi2  +  h_reverseRate_sh ) / (1 - exp(-(- h_reverseRate_V  +  h_reverseRate_thi2  +  h_reverseRate_sh )/ h_reverseRate_qg ))  / h_reverseRate_TIME_SCALE ? evaluable cdv\n"
  "    }\n"
  "    \n"
  "    h_steadyState_x = h_steadyState_rate  / (1 + exp(0 - (v -  h_steadyState_midpoint )/ h_steadyState_scale )) ? evaluable\n"
  "    h_timeCourse_V = v /  h_timeCourse_VOLT_SCALE ? evaluable\n"
  "    h_timeCourse_ALPHA = h_alpha  *  h_timeCourse_TIME_SCALE ? evaluable\n"
  "    h_timeCourse_BETA = h_beta  *  h_timeCourse_TIME_SCALE ? evaluable\n"
  "    if (( h_timeCourse_ALPHA  +  h_timeCourse_BETA ) == 0)  { \n"
  "        h_timeCourse_t = 0.0  *  h_timeCourse_TIME_SCALE ? evaluable cdv\n"
  "    } else if (1/( h_timeCourse_ALPHA + h_timeCourse_BETA ) <  h_timeCourse_hmin)  { \n"
  "        h_timeCourse_t = h_timeCourse_hmin  *  h_timeCourse_TIME_SCALE ? evaluable cdv\n"
  "    } else  { \n"
  "        h_timeCourse_t = 1/( h_timeCourse_ALPHA + h_timeCourse_BETA ) *  h_timeCourse_TIME_SCALE ? evaluable cdv\n"
  "    }\n"
  "    \n"
  "    h_q10Settings_q10 = h_q10Settings_q10Factor ^((temperature -  h_q10Settings_experimentalTemp )/ h_q10Settings_TENDEGREES ) ? evaluable\n"
  "    ? DerivedVariable is based on path: q10Settings[*]/q10, on: Component(id=h type=gateHHratesTauInf), from q10Settings; Component(id=null type=q10ExpTemp)\n"
  "    ? multiply applied to all instances of q10 in: <q10Settings> ([Component(id=null type=q10ExpTemp)]))\n"
  "    h_rateScale = h_q10Settings_q10 ? path based, prefix = h_\n"
  "    \n"
  "    ? DerivedVariable is based on path: forwardRate/r, on: Component(id=h type=gateHHratesTauInf), from forwardRate; Component(id=null type=nax_h_alpha_rate)\n"
  "    h_alpha = h_forwardRate_r ? path based, prefix = h_\n"
  "    \n"
  "    ? DerivedVariable is based on path: reverseRate/r, on: Component(id=h type=gateHHratesTauInf), from reverseRate; Component(id=null type=nax_h_beta_rate)\n"
  "    h_beta = h_reverseRate_r ? path based, prefix = h_\n"
  "    \n"
  "    ? DerivedVariable is based on path: steadyState/x, on: Component(id=h type=gateHHratesTauInf), from steadyState; Component(id=null type=HHSigmoidVariable)\n"
  "    h_inf = h_steadyState_x ? path based, prefix = h_\n"
  "    \n"
  "    ? DerivedVariable is based on path: timeCourse/t, on: Component(id=h type=gateHHratesTauInf), from timeCourse; Component(id=null type=nax_h_tau)\n"
  "    h_tauUnscaled = h_timeCourse_t ? path based, prefix = h_\n"
  "    \n"
  "    h_tau = h_tauUnscaled  /  h_rateScale ? evaluable\n"
  "    h_fcond = h_q ^ h_instances ? evaluable\n"
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
  "     \n"
  "    \n"
  "}\n"
  "\n"
  ;
#endif
