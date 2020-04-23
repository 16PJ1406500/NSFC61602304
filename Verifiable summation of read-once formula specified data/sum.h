#include <pbc/pbc.h>
//#include <pbc/pbc_test.h>
#include <time.h>

typedef struct
{
	pairing_t pairing;
	element_t g;
	element_t h;
	int r;
	int dr;

}pp;

typedef struct
{
	element_t k0;
	element_t **k;
	element_t a;
}sk;



//generate the parametr
int pp_new(pp *par, int r, int dr);

//free the structure
int pp_free(pp *par);

int sk_new(sk *sk, pp *par);

int sk_free(sk *sk, pp *par);

int fk(element_t fki, int i, element_t k0, element_t **k, pp *par);

int stor(element_t *t, sk *sk, element_t *m, int li, pp *par);

int vgen(element_t vk, sk *sk, int *S,int sl, pp *par);

int sum(element_t ro, element_t pi, element_t *m, element_t *t, int *S, int sl, pp *par);

int vrfy(element_t vk, element_t ro, element_t pi, sk *sk, pp *par);
