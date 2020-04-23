#include "sum.h"

int pp_new(pp *par, int r, int dr)
{
	pbc_param_t w;
	pbc_param_init_a_gen(w,128,256);
	pairing_init_pbc_param(par->pairing,w);
	element_init_G1(par->g,par->pairing);
	element_random(par->g);
	element_init_G1(par->h,par->pairing);
	element_random(par->h);
	par->r = r;
	par->dr = dr;
	return 0;
}


int pp_free(pp *par){
	element_clear(par->g);
	element_clear(par->h);
	pairing_clear(par->pairing);
	return 0;
}

int sk_new(sk *sk, pp *par){
	element_init_Zr(sk->k0,par->pairing);
	element_random(sk->k0);
	
	sk->k = malloc(sizeof(element_t*)*par->r);
	for(int i = 0;i<par->r;i++)
	{
		sk->k[i] = malloc(sizeof(element_t)*par->dr);
		for(int j = 0;j<par->dr;j++)
		{
			element_init_Zr(sk->k[i][j],par->pairing);
			element_random(sk->k[i][j]);
		}
	}

	element_init_Zr(sk->a,par->pairing);
	element_random(sk->a);
	return 0;
}

int sk_free(sk *sk, pp *par){
	element_clear(sk->k0);
	for(int i = 0;i<par->r;i++)
	{
		for(int j = 0;j<par->dr;j++)
		{
			element_clear(sk->k[i][j]);
		}
		free(sk->k[i]);
	}
	free(sk->k);
	element_clear(sk->a);
	return 0;
}


int fk(element_t fki, int i, element_t k0, element_t **k, pp *par){
	int *vi = malloc(sizeof(int)*par->r);
	for(int m = par->r-1;m>=0;m--){
		vi[m] = i%par->dr;
		
		i = i/par->dr;

	}
	
	element_t temp;
	element_init_Zr(temp,par->pairing);
	element_set(temp,k0);
	for(int m = 0;m<par->r;m++){
		element_mul(temp,temp,k[m][vi[m]]);

	}

	element_mul_zn(fki,par->g,temp);

	element_clear(temp);
	
	return 0;
}


int stor(element_t *t, sk *sk, element_t *m, int li, pp *par){
	sk_new(sk,par);
	
	element_t ga,gai,temp;
	element_init_G1(ga,par->pairing);
	element_init_G1(gai,par->pairing);
	element_init_G1(temp,par->pairing);

	element_mul_zn(ga,par->g,sk->a);//g^a

	for(int k = 0;k<li;k++){
		element_mul_zn(gai,ga,m[k]);

		fk(temp,k,sk->k0,sk->k,par);
		element_add(t[k],gai,temp);

	}

	
	element_clear(ga);
	element_clear(gai);
	element_clear(temp);
	return 0;
}

int vgen(element_t vk, sk *sk, int *S,int sl, pp *par){
	element_t temp;
	element_init_G1(temp,par->pairing);

	fk(vk,S[0],sk->k0,sk->k,par);
	for(int k = 1;k<sl;k++){
		fk(temp,S[k],sk->k0,sk->k,par);
		element_add(vk,vk,temp);

	}
	return 0;
}

int sum(element_t ro, element_t pi, element_t *m, element_t *t, int *S, int sl, pp *par){
	clock_t ss1,ee1,ss2,ee2;
	ss1 = clock();	
	element_set(ro,m[S[0]]);
	for(int k = 1;k<sl;k++){
		element_add(ro,ro,m[S[k]]);

	}
	ee1 = clock();
	printf("directly calculated time: %f\n", (double)(ee1 - ss1) /CLOCKS_PER_SEC);

	ss2 = clock();
	element_set(pi,t[S[0]]);

	for(int k = 1;k<sl;k++){
		element_add(pi,pi,t[S[k]]);

	}
	ee2 = clock();
	printf("directly mul time: %f\n", (double)(ee2 - ss2) /CLOCKS_PER_SEC);
	return 0;
}

int vrfy(element_t vk, element_t ro, element_t pi, sk *sk, pp *par){
	int flag = 1;
	element_t btemp;
	element_init_Zr(btemp,par->pairing);
	element_t gtemp;
	element_init_G1(gtemp,par->pairing);

	element_mul(btemp,sk->a,ro);

	element_mul_zn(gtemp,par->g,btemp);
	element_add(gtemp,gtemp,vk);

	element_printf("left = %B\n", pi);
	element_printf("rignt = %B\n", gtemp);
	flag = element_cmp(pi,gtemp);
	element_clear(btemp);
	element_clear(gtemp);
	return flag;
}
