#include "mfp.h"


int mfp_new(mfp *par, int d)
{
	bn_t temp;
	bn_new(temp);
	par->d = d;
	g1_get_ord(par->p);
	g1_new(par->g);
	g1_get_gen(par->g);
	par->R = malloc(sizeof(bn_t)*d);
	for(int i=0;i<d;i++)
	{
		bn_rand_mod(temp,par->p);
		g1_mul(par->R[i],par->g,temp);
	}

	bn_free(temp);
	return 0;
}


int mfp_free(mfp *par){
	bn_free(par->p);
	g1_free(par->g);
	free(par->R);
	return 0;
}
