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
 
#define nrn_init _nrn_init__wrap
#define _nrn_initial _nrn_initial__wrap
#define nrn_cur _nrn_cur__wrap
#define _nrn_current _nrn_current__wrap
#define nrn_jacob _nrn_jacob__wrap
#define nrn_state _nrn_state__wrap
#define _net_receive _net_receive__wrap 
#define install install__wrap 
 
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
#define v _p[0]
#define v_columnindex 0
 
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
 static void _hoc_install(void);
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
 "setdata_wrap", _hoc_setdata,
 "install_wrap", _hoc_install,
 0, 0
};
 /* declare global and static user variables */
 static int _thread1data_inuse = 0;
static double _thread1data[1];
#define _gth 0
#define INSTALLED_wrap _thread1data[0]
#define INSTALLED _thread[_gth]._pval[0]
#define verbose verbose_wrap
 double verbose = 0;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 0,0
};
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "INSTALLED_wrap", &INSTALLED_wrap,
 "verbose_wrap", &verbose_wrap,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(NrnThread*, _Memb_list*, int);
static void nrn_state(NrnThread*, _Memb_list*, int);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"wrap",
 0,
 0,
 0,
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 1, _prop);
 	/*initialize range parameters*/
 	_prop->param = _p;
 	_prop->param_size = 1;
 
}
 static void _initlists();
 static void _thread_mem_init(Datum*);
 static void _thread_cleanup(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _wrap_reg() {
	int _vectorized = 1;
  _initlists();
 	register_mech(_mechanism, nrn_alloc,(void*)0, (void*)0, (void*)0, nrn_init, hoc_nrnpointerindex, 2);
  _extcall_thread = (Datum*)ecalloc(1, sizeof(Datum));
  _thread_mem_init(_extcall_thread);
  _thread1data_inuse = 0;
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 1, _thread_mem_init);
     _nrn_thread_reg(_mechtype, 0, _thread_cleanup);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 1, 0);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 wrap /home/gluciferd/Macaque_auditory_thalamocortical_model_data/model/mod/wrap.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int install(_threadargsproto_);
 
/*VERBATIM*/

#include <math.h>
#include <stdlib.h>

double* Wrap(double* x,int n,int flen){
  double* y = (double*) calloc(n,sizeof(double));
  int i,j=0;
  for(i=flen/2+1;i<flen;i++)    y[j++]=x[i];
  j=n-flen/2-1;
  for(i=0;i<=flen/2;i++)   y[j++]=x[i];
  return y;
}

void WrapAround(void* vv) {
  double* x,*y;
  int vsz,fsz,i;
  vsz = vector_instance_px(vv,&x);
  fsz = (int) *getarg(1);
  if(fsz > vsz) {
    printf("WrapAround ERRA: invalid filter len %d > vector len %d!\n",fsz,vsz);
    return;
  }
  y = Wrap(x,vsz,fsz);
  for(i=0;i<vsz;i++) x[i]=y[i];
  free(y);
}

 
static int  install ( _threadargsproto_ ) {
   if ( INSTALLED  == 1.0 ) {
     printf ( "already installed wrap.mod" ) ;
     }
   else {
     INSTALLED = 1.0 ;
     
/*VERBATIM*/
    install_vector_method("WrapAround",WrapAround);
 }
    return 0; }
 
static void _hoc_install(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 install ( _p, _ppvar, _thread, _nt );
 hoc_retpushx(_r);
}
 
static void _thread_mem_init(Datum* _thread) {
  if (_thread1data_inuse) {_thread[_gth]._pval = (double*)ecalloc(1, sizeof(double));
 }else{
 _thread[_gth]._pval = _thread1data; _thread1data_inuse = 1;
 }
 }
 
static void _thread_cleanup(Datum* _thread) {
  if (_thread[_gth]._pval == _thread1data) {
   _thread1data_inuse = 0;
  }else{
   free((void*)_thread[_gth]._pval);
  }
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{

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

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{
} return _current;
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
}}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/gluciferd/Macaque_auditory_thalamocortical_model_data/model/mod/wrap.mod";
static const char* nmodl_file_text = 
  ": $Id: wrap.mod,v 1.1 2010/12/21 19:56:41 samn Exp $ \n"
  "\n"
  "NEURON {\n"
  "THREADSAFE\n"
  " SUFFIX wrap\n"
  " GLOBAL INSTALLED\n"
  " GLOBAL verbose\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "  INSTALLED=0\n"
  "  verbose=0\n"
  "}\n"
  "\n"
  "VERBATIM\n"
  "\n"
  "#include <math.h>\n"
  "#include <stdlib.h>\n"
  "\n"
  "double* Wrap(double* x,int n,int flen){\n"
  "  double* y = (double*) calloc(n,sizeof(double));\n"
  "  int i,j=0;\n"
  "  for(i=flen/2+1;i<flen;i++)    y[j++]=x[i];\n"
  "  j=n-flen/2-1;\n"
  "  for(i=0;i<=flen/2;i++)   y[j++]=x[i];\n"
  "  return y;\n"
  "}\n"
  "\n"
  "void WrapAround(void* vv) {\n"
  "  double* x,*y;\n"
  "  int vsz,fsz,i;\n"
  "  vsz = vector_instance_px(vv,&x);\n"
  "  fsz = (int) *getarg(1);\n"
  "  if(fsz > vsz) {\n"
  "    printf(\"WrapAround ERRA: invalid filter len %d > vector len %d!\\n\",fsz,vsz);\n"
  "    return;\n"
  "  }\n"
  "  y = Wrap(x,vsz,fsz);\n"
  "  for(i=0;i<vsz;i++) x[i]=y[i];\n"
  "  free(y);\n"
  "}\n"
  "\n"
  "ENDVERBATIM\n"
  "\n"
  "PROCEDURE install () {\n"
  "  if (INSTALLED==1) {\n"
  "    printf(\"already installed wrap.mod\")\n"
  "  } else {\n"
  "    INSTALLED=1\n"
  "    VERBATIM\n"
  "    install_vector_method(\"WrapAround\",WrapAround);\n"
  "    ENDVERBATIM\n"
  "  }\n"
  "}\n"
  ;
#endif
