#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;
#if defined(__cplusplus)
extern "C" {
#endif

extern void _cadad_IT2_dend_all_reg(void);
extern void _cadad_IT2_soma_reg(void);
extern void _cal_reg(void);
extern void _can_reg(void);
extern void _cat_reg(void);
extern void _ih_reg(void);
extern void _kap_reg(void);
extern void _kBK_reg(void);
extern void _kdr_reg(void);
extern void _kdr_soma_reg(void);
extern void _nax_reg(void);
extern void _pas_nml2_reg(void);
extern void _pg1_reg(void);
extern void _pg2_reg(void);
extern void _pg_reg(void);

void modl_reg() {
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");
    fprintf(stderr, " \"cadad_IT2_dend_all.mod\"");
    fprintf(stderr, " \"cadad_IT2_soma.mod\"");
    fprintf(stderr, " \"cal.mod\"");
    fprintf(stderr, " \"can.mod\"");
    fprintf(stderr, " \"cat.mod\"");
    fprintf(stderr, " \"ih.mod\"");
    fprintf(stderr, " \"kap.mod\"");
    fprintf(stderr, " \"kBK.mod\"");
    fprintf(stderr, " \"kdr.mod\"");
    fprintf(stderr, " \"kdr_soma.mod\"");
    fprintf(stderr, " \"nax.mod\"");
    fprintf(stderr, " \"pas_nml2.mod\"");
    fprintf(stderr, " \"pg1.mod\"");
    fprintf(stderr, " \"pg2.mod\"");
    fprintf(stderr, " \"pg.mod\"");
    fprintf(stderr, "\n");
  }
  _cadad_IT2_dend_all_reg();
  _cadad_IT2_soma_reg();
  _cal_reg();
  _can_reg();
  _cat_reg();
  _ih_reg();
  _kap_reg();
  _kBK_reg();
  _kdr_reg();
  _kdr_soma_reg();
  _nax_reg();
  _pas_nml2_reg();
  _pg1_reg();
  _pg2_reg();
  _pg_reg();
}

#if defined(__cplusplus)
}
#endif
