#include <fmpz.h>
#include <fmpz_poly.h>
#include <fq.h>
#include <fq_poly.h>
#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <relic/relic.h>


int mpz2bn(bn_t out, mpz_t in);
int fmpz2bn(bn_t out, fmpz_t in);
int fq2bn(bn_t out, fq_t in, fq_ctx_t ctx);

int bn2mpz(mpz_t out, bn_t in);
int bn2fmpz(fmpz_t out, bn_t in);
int bn2fq(fq_t out, bn_t in, fq_ctx_t ctx);


