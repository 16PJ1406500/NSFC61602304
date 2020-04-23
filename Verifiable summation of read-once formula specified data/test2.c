#include "sum2.h"

#include <time.h>
#include <math.h>
int main(int argc, char **argv)
{


//generate the parameters	
	pp *par = malloc(sizeof(pp));
	int r = 4;
	int dr = 5;
	int li = pow(dr,r);
	//printf("li = %d",li);
	pp_new(par,r,dr);
	
	printf("test\n");

	clock_t s1,s2,s3,s4,e1,e2,e3,e4;

//stor
	element_t *t = malloc(sizeof(element_t)*li);
	sk2 *sk2 = malloc(sizeof(*sk2));
	element_t *m = malloc(sizeof(element_t)*li);
	for(int i=0;i<li;i++)
	{   
		element_init_G1(t[i],par->pairing);
		
		element_init_Zr(m[i],par->pairing);
		element_random(m[i] );
	}
	s1 = clock();	
	stor2(t, sk2, m,li,par);
	e1 = clock();
	printf("The stor time was: %f\n", (double)(e1 - s1) /CLOCKS_PER_SEC);

//vgen
	element_t *vk = malloc(sizeof(element_t)*2);
	element_init_G1(vk[0],par->pairing);
	element_init_GT(vk[1],par->pairing);
	int sl = 36;
	int S[36];

	//int sl = 1;
	//int SS[1] = {255};
	int index = 0;
	int d10[3] = {2,3,4};
	int d21[2] = {0,2};
	int d30[3] = {1,2,4};
	int d41[2] = {0,4};
	//element_t *x = malloc(sizeof(element_t)*d);
	
	for(int a=0;a<3;a++)
	{
		for(int b=0;b<2;b++){
			for(int c=0;c<3;c++){
				for(int d=0;d<2;d++){
					S[index] = d10[a]*125+d21[b]*25+d30[c]*5+d41[d];
					//printf ("S%d = %d\n",index,S[index]);
					index++;
				}
			}
		}
	}
	s2 = clock();
	vgen2(vk,sk2, S,sl,par);
	e2 = clock();
	printf("The vgen time was: %f\n", (double)(e2 - s2) /CLOCKS_PER_SEC);
//sum
	element_t ro;
	element_t pi;
	element_init_Zr(ro,par->pairing);
	element_init_G1(pi,par->pairing);
	s3 = clock();
	sum2(ro,pi,m,t,S,sl,par);
	e3 = clock();
	printf("The sum time was: %f\n", (double)(e3 - s3) /CLOCKS_PER_SEC);

//vrfy
	s4 = clock();
	int flag = vrfy2(vk,ro,pi,par);
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
	sk_free2(sk2,par);
	free(sk2);
	element_clear(vk[0]);
	element_clear(vk[1]);
	free(vk);
	element_clear(ro);
	element_clear(pi);
	pp_free(par);
	free(par);

	return 0;
}
