#include "sum2.h"
#include <math.h>

int sum_test(sk *sk,int *S,int sl,element_t *m,element_t *t, pp *par)
{
	printf("sum:length of S is:%d",sl);
	clock_t s2,s3,s4,e2,e3,e4;


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
	//printf("The client time was: %f\n", (double)(e1+e2+e4 - s4-s2-s1) /CLOCKS_PER_SEC);
	printf("flag is:%d",flag);

	element_clear(vk);
	element_clear(ro);
	element_clear(pi);
	return 0;
}

int sum2_test(sk2 *sk2,int *S,int sl,element_t *m,element_t *t, pp *par)
{
	printf("sum2:length of S is:%d",sl);

	clock_t s2,s3,s4,e2,e3,e4;
	//vgen
	element_t *vk = malloc(sizeof(element_t)*2);
	element_init_G1(vk[0],par->pairing);
	element_init_GT(vk[1],par->pairing);
	
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
	//printf("The client time was: %f\n", (double)(e1+e2+e4 - s4-s2-s1) /CLOCKS_PER_SEC);
	printf("flag is:%d",flag);

	element_clear(vk[0]);
	element_clear(vk[1]);
	free(vk);
	element_clear(ro);
	element_clear(pi);
	return 0;
	
}


int main(int argc, char **argv)
{	
	int r = 4;
	int dr = 20;
	int li = pow(dr,r);

//S
	int slmax = 10000*9;
	int *S = malloc(sizeof(int)*slmax);

	//int sl = 1;
	//int SS[1] = {255};
	int index = 0;
	int d11[10] = {0,1,2,3,4,5,6,7,8,9};
	int d10[10] = {10,11,12,13,14,15,16,17,18,19};
	int d21[10] = {0,1,2,3,4,5,6,7,8,9};
	int d20[10] = {10,11,12,13,14,15,16,17,18,19};
	int d31[10] = {0,1,2,3,4,5,6,7,8,9};
	int d30[10] = {10,11,12,13,14,15,16,17,18,19};
	int d41[10] = {0,1,2,3,4,5,6,7,8,9};
	int d40[10] = {10,11,12,13,14,15,16,17,18,19};
	//element_t *x = malloc(sizeof(element_t)*d);
	
	for(int a=0;a<10;a++)
	{
		for(int b=0;b<10;b++){
			for(int c=0;c<10;c++){
				for(int d=0;d<10;d++){
					S[index] = d10[a]*pow(dr,3)+d21[b]*pow(dr,2)+d30[c]*dr+d41[d];
					index++;
				}
			}
		}
	}

	for(int a=0;a<10;a++)
	{
		for(int b=0;b<10;b++){
			for(int c=0;c<10;c++){
				for(int d=0;d<10;d++){
					S[index] = d10[a]*pow(dr,3)+d21[b]*pow(dr,2)+d31[c]*dr+d40[d];
					index++;
				}
			}
		}
	}
	for(int a=0;a<10;a++)
	{
		for(int b=0;b<10;b++){
			for(int c=0;c<10;c++){
				for(int d=0;d<10;d++){
					S[index] = d10[a]*pow(dr,3)+d21[b]*pow(dr,2)+d31[c]*dr+d41[d];
					index++;
				}
			}
		}
	}
	for(int a=0;a<10;a++)
	{
		for(int b=0;b<10;b++){
			for(int c=0;c<10;c++){
				for(int d=0;d<10;d++){
					S[index] = d11[a]*pow(dr,3)+d20[b]*pow(dr,2)+d30[c]*dr+d41[d];
					index++;
				}
			}
		}
	}
	for(int a=0;a<10;a++)
	{
		for(int b=0;b<10;b++){
			for(int c=0;c<10;c++){
				for(int d=0;d<10;d++){
					S[index] = d11[a]*pow(dr,3)+d20[b]*pow(dr,2)+d31[c]*dr+d40[d];
					index++;
				}
			}
		}
	}
	for(int a=0;a<10;a++)
	{
		for(int b=0;b<10;b++){
			for(int c=0;c<10;c++){
				for(int d=0;d<10;d++){
					S[index] = d11[a]*pow(dr,3)+d20[b]*pow(dr,2)+d31[c]*dr+d41[d];
					index++;
				}
			}
		}
	}
	for(int a=0;a<10;a++)
	{
		for(int b=0;b<10;b++){
			for(int c=0;c<10;c++){
				for(int d=0;d<10;d++){
					S[index] = d11[a]*pow(dr,3)+d21[b]*pow(dr,2)+d30[c]*dr+d41[d];
					index++;
				}
			}
		}
	}
	for(int a=0;a<10;a++)
	{
		for(int b=0;b<10;b++){
			for(int c=0;c<10;c++){
				for(int d=0;d<10;d++){
					S[index] = d11[a]*pow(dr,3)+d21[b]*pow(dr,2)+d31[c]*dr+d40[d];
					index++;
				}
			}
		}
	}
	for(int a=0;a<10;a++)
	{
		for(int b=0;b<10;b++){
			for(int c=0;c<10;c++){
				for(int d=0;d<10;d++){
					S[index] = d11[a]*pow(dr,3)+d21[b]*pow(dr,2)+d31[c]*dr+d41[d];
					index++;
				}
			}
		}
	}
	//for(int i = index;i<sl;i++){
	//	S[i] = S[i-1];
	//}

//generate the parameters	
	pp *par = malloc(sizeof(pp));
//	pp *par2 = malloc(sizeof(pp));
	//printf("li = %d",li);
	pp_new(par,r,dr);
//	pp_new2(par2,r,dr)
	printf("test\n");

	clock_t s1,e1;


	element_t *t = malloc(sizeof(element_t)*li);
	element_t *t2 = malloc(sizeof(element_t)*li);
	sk *sk = malloc(sizeof(*sk));
	sk2 *sk2 = malloc(sizeof(*sk2));
	element_t *m = malloc(sizeof(element_t)*li);
	for(int i=0;i<li;i++)
	{   
		element_init_G1(t[i],par->pairing);
		element_init_G1(t2[i],par->pairing);
		element_init_Zr(m[i],par->pairing);
		element_random(m[i] );
	}

	//stor
	s1 = clock();	
	stor(t, sk, m,li,par);
	e1 = clock();
	printf("The stor time was: %f\n", (double)(e1 - s1) /CLOCKS_PER_SEC);
	

	
	
	//stor2
	s1 = clock();	
	stor2(t2, sk2, m,li,par);
	e1 = clock();
	printf("The stor2 time was: %f\n", (double)(e1 - s1) /CLOCKS_PER_SEC);


	for(int si = 10000;si<slmax;si+=10000){
		printf("*******************************\n");
		printf("|S|=%d\n",si);
		printf("sum test\n");
		sum_test(sk,S,si,m,t,par);
		printf ("------------------------------\n");
		printf("sum2 test\n");
		sum2_test(sk2,S,si,m,t2,par);
		
		
	}
	
//free
	for(int i=0;i<li;i++)
	{   
		element_clear(t[i]);
		element_clear(m[i]);
	}

	free(t);
	free(m);

	sk_free(sk,par);
	free(sk);

	
	sk_free2(sk2,par);
	free(sk2);
	
	pp_free(par);
	free(par);

	
	return 0;




}
