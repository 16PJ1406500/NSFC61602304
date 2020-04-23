#include "bn_ext.h"
#include "prfm.h"


int mvm_init();

int fq_mat_randz(fq_mat_t F, mvm_par *par);

int keygen(gt_t PKm, g1_t **W, prfk *K, fq_mat_t M, mvm_par *par);

int probgen(gt_t *VKx, int n, int d, prfk *K, bn_t *x, mvm_par *par);

int compute(fq_mat_t y,g1_t *V, g1_t **W, fq_mat_t M, bn_t *x, mvm_par *par);

int verify(gt_t PKm, gt_t *VKx,fq_mat_t y, g1_t *V, mvm_par *par);
