#ifndef _UTILS_H_
#define _UTILS_H_
#include "utils.h"
#endif

//define the parameter
typedef struct
{
	int d;
	bn_t p;
	g1_t g;
	g1_t *R;

}mfp;

//generate the parametr
int mfp_new(mfp *par, int d);

//free the structure
int mfp_free(mfp *par);
