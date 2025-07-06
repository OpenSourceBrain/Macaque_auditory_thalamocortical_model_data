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
 
#define nrn_init _nrn_init__Cad_int
#define _nrn_initial _nrn_initial__Cad_int
#define nrn_cur _nrn_cur__Cad_int
#define _nrn_current _nrn_current__Cad_int
#define nrn_jacob _nrn_jacob__Cad_int
#define nrn_state _nrn_state__Cad_int
#define _net_receive _net_receive__Cad_int 
#define state state__Cad_int 
 
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
#define depth _p[0]
#define depth_columnindex 0
#define taur _p[1]
#define taur_columnindex 1
#define taur2 _p[2]
#define taur2_columnindex 2
#define Cainf _p[3]
#define Cainf_columnindex 3
#define Cainf2 _p[4]
#define Cainf2_columnindex 4
#define Cai0 _p[5]
#define Cai0_columnindex 5
#define kt _p[6]
#define kt_columnindex 6
#define kt2 _p[7]
#define kt2_columnindex 7
#define kd _p[8]
#define kd_columnindex 8
#define k _p[9]
#define k_columnindex 9
#define drive_channel _p[10]
#define drive_channel_columnindex 10
#define drive_pump _p[11]
#define drive_pump_columnindex 11
#define drive_pump2 _p[12]
#define drive_pump2_columnindex 12
#define iCa _p[13]
#define iCa_columnindex 13
#define Cai _p[14]
#define Cai_columnindex 14
#define DCai _p[15]
#define DCai_columnindex 15
#define v _p[16]
#define v_columnindex 16
#define _g _p[17]
#define _g_columnindex 17
#define _ion_iCa	*_ppvar[0]._pval
#define _ion_Cai	*_ppvar[1]._pval
#define _style_Ca	*((int*)_ppvar[2]._pvoid)
 
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
 "setdata_Cad_int", _hoc_setdata,
 0, 0
};
 /* declare global and static user variables */
#define kd2 kd2_Cad_int
 double kd2 = 1e-07;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "kd2_Cad_int", "mM",
 "depth_Cad_int", "um",
 "taur_Cad_int", "ms",
 "taur2_Cad_int", "ms",
 "Cainf_Cad_int", "mM",
 "Cainf2_Cad_int", "mM",
 "Cai0_Cad_int", "mM",
 "kt_Cad_int", "mM/ms",
 "kt2_Cad_int", "mM/ms",
 "kd_Cad_int", "mM",
 "drive_channel_Cad_int", "mM/ms",
 "drive_pump_Cad_int", "mM/ms",
 "drive_pump2_Cad_int", "mM/ms",
 0,0
};
 static double delta_t = 1;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "kd2_Cad_int", &kd2_Cad_int,
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
"Cad_int",
 "depth_Cad_int",
 "taur_Cad_int",
 "taur2_Cad_int",
 "Cainf_Cad_int",
 "Cainf2_Cad_int",
 "Cai0_Cad_int",
 "kt_Cad_int",
 "kt2_Cad_int",
 "kd_Cad_int",
 "k_Cad_int",
 0,
 "drive_channel_Cad_int",
 "drive_pump_Cad_int",
 "drive_pump2_Cad_int",
 0,
 0,
 0};
 static Symbol* _Ca_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 18, _prop);
 	/*initialize range parameters*/
 	depth = 0.1;
 	taur = 700;
 	taur2 = 70;
 	Cainf = 1e-08;
 	Cainf2 = 5e-05;
 	Cai0 = 5e-05;
 	kt = 1;
 	kt2 = 1;
 	kd = 0.0005;
 	k = 1;
 	_prop->param = _p;
 	_prop->param_size = 18;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_Ca_sym);
 nrn_check_conc_write(_prop, prop_ion, 1);
 nrn_promote(prop_ion, 3, 0);
 	_ppvar[0]._pval = &prop_ion->param[3]; /* iCa */
 	_ppvar[1]._pval = &prop_ion->param[1]; /* Cai */
 	_ppvar[2]._pvoid = (void*)(&(prop_ion->dparam[0]._i)); /* iontype for Ca */
 
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

 void _cp2_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("Ca", 2.0);
 	_Ca_sym = hoc_lookup("Ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 18, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "Ca_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "Ca_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "#Ca_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	nrn_writes_conc(_mechtype, 0);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Cad_int /home/gluciferd/Macaque_auditory_thalamocortical_model_data/NeuroML2/compare_tmp/IT2/mod/cp2.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 96489;
static int _reset;
static char *modelname = "decay of internal calcium concentration";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[1], _dlist1[1];
 static int state(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset = 0; {
   drive_channel = - ( k * 10000.0 ) * iCa / ( 2.0 * FARADAY * depth ) ;
   if ( drive_channel <= 0. ) {
     drive_channel = 0. ;
     }
   drive_pump = - kt * Cai / ( Cai + kd ) ;
   drive_pump2 = - kt2 * Cai / ( Cai + kd2 ) ;
   DCai = drive_channel + drive_pump + drive_pump2 + ( Cainf - Cai ) / taur + ( Cainf2 - Cai ) / taur2 ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
 drive_channel = - ( k * 10000.0 ) * iCa / ( 2.0 * FARADAY * depth ) ;
 if ( drive_channel <= 0. ) {
   drive_channel = 0. ;
   }
 drive_pump = - kt * Cai / ( Cai + kd ) ;
 drive_pump2 = - kt2 * Cai / ( Cai + kd2 ) ;
 DCai = DCai  / (1. - dt*( ( ( ( - 1.0 ) ) ) / taur + ( ( ( - 1.0 ) ) ) / taur2 )) ;
  return 0;
}
 /*END CVODE*/
 static int state (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) { {
   drive_channel = - ( k * 10000.0 ) * iCa / ( 2.0 * FARADAY * depth ) ;
   if ( drive_channel <= 0. ) {
     drive_channel = 0. ;
     }
   drive_pump = - kt * Cai / ( Cai + kd ) ;
   drive_pump2 = - kt2 * Cai / ( Cai + kd2 ) ;
    Cai = Cai + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / taur + ( ( ( - 1.0 ) ) ) / taur2)))*(- ( drive_channel + drive_pump + drive_pump2 + ( ( Cainf ) ) / taur + ( ( Cainf2 ) ) / taur2 ) / ( ( ( ( - 1.0 ) ) ) / taur + ( ( ( - 1.0 ) ) ) / taur2 ) - Cai) ;
   }
  return 0;
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
  iCa = _ion_iCa;
  Cai = _ion_Cai;
  Cai = _ion_Cai;
     _ode_spec1 (_p, _ppvar, _thread, _nt);
  _ion_Cai = Cai;
 }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 1; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 	_pv[0] = &(_ion_Cai);
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
  iCa = _ion_iCa;
  Cai = _ion_Cai;
  Cai = _ion_Cai;
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_Ca_sym, _ppvar, 0, 3);
   nrn_update_ion_pointer(_Ca_sym, _ppvar, 1, 1);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
 {
   Cai = Cai0 ;
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
  iCa = _ion_iCa;
  Cai = _ion_Cai;
  Cai = _ion_Cai;
 initmodel(_p, _ppvar, _thread, _nt);
  _ion_Cai = Cai;
  nrn_wrote_conc(_Ca_sym, (&(_ion_Cai)) - 1, _style_Ca);
}
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{
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
  iCa = _ion_iCa;
  Cai = _ion_Cai;
  Cai = _ion_Cai;
 {   state(_p, _ppvar, _thread, _nt);
  } {
   }
  _ion_Cai = Cai;
}}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = Cai_columnindex;  _dlist1[0] = DCai_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/gluciferd/Macaque_auditory_thalamocortical_model_data/NeuroML2/compare_tmp/IT2/mod/cp2.mod";
static const char* nmodl_file_text = 
  ": $Id: cp2.mod,v 1.6 1998/08/16 20:43:54 billl Exp $\n"
  ": EDITED BY ERICA Y GRIFFITH, JAN 2020 FOR USE IN THALAMIC INTERNEURON MODEL\n"
  "TITLE decay of internal calcium concentration\n"
  ":\n"
  ": Internal calcium concentration due to calcium currents and pump.\n"
  ": Differential equations.\n"
  ":\n"
  ": Simple model of ATPase pump with 3 kinetic constants (Destexhe 92)\n"
  ":     Cai + P <-> CaP -> Cao + P  (k1,k2,k3)\n"
  ": A Michaelis-Menten approximation is assumed, which reduces the complexity\n"
  ": of the system to 2 parameters: \n"
  ":       kt = <tot enzyme concentration> * k3  -> TIME CONSTANT OF THE PUMP\n"
  ":	kd = k2/k1 (dissociation constant)    -> EQUILIBRIUM CALCIUM VALUE\n"
  ": The values of these parameters are chosen assuming a high affinity of \n"
  ": the pump to calcium and a low transport capacity (cfr. Blaustein, \n"
  ": TINS, 11: 438, 1988, and references therein).  \n"
  ":\n"
  ": Units checked using \"modlunit\" -> factor 10000 needed in ca entry\n"
  ":\n"
  ": VERSION OF PUMP + DECAY (decay can be viewed as simplified buffering)\n"
  ":\n"
  ": All variables are range variables\n"
  ":\n"
  ":\n"
  ": This mechanism was published in:  Destexhe, A. Babloyantz, A. and \n"
  ": Sejnowski, TJ.  Ionic mechanisms for intrinsic slow oscillations in\n"
  ": thalamic relay neurons. Biophys. J. 65: 1538-1552, 1993)\n"
  ":\n"
  ": Written by Alain Destexhe, Salk Institute, Nov 12, 1992\n"
  ":\n"
  "\n"
  "INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX Cad_int\n"
  "	USEION Ca READ iCa, Cai WRITE Cai VALENCE 2\n"
  "	RANGE depth,kt,kt2,kd,Cainf,taur,k,taur2,Cainf2,Cai0\n"
  "        RANGE drive_channel,drive_pump,drive_pump2\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	(molar) = (1/liter)			: moles do not appear in units\n"
  "	(mM)	= (millimolar)\n"
  "	(um)	= (micron)\n"
  "	(mA)	= (milliamp)\n"
  "	(msM)	= (ms mM)\n"
  "}\n"
  "\n"
  "CONSTANT {\n"
  "	FARADAY = 96489		(coul)		: moles do not appear in units\n"
  ":	FARADAY = 96.489	(k-coul)	: moles do not appear in units\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	depth	= .1	(um)		: depth of shell\n"
  "	taur	= 700	(ms)		: rate of calcium removal\n"
  "	taur2	= 70	(ms)		: rate of calcium removal\n"
  "	Cainf	= 1e-8	(mM)\n"
  "	Cainf2	= 5e-5	(mM)\n"
  "	Cai0  = 5e-5	(mM)\n"
  "	kt	= 1	(mM/ms)		: estimated from k3=.5, tot=.001\n"
  "	kt2	= 1	(mM/ms)		: estimated from k3=.5, tot=.001\n"
  "	kd	= 5e-4	(mM)		: estimated from k2=250, k1=5e5\n"
  "	kd2	= 1e-7	(mM)		: estimated from k2=250, k1=5e5 : NOT RANGE VAR!!!\n"
  "        k       = 1\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	iCa		(mA/cm2)\n"
  "	drive_channel	(mM/ms)\n"
  "	drive_pump	(mM/ms)\n"
  "	drive_pump2	(mM/ms)\n"
  "}\n"
  "\n"
  "STATE {\n"
  "	Cai		(mM) <1e-8> : to have tolerance of .01nM\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	Cai = Cai0\n"
  "}\n"
  "\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE state METHOD cnexp\n"
  "}\n"
  "\n"
  "DERIVATIVE state { \n"
  "	drive_channel =  - (k*10000) * iCa / (2 * FARADAY * depth)\n"
  "	if (drive_channel<=0.) { drive_channel = 0. }: cannot pump inward\n"
  ":	drive_pump = -tot * k3 * Cai / (Cai + ((k2+k3)/k1) )	: quasistat\n"
  "	drive_pump = -kt * Cai / (Cai + kd )		: Michaelis-Menten\n"
  "	drive_pump2 = -kt2 * Cai / (Cai + kd2 )		: Michaelis-Menten\n"
  "	Cai' = drive_channel+drive_pump+drive_pump2+(Cainf-Cai)/taur+(Cainf2-Cai)/taur2\n"
  "}\n"
  ;
#endif
