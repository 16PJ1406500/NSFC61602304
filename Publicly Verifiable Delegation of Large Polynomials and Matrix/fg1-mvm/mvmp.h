#include "bn_ext.h"

typedef struct
{
	bn_t p;
	fmpz_t pf;
	fq_ctx_t ctx;
	g1_t g;
	g2_t h;
	gt_t gt;
}mvm_par;

//generate the parameters for the scheme
int mvmp_new(mvm_par *par);

//free the struct
int mvmp_free(mvm_par *par);