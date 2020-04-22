#include <stdio.h>
#include <time.h>
#include "mm42.h"

void try(int n, int m, mm_par *par)
{
	clock_t s1,s2,s3,s4,e1,e2,e3,e4;
	g1_t **N = malloc(sizeof(g1_t*)*n);
	for(int i=0;i<n;i++)
	   N[i] = malloc(sizeof(g1_t)*m);
	
	gt_t *PK = malloc(sizeof(gt_t)*m);

	fq_mat_t M;
	fq_mat_init(M,n,m,par->ctx);


	fq_mat_randz(M,par);
	s1 = clock();
	mm_setup(N,PK,M,par);
	e1 = clock();


	bn_t *x = malloc(sizeof(bn_t)*m);
	for(int j=0;j<m;j++)
		bn_rand_mod(x[j],par->p);

	gt_t VKx;
	
	gt_new(VKx);
	s2 = clock();
	mm_pgen(VKx,x,PK,m);
	e2 = clock();

        //printf("this is intest\n ");

	fq_mat_t Y;
	fq_mat_init(Y,n,m,par->ctx);

	g1_t Pi;
	g1_new(Pi);
	s3 = clock();
	mm_comp(Y,Pi,x,M,N,par);
	e3 = clock();

	s4 = clock();
	mm_vrfy(Y,Pi,VKx,par);
	e4 = clock();
	printf("\n matrix dimension m=%d, client time=%f", m, (double)(e1+e2+e4 - s4-s2-s1) /CLOCKS_PER_SEC);
	

	for(int i=0;i<n;i++)
		free(N[i]);
	free(N);
	free(PK);
	fq_mat_clear(Y,par->ctx);
	g1_free(Pi);
}


int main()
{
	mm42_init();
	mm_par *par = malloc(sizeof(*par));	

        for (int i=1;i<21;i++)
        {
            mmp_new(par,10*i);
            try(10*i,10*i,par);
            mmp_free(par);
        }
	free(par);

	return 0;
}

