#pragma once

#ifndef LIBRSA_H
#define LIBRSA_H

#define LIBRSA_API __declspec(dllexport)

#ifdef __cplusplus
extern "C" {
#endif

#include "stdlib.h"
#include "mathtools.h"
#include "mpir.h"
#include "time.h"

	typedef struct {
		mpz_t n;
		mpz_t e;
	} PublicKey;

	typedef struct {
		mpz_t n;
		mpz_t d;
	} PrivateKey;

	typedef struct {
		PublicKey* public_key;
		PrivateKey* private_key;
	} KeyPair;

	extern LIBRSA_API KeyPair* alloc_key_pair();
	extern LIBRSA_API KeyPair* random_key_pair(mp_bitcnt_t half_bits);
	extern LIBRSA_API mpz_t* encode(char* data, unsigned length, PublicKey* public_key);
	extern LIBRSA_API char* decode(mpz_t* encoded, unsigned length, PrivateKey* private_key);

#ifdef __cplusplus
}
#endif

#endif /* LIBRSA_H */