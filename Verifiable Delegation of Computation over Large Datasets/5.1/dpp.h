#include "bn_ext.h"

typedef struct
{
	int m;
	fmpz_t pf;
	fq_ctx_t ctx;
	bn_t p;
	g1_t g;
}dp_par;

//generate the parameters for the scheme
int dpp_new(dp_par *par);

//free the struct
int dpp_free(dp_par *par);