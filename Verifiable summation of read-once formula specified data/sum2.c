#include "sum2.h"

int pp_new2(pp *par, int r, int dr)
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


int pp_free2(pp *par){
	element_clear(par->g);
	pairing_clear(par->pairing);
	return 0;
}

int sk_new2(sk2 *sk, pp *par){
	sk->k0 = malloc(sizeof(element_t)*2);
	
	element_init_Zr(sk->k0[0],par->pairing);
	element_random(sk->k0[0]);
	element_init_Zr(sk->k0[1],par->pairing);
	element_random(sk->k0[1]);
	
	sk->k = malloc(sizeof(element_t**)*par->r);
	for(int i = 0;i<par->r;i++)
	{
		sk->k[i] = malloc(sizeof(element_t*)*par->dr);
		for(int j = 0;j<par->dr;j++)
		{
			sk->k[i][j] = malloc(sizeof(element_t)*4);
			for(int l = 0;l<4;l++){
				element_init_Zr(sk->k[i][j][l],par->pairing);
				element_random(sk->k[i][j][l]);
			}
			
		}
	}

	element_init_Zr(sk->a,par->pairing);
	element_random(sk->a);
	return 0;
}

int sk_free2(sk2 *sk, pp *par){
	element_clear(sk->k0[0]);
	element_clear(sk->k0[1]);
	for(int i = 0;i<par->r;i++)
	{
		for(int j = 0;j<par->dr;j++)
		{
			for(int l = 0;l<4;l++){
				element_clear(sk->k[i][j][l]);
			}
			free(sk->k[i][j]);			
		}
		free(sk->k[i]);
	}
	free(sk->k);
	element_clear(sk->a);
	return 0;
}


int fk2(element_t fki, int i, element_t *k0, element_t ***k, pp *par){
	int *vi = malloc(sizeof(int)*par->r);
	for(int m = par->r-1;m>=0;m--){
		vi[m] = i%par->dr;
		
		i = i/par->dr;

	}
	
	element_t alpha,gama,t0,t1,t2,t3;
	element_init_Zr(alpha,par->pairing);
	element_init_Zr(gama,par->pairing);
	element_init_Zr(t0,par->pairing);
	element_init_Zr(t1,par->pairing);
	element_init_Zr(t2,par->pairing);
	element_init_Zr(t3,par->pairing);
	element_set(alpha,k0[0]);
	element_set(gama,k0[1]);
	
	for(int m = 0;m<par->r;m++){
		element_mul_zn(t0,alpha,k[m][vi[m]][0]);
		element_mul_zn(t1,gama,k[m][vi[m]][1]);
		element_mul_zn(t2,alpha,k[m][vi[m]][2]);
		element_mul_zn(t3,gama,k[m][vi[m]][3]);
		element_add(alpha,t0,t1);
		element_add(gama,t2,t3);
	}

	element_mul_zn(fki,par->g,alpha);

	element_clear(alpha);
	element_clear(gama);
	element_clear(t0);
	element_clear(t1);
	element_clear(t2);
	element_clear(t3);
		
	
	return 0;
}


int stor2(element_t *t, sk2 *sk, element_t *m, int li, pp *par){
	printf("store\n");
	sk_new2(sk,par);
	
	element_t hm,temp;
	element_init_G1(hm,par->pairing);
	//element_init_G1(gai,par->pairing);
	element_init_G1(temp,par->pairing);
	

	//element_mul_zn(ga,par->g,sk->a);//g^a

	for(int k = 0;k<li;k++){
		element_mul_zn(hm,par->h,m[k]);

		fk2(temp,k,sk->k0,sk->k,par);
		element_add(temp,hm,temp);
		element_mul_zn(t[k],temp,sk->a);

	}

	
	element_clear(hm);
	//element_clear(gai);
	element_clear(temp);
	return 0;
}

int vgen2(element_t *vk, sk2 *sk, int *S,int sl, pp *par){
	
	element_t t1,t2;
	element_init_G1(t1,par->pairing);
	element_init_G1(t2,par->pairing);
	//element_init_G1(ga,par->pairing);
	
	fk2(t1,S[0],sk->k0,sk->k,par);
	for(int k = 1;k<sl;k++){
		fk2(t2,S[k],sk->k0,sk->k,par);
		element_add(t1,t1,t2);
		
	}

	element_mul_zn(vk[0],par->g,sk->a);//vk1=ga

	element_pairing(vk[1],t1,vk[0]);//vk2

	element_clear(t1);
	element_clear(t2);
	
	return 0;
}

int sum2(element_t ro, element_t pi, element_t *m, element_t *t, int *S, int sl, pp *par){
	element_set(ro,m[S[0]]);
	for(int k = 1;k<sl;k++){
		element_add(ro,ro,m[S[k]]);

	}

	element_set(pi,t[S[0]]);

	for(int k = 1;k<sl;k++){
		element_add(pi,pi,t[S[k]]);

	}
	return 0;
}

int vrfy2(element_t *vk, element_t ro, element_t pi, pp *par){
	int flag = 1;
	element_t left,right,hro;
	element_init_GT(left,par->pairing);
	element_init_GT(right,par->pairing);
	element_init_G1(hro,par->pairing);
	
	element_pairing(left,pi,par->g);
	
	element_mul_zn(hro,par->h,ro);
	element_pairing(right,vk[0],hro);
	element_add(right,right,vk[1]);

	flag = element_cmp(left,right);

	element_clear(hro);
	element_clear(left);
	element_clear(right);
	return flag;
}
