#include "mf.h"

int mf_keygen(g1_t *W, vkf *vkf, bn_t *f, mfp *par)
{
	bn_t baf;
	bn_new(baf);
	g1_t af,gkr;
	g1_new(af);
	g1_new(gkr);
	
	bn_rand_mod(vkf->k,par->p);
	bn_rand_mod(vkf->a,par->p);
	
	for(int i=0;i<par->d;i++)
	{
		bn_mul(baf,f[i],vkf->a);
		bn_mod_basic(baf,baf,par->p);
		g1_mul(gkr,par->R[i],vkf->k);
		g1_mul(af,par->g,baf);
		g1_add(W[i],gkr,af);
		g1_norm(W[i],W[i]);
	}
	g1_free(af);
	g1_free(gkr);
	bn_free(baf);
	return 0;
	
}

int mf_prg(g1_t vkx, bn_t *x,mfp *par)
{
	g1_t temp;
	g1_new(temp);
	g1_set_infty(vkx);
	for(int i=0;i<par->d;i++)
	{
		g1_mul(temp,par->R[i],x[i]);
		g1_add(vkx,vkx,temp);		
	}
	g1_norm(vkx,vkx);
	g1_free(temp);
	return 0;
}

int mf_comp(bn_t y, g1_t V, g1_t *W, bn_t *f, bn_t *x, mfp *par)
{

	bn_t ty;
	g1_t temp;
	g1_new(temp);
	bn_new(ty);
	bn_zero(y);
	for(int i=0;i<par->d;i++)
	{
		bn_mul(ty,f[i],x[i]);
		bn_add(y,y,ty);
		//printf("i=%d",i);
	}
	bn_mod_basic(y,y,par->p);
	
	g1_set_infty(V);
	for(int i=0;i<par->d;i++)
	{
		g1_mul(temp,W[i],x[i]);
		g1_add(V,V,temp);		
	}
	g1_norm(V,V);
	bn_free(ty);	
	g1_free(temp);
	return 0;
}

int mf_vrfy(vkf *vkf, g1_t vkx, bn_t y, g1_t V, mfp *par)
{
	int flag = 2;
	bn_t bay;	
	g1_t right,ay,gkv;

	bn_new(bay);
	g1_new(right);
	g1_new(ay);
	g1_new(gkv);

	bn_mul(bay,y,vkf->a);
	bn_mod_basic(bay,bay,par->p);

	g1_mul(ay,par->g,bay);
	g1_mul(gkv,vkx,vkf->k);
	g1_add(right,ay,gkv);
	g1_norm(right,right);
	flag = g1_cmp(V,right);

	bn_free(bay);
	g1_free(right);
	g1_free(ay);
	g1_free(gkv);
	return flag;
}

int mvkf_new(mvkf *vkf, int n)
{
	//bn_new(vkf->a);
	bn_new(vkf->k);
	vkf->r = malloc(sizeof(bn_t)*n);
	for(int i=0;i<n;i++)
	{
		bn_new(vkf->r[i]);
	}
}

int mvkf_free(mvkf *vkf, int n)
{
	//bn_free(vkf->a);
	bn_free(vkf->k);
	for(int i=0;i<n;i++)
	{
		bn_free(vkf->r[i]);
	}
	free(vkf->r);
}


int mmf_keygen(g1_t *W, mvkf *vkf, bn_t **f, int n, mfp *par)
{
	bn_t *s = malloc(sizeof(bn_t)*par->d);
//	vkf->r = malloc(sizeof(bn_t)*n);
	bn_t temp;
	bn_new(temp);
	
	for(int i=0;i<n;i++)
	{
//		bn_new(vkf->r[i]);
		bn_rand_mod(vkf->r[i],par->p);
	}
//s
	for(int j=0;j<par->d;j++)
	{
		bn_new(s[j]);
		bn_zero(s[j]);
		for(int i=0;i<n;i++)
		{
			bn_mul(temp,vkf->r[i],f[i][j]);
			bn_add(s[j],s[j],temp);
			
		}
		bn_mod_basic(s[j],s[j],par->p);
	}

	g1_t as,gkr;
	//bn_t asi;
	g1_new(as);
	g1_new(gkr);
	//bn_new(asi);
	bn_rand_mod(vkf->k,par->p);
	//bn_rand_mod(vkf->a,par->p);
/*	
	for(int i=0;i<par->d;i++)
	{
		g1_mul(gkr,par->R[i],vkf->k);
		g1_mul(as,par->g,vkf->a);
		g1_mul(as,as,s[i]);
		g1_add(W[i],gkr,as);
		g1_norm(W[i],W[i]);
	}
*/

	for(int i=0;i<par->d;i++)
	{
		//bn_mul(asi,vkf->a,s[i]);
		//bn_mod_basic(asi,asi,par->p);
		g1_mul(gkr,par->R[i],vkf->k);
		g1_mul(as,par->g,s[i]);
//		g1_mul(as,as,s[i]);
		g1_add(W[i],gkr,as);
		g1_norm(W[i],W[i]);
	}



	//bn_free(asi);	
	g1_free(as);
	g1_free(gkr);
	bn_free(temp);
	free(s);
	return 0;
}


int mmf_comp(bn_t *y, g1_t V, g1_t *W, bn_t **f, bn_t *x, int n, mfp *par)
{
	bn_t temp;	
	bn_new(temp);
	g1_t g1t;
	g1_new(g1t);
	g1_set_infty(g1t);
	for(int i=0;i<n;i++)
	{
		bn_zero(y[i]);
		for(int j=0;j<par->d;j++)
		{
			bn_mul(temp,f[i][j],x[j]);
			bn_add(y[i],y[i],temp);
			
		}
		bn_mod_basic(y[i],y[i],par->p);
	}

	g1_set_infty(V);
	for(int i=0;i<par->d;i++)
	{
		g1_mul(g1t,W[i],x[i]);
		g1_add(V,V,g1t);		
	}
	g1_norm(V,V);
	bn_free(temp);
	g1_free(g1t);
	return 0;
}

int mm(bn_t *y, bn_t **f, bn_t *x, int n, mfp *par)
{
	bn_t temp;	
	bn_new(temp);
	for(int i=0;i<n;i++)
	{
		bn_zero(y[i]);
		for(int j=0;j<par->d;j++)
		{
			bn_mul(temp,f[i][j],x[j]);
			bn_add(y[i],y[i],temp);
			
		}
		bn_mod_basic(y[i],y[i],par->p);
	}

	bn_free(temp);
	return 0;
}

int mmf_vrfy(mvkf *vkf, g1_t vkx, bn_t *y, g1_t V, int n, mfp *par)
{
	int flag = 2;
	g1_t right,gry,gkv;

	g1_new(right);
	g1_new(gry);
	g1_new(gkv);
	g1_set_infty(gry);
	g1_set_infty(gkv);
	
	bn_t ry, temp;
	bn_new(ry);
	bn_new(temp);
	//bn_new(bary);
	bn_zero(ry);
	for(int i=0;i<n;i++)
	{
		bn_mul(temp,vkf->r[i],y[i]);
		bn_add(ry,ry,temp);
		
	}
	bn_mod_basic(ry,ry,par->p);
	

	//bn_mul(bary,vkf->a,ry);
	//bn_mod_basic(bary,bary,par->p);
//	g1_mul(ary,par->g,vkf->a);
//	g1_mul(ary,ary,ry);
	g1_mul(gry,par->g,ry);
	g1_mul(gkv,vkx,vkf->k);
	g1_add(right,gry,gkv);
	g1_norm(right,right);
	flag = g1_cmp(V,right);

	g1_free(right);
	g1_free(gry);
	g1_free(gkv);
	bn_free(ry);
	bn_free(temp);
	//bn_free(bary);
	return flag;
}
