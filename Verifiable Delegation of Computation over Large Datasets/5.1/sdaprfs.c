#include "sdaprfs.h"

int prfs_kengen(prfk *K, dp_par *par)
{
	bn_new(K->k0);
	bn_new(K->k1);
	bn_rand_mod(K->k0,par->p);
	bn_rand_mod(K->k1,par->p);
	return 0;
}

int prfs(g1_t fkx, bn_t x, prfk *K, dp_par *par)
{
	bn_t temp;
	bn_new(temp);
//	printf("prf1\n");
	bn_mxp(temp,K->k1,x,par->p);//(k1^x)modp
//	printf("prf2\n");
	bn_mul(temp,temp,K->k0);//k0*k1^x
	bn_mod_basic(temp,temp,par->p);//k0*k1^xmodp
//	printf("prf3\n");
	g1_mul(fkx,par->g,temp);
	bn_clean(temp);
	return 0;
}
