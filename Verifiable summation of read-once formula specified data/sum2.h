#include <pbc/pbc.h>
#include <pbc/pbc_test.h>
#include "sum.h"
/*
typedef struct
{
	pairing_t pairing;
	element_t g;
	element_t h;
	int r;
	int dr;

}pp;
*/

typedef struct
{
	element_t *k0;
	element_t ***k;
	element_t a;
}sk2;



//generate the parametr
int pp_new2(pp *par, int r, int dr);

//free the structure
int pp_free2(pp *par);

int sk_new2(sk2 *sk, pp *par);

int sk_free2(sk2 *sk, pp *par);

int fk2(element_t fki, int i, element_t *k0, element_t ***k, pp *par);

int stor2(element_t *t, sk2 *sk, element_t *m, int li, pp *par);

int vgen2(element_t *vk, sk2 *sk, int *S,int sl, pp *par);

int sum2(element_t ro, element_t pi, element_t *m, element_t *t, int *S, int sl, pp *par);

int vrfy2(element_t *vk, element_t ro, element_t pi, pp *par);
