#pragma once

#ifndef MATHTOOLS_H
#define MATHTOOLS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mpir.h"

	extern void random_prime(mpz_t prime, gmp_randstate_t randstate, mp_bitcnt_t bits);
	extern void random_gcd_e(mpz_t result, mpz_t target, gmp_randstate_t randstate);
	extern void ext_euclid(mpz_t recursion, mpz_t a, mpz_t b, mpz_t x, mpz_t y);


#ifdef __cplusplus
}
#endif

#endif /* MATHTOOLS_H */
