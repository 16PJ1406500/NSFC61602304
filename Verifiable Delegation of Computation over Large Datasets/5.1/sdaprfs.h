#include "dpp.h"
#include "bn_ext.h"
typedef struct
{
	bn_t k0;
	bn_t k1;
}prfk;


int prfs_kengen(prfk *K, dp_par *par);

int prfs(g1_t fkx, bn_t x, prfk *K, dp_par *par);