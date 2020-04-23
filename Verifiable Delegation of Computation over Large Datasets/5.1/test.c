/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * test.c
 * Copyright (C) 2018
 *
 * delegate-polynomials is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * delegate-polynomials is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include "dp.h"

int main(int argc, char **argv)
{
	printf("init dp\n");
	dp_init();

	printf("test keygen:\n");
	dp_par *par = malloc(sizeof(*par));
	dpp_new(par);

	sk *sk = malloc(sizeof(*sk));

	int d = 1;
	bn_t c[d];
	for(int i = 0;i<d;i++)
	{
		bn_rand_mod(c[i],par->p);
	}

	g1_t t[d];
	for(int i=0;i<d;i++)
	{
		g1_new(t[i]);
	}
	printf("keygen:\n");
	keygen(sk,t,c,d,par);
	bn_t x;
	bn_new(x);
	// bn_rand_mod(x,par->p);
	bn_set_dig(x,1);
	bn_t y;
	bn_new(y);
	printf("compute:\n");
	g1_t tout;
	g1_new(tout);
	compute(tout,y,t,c,x,d,par);
	printf("verify:\n");

	int flagout=0;
	flagout=verify(sk,x,tout,y,d,par);
	printf("\nthe verify result:%d\n",flagout);
	return (0);
}
