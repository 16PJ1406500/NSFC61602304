#include "bn_ext.h"

int mpz2bn(bn_t out, mpz_t in)		
{
	int size = mpz_sizeinbase(in, 10) + 2;		// + 2 bytes for minus sign and NULL
	char * temp = malloc(sizeof(char)*size);

	mpz_get_str(temp, 10, in);
	bn_zero(out);
	bn_read_str(out, temp, size, 10);

	free(temp);
	return 0;
}

int fmpz2bn(bn_t out, fmpz_t in)		
{
	mpz_t temp;
	mpz_init(temp);

	fmpz_get_mpz(temp , in);

	mpz2bn(out, temp);

	mpz_clear(temp);

	return 0;
}

int fq2bn(bn_t out, fq_t in, fq_ctx_t ctx)
{
	fmpz_t temp;
	fmpz_init(temp);

	fmpz_set_str(temp, fq_get_str_pretty(in, ctx), 10);

	fmpz2bn(out, temp);

	fmpz_clear(temp);
	return 0;
}

int bn2mpz(mpz_t out, bn_t in)
{
	int size = bn_size_str(in, 10);
	char * temp = malloc(sizeof(char)*size);

	bn_write_str(temp, size, in, 10);
	mpz_set_str(out,temp, 10);

	free(temp);
	return 0;
}

int bn2fmpz(fmpz_t out, bn_t in)
{
	mpz_t temp;
	mpz_init(temp);

	bn2mpz(temp, in);

	fmpz_set_mpz(out , temp);

	mpz_clear(temp);
	return 0;
}

int bn2fq(fq_t out, bn_t in, fq_ctx_t ctx)
{
	fmpz_t temp;
	fmpz_init(temp);
	
	bn2fmpz(temp, in);
	fq_set_fmpz(out, temp, ctx);

	fmpz_clear(temp);
	return 0;
}







