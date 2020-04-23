#include "dp.h"


int dp_init()
{
	// Set up the context
	if (core_init() != STS_OK)
	{
		core_clean();
		return 1;
	}
	if (pc_param_set_any() != STS_OK)
	{
		THROW(ERR_NO_CURVE);
		core_clean();
		return 1;
	}
	return 0;
}


int keygen(sk *sk, g1_t *t, bn_t *c, int d, dp_par *par)
{

	sk->K = malloc(sizeof(prfk));
	prfs_kengen(sk->K,par);

	bn_new(sk->a);
	bn_rand_mod(sk->a,par->p);

	g1_t gi;
	g1_new(gi);
	bn_t fi;
	bn_new(fi);
	g1_t ac;
	g1_new(ac);

	printf("begin for:\n");

	for(int i=0;i<d;i++)
	{
		g1_set_infty(gi);
	//	printf("set fi:%d\n",i);
		bn_set_dig(fi,i);
	//	printf("prf\n");
		prfs(gi,fi,sk->K,par);
	//	g1_norm(gi,gi);
	//	printf("ac:\n");
		g1_mul(ac,par->g,sk->a);
		g1_mul(ac,ac,c[i]);
		// g1_print(gi);
		// g1_print(ac);
	//	printf("t:\n");
		g1_add(t[i],gi,ac);
	//	printf("t%d\n",i);
	//	g1_print(t[i]);

	}

	g1_free(gi);
	bn_clean(fi);
	g1_free(ac);

	return 0;
}


int compute(g1_t tout,bn_t y,g1_t *t, bn_t *c,bn_t x,int d,dp_par *par)
{
	bn_t w[d];
	for(int i=0;i<d;i++)
	{
		bn_new(w[i]);
	}
	bn_t temp1bn;
	bn_new(temp1bn);
	g1_t tempg1;
	g1_new(tempg1);
	bn_t temp2bn;
	bn_new(temp2bn);
	for(int i=0;i<d;i++)
	{
		bn_set_dig(temp1bn,i);
		bn_mxp(w[i],x,temp1bn,par->p);
		bn_mod_basic(w[i],w[i],par->p);
	}
	for(int i=0;i<d;i++)
	{
		// bn_print(y);
		bn_mul(temp2bn,c[i],w[i]);
		bn_add(y,y,temp2bn);
		bn_mod_basic(y,y,par->p);
		// bn_print(y);
	}
	for(int i=0;i<d;i++)
	{
		// bn_print(w[i]);
		// bn_print(w[i]);
		g1_mul(tempg1,t[i],w[i]);
		// g1_print(t[i]);
		// // g1_print(tout);
		// g1_print(tempg1);
		// g1_new(tout);

		g1_add(tout,tout,tempg1);
		// g1_print(tout);
	}
	// g1_print(tout);
	bn_clean(temp1bn);
	bn_clean(temp2bn);
	g1_free(tempg1);
	return 0;
}


int verify(sk* sk,bn_t x,g1_t tout,bn_t y,int d,dp_par *par)
{
	bn_t k1x;
	bn_new(k1x);
	bn_t bnone;
	bn_new(bnone);
	bn_t fenmu;
	bn_new(fenmu);
	bn_t k1exp;
	bn_new(k1exp);
	bn_t xexp;
	bn_new(xexp);
	bn_t fenzisub;
	bn_new(fenzisub);
	bn_t xexpk1exp;
	bn_new(xexpk1exp);
	bn_t fenzi;
	bn_new(fenzi);
	bn_t bnd;
	bn_new(bnd);
	bn_t z;
	bn_new(z);
	g1_t right;
	g1_new(right);
	bn_t rightbn;	
	bn_new(rightbn);
	bn_set_dig(bnd,d);
	bn_set_dig(bnone,1);
	bn_mul(k1x,sk->K->k1,x);
	// bn_print(sk->K->k1);
	// bn_print(sk->K->k0);
	bn_sub(fenmu,bnone,k1x);
	// bn_print(k1x);
	bn_mxp(k1exp,sk->K->k1,bnd,par->p);
	bn_mxp(xexp,x,bnd,par->p);
	// bn_print(xexp);
	bn_mul(xexpk1exp,xexp,k1exp);
	bn_sub(fenzisub,bnone,xexpk1exp);
	bn_mul(fenzi,fenzisub,sk->K->k0);
	bn_div(z,fenzi,fenmu);
	// bn_print(z);
	// bn_print(sk->K->k0);
	// bn_print(sk->a);
	bn_mod_basic(z,z,par->p);
	g1_t ag1;
	g1_new(ag1);
	g1_mul(ag1,par->g,sk->a);
	g1_t ayg1;
	g1_new(ayg1);
	g1_mul(ayg1,ag1,y);
	g1_t zg1;
	g1_new(zg1);
	g1_mul(zg1,par->g,z);
	g1_add(right,zg1,ayg1);
	// g1_print(zg1);
	// g1_print(ayg1);



	// bn_print(z);
	// g1_print(zg1);
	// bn_print(y);
	// bn_print(sk->a);
	// bn_mul(ay,sk->a,y);
	// bn_add(zay,z,ay);
	// bn_mod_basic(zay,zay,par->p);
	// bn_mod_basic(zay,zay,par->p);
	// g1_mul(right,par->g,zay);
	// g1_print(ayg1);
	// bn_add(rightbn,ay,z);
	// g1_mul(right,par->g,rightbn);
	int flag=0;
	printf("\nverifaction left:\n" );
	g1_print(tout);
	printf("\nverifaction right:\n" );
	g1_print(right);
	flag=g1_cmp(right,tout);
	if(flag==2)
	{
		return 2;
	}
	return 0;
}
