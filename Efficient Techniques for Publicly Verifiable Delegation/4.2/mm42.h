#include "param.h"

//init project
int mm42_init();

//Random matrix generation
int fq_mat_randz(fq_mat_t F, mm_par *par);

// M -> EKM = (M,N), PKm
int mm_setup(g1_t **N, gt_t *PK, fq_mat_t M, mm_par *par);

//x,PKm -> VKx
int mm_pgen(gt_t VKx, bn_t *x, gt_t *PK, int m);

//sigmax = x, EKM = (M,N) -> y,Pi
int mm_comp(fq_mat_t Y, g1_t Pi, bn_t *x, fq_mat_t M, g1_t **N, mm_par *par);

//y,Pi,VKx -> flag
int mm_vrfy(fq_mat_t Y, g1_t Pi, gt_t VKx, mm_par *par);