#include "dpp.h"

int dpp_new(dp_par *par)
{
	par->m = 24;
	g1_get_ord(par->p);
	bn2fmpz(par->pf,par->p);
	fq_ctx_init(par->ctx,par->pf,1,"ctx");
	g1_new(par->g);
	g1_get_gen(par->g);
	return 0;
}
int dpp_free(dp_par *par)
{
	bn_clean(par->p);
	fmpz_clear(par->pf);
	fq_ctx_clear(par->ctx);
	g1_free(par->g);
	return 0;
}