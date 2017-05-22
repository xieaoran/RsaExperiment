#include "mathtools.h"

#ifdef __cplusplus
extern "C" {
#endif

	// random n-bit prime number
	void random_prime(mpz_t prime, gmp_randstate_t randstate, mp_bitcnt_t bits)
	{
		mpz_urandomb(prime, randstate, bits);
		mpz_setbit(prime, bits - 1);
		mpz_nextprime(prime, prime);
	}

	// result < target && result is prime && result not divisor of target
	void random_gcd_e(mpz_t result, mpz_t target, gmp_randstate_t randstate)
	{
		while (mpz_cmp(result, target) >= 0 || mpz_divisible_p(target, result) != 0)
		{
			mpz_urandomm(result, randstate, target);
			mpz_nextprime(result, result);
		}
	}

	// ax + by = gcd(a,b)
	void ext_euclid(mpz_t recursion, mpz_t a, mpz_t b, mpz_t x, mpz_t y)
	{
		if (mpz_cmp_ui(b, 0) == 0)
		{
			mpz_set_ui(x, 1);
			mpz_set_ui(y, 0);
			mpz_set(recursion, a);
			return;
		}

		mpz_t mod;
		mpz_init(mod);

		mpz_mod(mod, a, b);
		ext_euclid(recursion, b, mod, x, y);
		mpz_clear(mod);

		mpz_t temp, quotient;
		mpz_inits(temp, quotient, NULL);

		mpz_set(temp, x);
		mpz_set(x, y);
		mpz_fdiv_q(quotient, a, b);
		mpz_mul(y, quotient, y);
		mpz_sub(y, temp, y);
		mpz_clears(temp, quotient, NULL);
	}


#ifdef __cplusplus
}
#endif