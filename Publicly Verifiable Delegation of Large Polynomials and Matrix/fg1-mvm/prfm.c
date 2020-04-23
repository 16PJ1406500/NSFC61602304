#include "prfm.h"

int prfs_keygen(prfk *K, int n, int d, mvm_par *par)
{
	K->A = malloc(sizeof(g1_t)*d);
	K->B = malloc(sizeof(g1_t)*d);
	K->a = malloc(sizeof(bn_t)*n);
	K->b = malloc(sizeof(bn_t)*n);

	for(int i=0;i<d;i++)
	{
		g1_new(K->A[i]);
		g1_new(K->B[i]);
		g1_rand(K->A[i]);
		g1_rand(K->B[i]);
	}

	for(int j=0;j<n;j++)
	{
		bn_new(K->a[j]);
		bn_new(K->b[j]);
		bn_rand_mod(K->a[j],par->p);
		bn_rand_mod(K->b[j],par->p);
	}
	return 0;
}

int prfs(g1_t fk, prfk *K, int i, int j)
{
	g1_t Aa;
	g1_t Bb;

	g1_new(Aa);
	g1_new(Bb);

	g1_mul(Aa,K->A[j],K->a[i]);
	g1_mul(Bb,K->B[j],K->b[i]);
	g1_add(fk,Aa,Bb);

	g1_free(Aa);
	g1_free(Bb);
		
	return 0;
}
