#include "librsa.h"
#include "../../Dependencies/mpir-3.0.0/mpir.h"


#ifdef __cplusplus
extern "C" {
#endif

	KeyPair* alloc_key_pair()
	{
		KeyPair* key_pair = (KeyPair*)malloc(sizeof(KeyPair));
		key_pair->private_key = (PrivateKey*)malloc(sizeof(PrivateKey));
		mpz_inits(key_pair->private_key->n, key_pair->private_key->d, NULL);
		key_pair->public_key = (PublicKey*)malloc(sizeof(PublicKey));
		mpz_inits(key_pair->public_key->n, key_pair->public_key->e, NULL);
		return key_pair;
	}

	KeyPair* random_key_pair(mp_bitcnt_t half_bits)
	{
		gmp_randstate_t randstate;
		gmp_randinit_default(randstate);
		gmp_randseed_ui(randstate, (unsigned long)time(NULL));

		mpz_t p, q, n;
		mpz_inits(p, q, n, NULL);
		while (mpz_cmp(p, q) == 0)
		{
			random_prime(p, randstate, half_bits);
			random_prime(q, randstate, half_bits);
		}
		mpz_mul(n, p, q);

#ifdef DEBUG_PRINT
		gmp_printf("p=%Zd\n", p);
		gmp_printf("q=%Zd\n", q);
#endif

		mpz_t pm, qm;
		mpz_inits(pm, qm, NULL);
		mpz_sub_ui(pm, p, 1);
		mpz_sub_ui(qm, q, 1);
		mpz_clears(p, q, NULL);

		mpz_t e, euler_f;
		mpz_inits(e, euler_f, NULL);
		mpz_mul(euler_f, pm, qm);
		mpz_set_ui(e, 65537);
		//mpz_set(e, euler_f);
		//random_gcd_e(e, euler_f, randstate);

#ifdef DEBUG_PRINT
		gmp_printf("f=(p-1)*(q-1)=%Zd\n", euler_f);
		gmp_printf("n=p*q=%Zd\n", n);
		gmp_printf("e=%Zd\n", e);
#endif
		mpz_clears(pm, qm, NULL);

		mpz_t r, x, y;
		mpz_inits(r, x, y, NULL);
		ext_euclid(r, e, euler_f, x, y);
		mpz_mod(x, x, euler_f);
		if (mpz_sgn(x) < 0) mpz_add(x, x, euler_f);
		mpz_clears(euler_f, r, y, NULL);

#ifdef DEBUG_PRINT
		gmp_printf("d=%Zd\n", x);
#endif

		KeyPair* key_pair = alloc_key_pair();
		mpz_set(key_pair->public_key->n, n);
		mpz_set(key_pair->public_key->e, e);
		mpz_set(key_pair->private_key->n, n);
		mpz_set(key_pair->private_key->d, x);
		mpz_clears(n, e, x, NULL);
		return key_pair;
	}

	mpz_t* encode(char* data, unsigned length, PublicKey* public_key)
	{
		mpz_t* encoded = malloc(sizeof(mpz_t) * length);
		mpz_t current;
		mpz_init(current);

		for (unsigned i = 0; i < length; i++)
		{
			mpz_init(encoded[i]);
			mpz_set_ui(current, data[i]);
			mpz_powm(encoded[i], current, public_key->e, public_key->n);
		}

		mpz_clear(current);
		return encoded;
	}

	char* decode(mpz_t* encoded, unsigned length, PrivateKey* private_key)
	{
		char* decoded = malloc(sizeof(char) * length);
		mpz_t current;
		mpz_init(current);

		for (unsigned i = 0; i < length; i++)
		{
			mpz_powm(current, encoded[i], private_key->d, private_key->n);
			decoded[i] = (char)mpz_get_ui(current);
		}

		mpz_clear(current);
		return decoded;
	}


#ifdef __cplusplus
}
#endif