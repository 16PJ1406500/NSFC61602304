#include "sum.h"

#include <math.h>
int main(int argc, char **argv)
{	
	int r = 4;
	int dr = 5;
	int li = pow(dr,r);

//S
	int sl = 102400;
	int S[102400];

	//int sl = 1;
	//int SS[1] = {255};
	int index = 0;
	int d11[2] = {0,1};
	int d10[3] = {2,3,4};
	int d21[2] = {0,2};
	int d20[3] = {1,3,4};
	int d31[2] = {0,3};
	int d30[3] = {1,2,4};
	int d41[2] = {0,4};
	int d40[3] = {1,2,3};
	//element_t *x = malloc(sizeof(element_t)*d);
	
	for(int a=0;a<3;a++)
	{
		for(int b=0;b<2;b++){
			for(int c=0;c<3;c++){
				for(int d=0;d<2;d++){
					S[index] = d10[a]*pow(dr,3)+d21[b]*pow(dr,2)+d30[c]*dr+d41[d];
					index++;
				}
			}
		}
	}
	for(int a=0;a<3;a++)
	{
		for(int b=0;b<2;b++){
			for(int c=0;c<2;c++){
				for(int d=0;d<3;d++){
					S[index] = d10[a]*pow(dr,3)+d21[b]*pow(dr,2)+d31[c]*dr+d40[d];
					index++;
				}
			}
		}
	}
	for(int a=0;a<3;a++)
	{
		for(int b=0;b<2;b++){
			for(int c=0;c<2;c++){
				for(int d=0;d<2;d++){
					S[index] = d10[a]*pow(dr,3)+d21[b]*pow(dr,2)+d31[c]*dr+d41[d];
					index++;
				}
			}
		}
	}
	for(int a=0;a<2;a++)
	{
		for(int b=0;b<3;b++){
			for(int c=0;c<3;c++){
				for(int d=0;d<2;d++){
					S[index] = d11[a]*pow(dr,3)+d20[b]*pow(dr,2)+d30[c]*dr+d41[d];
					index++;
				}
			}
		}
	}
	for(int a=0;a<2;a++)
	{
		for(int b=0;b<3;b++){
			for(int c=0;c<2;c++){
				for(int d=0;d<3;d++){
					S[index] = d11[a]*pow(dr,3)+d20[b]*pow(dr,2)+d31[c]*dr+d40[d];
					index++;
				}
			}
		}
	}
	for(int a=0;a<2;a++)
	{
		for(int b=0;b<3;b++){
			for(int c=0;c<2;c++){
				for(int d=0;d<2;d++){
					S[index] = d11[a]*pow(dr,3)+d20[b]*pow(dr,2)+d31[c]*dr+d41[d];
					index++;
				}
			}
		}
	}
	for(int a=0;a<2;a++)
	{
		for(int b=0;b<2;b++){
			for(int c=0;c<3;c++){
				for(int d=0;d<2;d++){
					S[index] = d11[a]*pow(dr,3)+d21[b]*pow(dr,2)+d30[c]*dr+d41[d];
					index++;
				}
			}
		}
	}
	for(int a=0;a<2;a++)
	{
		for(int b=0;b<2;b++){
			for(int c=0;c<2;c++){
				for(int d=0;d<3;d++){
					S[index] = d11[a]*pow(dr,3)+d21[b]*pow(dr,2)+d31[c]*dr+d40[d];
					index++;
				}
			}
		}
	}
	for(int a=0;a<2;a++)
	{
		for(int b=0;b<2;b++){
			for(int c=0;c<2;c++){
				for(int d=0;d<2;d++){
					S[index] = d11[a]*pow(dr,3)+d21[b]*pow(dr,2)+d31[c]*dr+d41[d];
					index++;
				}
			}
		}
	}
	for(int i = index;i<sl;i++){
		S[i] = S[i-1];
	}

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
