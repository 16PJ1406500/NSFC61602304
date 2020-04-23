#include <time.h>
#include "utils.h"
int main(int argc, char **argv){
	sinit();
	bn_t p;
	g1_t g;
	bn_new(p);
	g1_new(g);
	g1_get_ord(p);
	g1_get_gen(g);

	int n = 1000000;
	
	double s1,e1;
//trng
	bn_t *trng = malloc(sizeof(bn_t)*n);
	s1 = omp_get_wtime();
	#pragma omp parallel for
	for(int i = 0;i<n;i++){
		bn_rand_mod(trng[i],p);
	}
	e1 = omp_get_wtime();;
	
	printf("trng:%f\n",(double)(e1 - s1) );

//taddp
	bn_t *temp = malloc(sizeof(bn_t)*n);
	bn_t *ans = malloc(sizeof(bn_t)*n);
	#pragma omp parallel for
	for(int i = 0;i<n;i++){
		bn_new(temp[i]);
		bn_rand_mod(temp[i],p);
	}

	s1 = omp_get_wtime();
	#pragma omp parallel for
	for(int i = 0;i<n;i++){
		bn_new(ans[i]);
		bn_add(ans[i],temp[i],trng[i]);
		bn_mod_basic(ans[i],ans[i],p);
	}
	e1 = omp_get_wtime();
	
	printf("taddp:%f\n",(double)(e1 - s1) );
//tmulp
	s1 = omp_get_wtime();
	#pragma omp parallel for
	for(int i = 0;i<n;i++){
		bn_mul(ans[i],temp[i],trng[i]);
		bn_mod_basic(ans[i],ans[i],p);
	}
	e1 = omp_get_wtime();
	
	printf("tmulp:%f\n",(double)(e1 - s1) );

//texpG
	g1_t *tg = malloc(sizeof(g1_t)*n);
	s1 = omp_get_wtime();
	#pragma omp parallel for
	for(int i = 0;i<n;i++){
		g1_new(tg[i]);
		g1_mul(tg[i],g,trng[i]);
		g1_norm(tg[i],tg[i]);
	}
	e1 = omp_get_wtime();
	
	printf("texpG:%f\n",(double)(e1 - s1) );
//tmulG
	g1_t *tg2 = malloc(sizeof(g1_t)*n);
	g1_t *ansg = malloc(sizeof(g1_t)*n);
	#pragma omp parallel for
	for(int i = 0;i<n;i++){
		g1_mul(tg2[i],g,temp[i]);
		g1_norm(tg2[i],tg2[i]);
	}
	
	s1 = omp_get_wtime();
	#pragma omp parallel for
	for(int i = 0;i<n;i++){
		g1_new(ansg[i]);
		g1_add(ansg[i],tg[i],tg2[i]);
		g1_norm(ansg[i],ansg[i]);
	}
	e1 = omp_get_wtime();
	
	printf("tmulG:%f\n",(double)(e1 - s1));

	
	free(trng);
	free(temp);
	free(ans);
	free(tg);
	free(tg2);
	free(ansg);
	bn_free(p);
	g1_free(g);
	sclose();
	return 0;
}
