#include "mvmp.h"
#include "bn_ext.h"
typedef struct
{
	g1_t *A;
	g1_t *B;
	bn_t *a;
	bn_t *b;
}prfk;


int prfs_keygen(prfk *K, int n, int d, mvm_par *par);

int prfs(g1_t fk, prfk *K, int i, int j);