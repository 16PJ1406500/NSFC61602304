#include "sum.h"

#include <math.h>
int main(int argc, char **argv)
{	
	int r = 4;
	int dr = 40;
	int li = pow(dr,r);

//S
	int sl = 160000;
	int S[160000];

	//int sl = 1;
	//int SS[1] = {255};
	int index = 0;
	int d11[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	int d10[20] = {20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39};
	int d21[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	int d20[20] = {20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39};
	int d31[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	int d30[20] = {20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39};
	int d41[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	int d40[20] = {20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39};
	//element_t *x = malloc(sizeof(element_t)*d);
	
	for(int a=0;a<20;a++)
	{
		for(int b=0;b<20;b++){
			for(int c=0;c<20;c++){
				for(int d=0;d<20;d++){
					S[index] = d10[a]*pow(dr,3)+d21[b]*pow(dr,2)+d30[c]*dr+d41[d];
					index++;
				}
			}
		}
	}
/*
	for(int a=0;a<20;a++)
	{
		for(int b=0;b<20;b++){
			for(int c=0;c<20;c++){
				for(int d=0;d<20;d++){
					S[index] = d10[a]*pow(dr,3)+d21[b]*pow(dr,2)+d31[c]*dr+d40[d];
					index++;
				}
			}
		}
	}
	for(int a=0;a<20;a++)
	{
		for(int b=0;b<20;b++){
			for(int c=0;c<20;c++){
				for(int d=0;d<20;d++){
					S[index] = d10[a]*pow(dr,3)+d21[b]*pow(dr,2)+d31[c]*dr+d41[d];
					index++;
				}
			}
		}
	}
	for(int a=0;a<20;a++)
	{
		for(int b=0;b<20;b++){
			for(int c=0;c<20;c++){
				for(int d=0;d<20;d++){
					S[index] = d11[a]*pow(dr,3)+d20[b]*pow(dr,2)+d30[c]*dr+d41[d];
					index++;
				}
			}
		}
	}
	for(int a=0;a<20;a++)
	{
		for(int b=0;b<20;b++){
			for(int c=0;c<20;c++){
				for(int d=0;d<20;d++){
					S[index] = d11[a]*pow(dr,3)+d20[b]*pow(dr,2)+d31[c]*dr+d40[d];
					index++;
				}
			}
		}
	}
	for(int a=0;a<20;a++)
	{
		for(int b=0;b<20;b++){
			for(int c=0;c<20;c++){
				for(int d=0;d<20;d++){
					S[index] = d11[a]*pow(dr,3)+d20[b]*pow(dr,2)+d31[c]*dr+d41[d];
					index++;
				}
			}
		}
	}
	for(int a=0;a<20;a++)
	{
		for(int b=0;b<20;b++){
			for(int c=0;c<20;c++){
				for(int d=0;d<20;d++){
					S[index] = d11[a]*pow(dr,3)+d21[b]*pow(dr,2)+d30[c]*dr+d41[d];
					index++;
				}
			}
		}
	}
	for(int a=0;a<20;a++)
	{
		for(int b=0;b<20;b++){
			for(int c=0;c<20;c++){
				for(int d=0;d<20;d++){
					S[index] = d11[a]*pow(dr,3)+d21[b]*pow(dr,2)+d31[c]*dr+d40[d];
					index++;
				}
			}
		}
	}
	for(int a=0;a<20;a++)
	{
		for(int b=0;b<20;b++){
			for(int c=0;c<20;c++){
				for(int d=0;d<20;d++){
					S[index] = d11[a]*pow(dr,3)+d21[b]*pow(dr,2)+d31[c]*dr+d41[d];
					index++;
				}
			}
		}
	}*/
	//for(int i = index;i<sl;i++){
	//	S[i] = S[i-1];
	//}

//generate the parameters	
	pp *par = malloc(sizeof(pp));
	//printf("li = %d",li);
	pp_new(par,r,dr);
	
	printf("test\n");

	clock_t s1,s2,s3,s4,e1,e2,e3,e4;

//stor
	element_t *t = malloc(sizeof(element_t)*li);
	sk *sk = malloc(sizeof(*sk));
	element_t *m = malloc(sizeof(element_t)*li);
	for(int i=0;i<li;i++)
	{   
		element_init_G1(t[i],par->pairing);
		
		element_init_Zr(m[i],par->pairing);
		element_random(m[i] );
	}
	s1 = clock();	
	stor(t, sk, m,li,par);
	e1 = clock();
	printf("The stor time was: %f\n", (double)(e1 - s1) /CLOCKS_PER_SEC);

//vgen
	element_t vk;
	element_init_G1(vk,par->pairing);
	
	s2 = clock();
	vgen(vk,sk, S,sl,par);
	e2 = clock();
	printf("The vgen time was: %f\n", (double)(e2 - s2) /CLOCKS_PER_SEC);
//sum
	element_t ro;
	element_t pi;
	element_init_Zr(ro,par->pairing);
	element_init_G1(pi,par->pairing);
	s3 = clock();
	sum(ro,pi,m,t,S,sl,par);
	e3 = clock();
	printf("The sum time was: %f\n", (double)(e3 - s3) /CLOCKS_PER_SEC);

//vrfy
	s4 = clock();
	int flag = vrfy(vk,ro,pi,sk,par);
	e4 = clock();
	printf("The vrfy time was: %f\n", (double)(e4 - s4) /CLOCKS_PER_SEC);
	printf("The client time was: %f\n", (double)(e1+e2+e4 - s4-s2-s1) /CLOCKS_PER_SEC);
	printf("flag is:%d",flag);

	for(int i=0;i<li;i++)
	{   
		element_clear(t[i]);
		element_clear(m[i]);
	}

	
	
	free(t);
	free(m);
	sk_free(sk,par);
	free(sk);
	element_clear(vk);
	element_clear(ro);
	element_clear(pi);
	pp_free(par);
	free(par);

	return 0;
}
