#include "bn_ext.h"

typedef struct
{
	bn_t p;
	fmpz_t pf;
	int n;
	fq_ctx_t ctx;
	g1_t g;
	g2_t h;
	gt_t gt;
	g1_t *G;
	bn_t delta;
	g2_t hd;
	
}mm_par;

//init matrix multiplication paramters
int mmp_new(mm_par *par, int n);

//free
int mmp_free(mm_par *par);