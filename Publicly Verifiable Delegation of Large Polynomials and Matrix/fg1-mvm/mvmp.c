#include "mvmp.h"

int mvmp_new(mvm_par *par)
{
	g1_get_ord(par->p);
	bn2fmpz(par->pf,par->p);
	fq_ctx_init(par->ctx,par->pf,1,"ctx");
	g1_new(par->g);
	g1_get_gen(par->g);
	g2_new(par->h);
	g2_get_gen(par->h);
	gt_new(gt);
	pc_map(par->gt,par->g,par->h);
	return 0;
}
int mvmp_free(mvm_par *par)
{
	bn_clean(par->p);
	fmpz_clear(par->pf);
	fq_ctx_clear(par->ctx);
	g1_free(par->g);
	g2_free(par->h);
	gt_free(par->gt);
	return 0;
}