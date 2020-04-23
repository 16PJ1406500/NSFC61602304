#include "mfp.h"
typedef struct
{
	bn_t a;
	bn_t k;
}vkf;

typedef struct
{
	//bn_t a;
	bn_t k;
	bn_t *r;
}mvkf;
int mf_keygen(g1_t *W, vkf *vkf, bn_t *f, mfp *par);

int mf_prg(g1_t vkx, bn_t *x,mfp *par);

int mf_comp(bn_t y, g1_t V, g1_t *W, bn_t *f, bn_t *x, mfp *par);

int mf_vrfy(vkf *vkf, g1_t vkx, bn_t y, g1_t V, mfp *par);

int mvkf_new(mvkf *vkf, int n);

int mvkf_free(mvkf *vkf, int n);

int mmf_keygen(g1_t *W, mvkf *vkf, bn_t **f, int n, mfp *par);

int mmf_comp(bn_t *y, g1_t V, g1_t *W, bn_t **f, bn_t *x, int n, mfp *par);

int mmf_vrfy(mvkf *vkf, g1_t vkx, bn_t *y, g1_t V, int n, mfp *par);
