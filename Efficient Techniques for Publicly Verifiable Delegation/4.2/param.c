#include "param.h"

int mmp_new(mm_par *par, int n)
{
	g1_get_ord(par->p);
	bn2fmpz(par->pf,par->p);
	
	par->n = n;
	
	fq_ctx_init(par->ctx,par->pf,1,"ctx");
	
	g1_new(par->g);
	g1_get_gen(par->g);
	g2_new(par->h);
	g2_get_gen(par->h); 
	gt_new(par->gt);
	pc_map(par->gt, par->g, par->h);

	par->G = malloc(sizeof(g1_t)*par->n);
	bn_t tb;
	bn_new(tb);
	for(int i=0;i<n;i++)
	{
		bn_rand_mod(tb,par->p);
		g1_mul(par->G[i],par->g,tb);
	}
	bn_free(tb);

	//select delta
//	bn_t delta;
	bn_new(par->delta);

	bn_rand_mod(par->delta,par->p);
	//hd
	g2_mul(par->hd,par->h,par->delta);

	return 0;
}

int mmp_free(mm_par *par)
{
	bn_clean(par->p);
	fmpz_clear(par->pf);
	fq_ctx_clear(par->ctx);
	free(par->G);
	g1_free(par->g);
	g2_free(par->h);
	gt_free(par->gt);
	bn_free(par->delta);
	g1_free(hd);

	return 0;
}