
#include <stdio.h>
#include "mvm.h"

int main(int argc, char **argv)
{
	printf("init \n");
	mvm_init();

	printf("test :\n");
	mvm_par *par = malloc(sizeof(*par));
	mvmp_new(par);

	int n = 7;
	int d = 5;

	fq_mat_t M;
	fq_mat_init(M,n,d,par->ctx);
	fq_mat_randz(M,par);
	
	gt_t PKm;
	gt_new(PKm);
	
	g1_t **W = malloc(sizeof(g1_t*)*n);
	//g1_t **FK = malloc(sizeof(g1_t*)*n);
	for(int i=0;i<n;i++)
	{
		W[i] = malloc(sizeof(g1_t)*d);
	//	FK[i] = malloc(sizeof(g1_t)*d);
	}

	prfk *K = malloc(sizeof(prfk));

	printf("keygen:\n");
	keygen(PKm,W,K,M,par);
/*
	printf("\nFK\n");
	g1_print(FK[1][3]);	
	printf("Pkm\n");
	gt_print(PKm);
	printf("\nW\n");
	g1_print(W[1][3]);
	printf("\nK\n");
	g1_print(K->A[1]);	
	printf("\nM\n");
	fq_mat_print_pretty(M,par->ctx);
*/

	printf("probgen:\n");
	gt_t *VKx = malloc(sizeof(gt_t)*n);
	bn_t *x = malloc(sizeof(bn_t)*d);

	for(int i=0;i<d;i++)
		bn_rand_mod(x[i],par->p);
	
	probgen(VKx,n,d,K,x,par);
//	printf("\nVKx\n");
//	gt_print(VKx[4]);	
	
	printf("compute:\n");

	fq_mat_t y;
	fq_mat_init(y,n,1,par->ctx);
	
	g1_t *V = malloc(sizeof(g1_t)*n);
	
	compute(y,V,W,M,x,par);
/*	printf("\nV\n");
	g1_print(V[4]);
	printf("\ny\n");
	fq_mat_print_pretty(y,par->ctx);
*/	
	printf("verify:\n");
	int flag;
	flag = verify(PKm,VKx,y,V,par);
	
	//free
	gt_free(PKm);
	mvmp_free(par);
	for(int i=0;i<n;i++)
	{
		free(W[i]);
//		free(FK[i]);
	}
	free(W);
//	free(FK);
	free(K);
	free(VKx);
	fq_mat_clear(M,par->ctx);
	fq_mat_clear(y,par->ctx);
	free(V);
	return (0);
}

