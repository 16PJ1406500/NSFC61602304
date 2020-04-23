#include "bn_ext.h"
#include "sdaprfs.h"

typedef struct
{
	prfk *K;
	bn_t a;
}sk;

int dp_init();

int keygen(sk *sk, g1_t *t, bn_t *c, int d, dp_par *par);

int compute(g1_t tout,bn_t y,g1_t *t, bn_t *c,bn_t x,int d,dp_par *par);

int verify(sk* sk,bn_t x,g1_t tout,bn_t y,int d,dp_par *par);
