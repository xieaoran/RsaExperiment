#include "librsa.h"
#include "stdio.h"
#include "mpir.h"

int main()
{
	KeyPair* key_pair = random_key_pair(16);

	char* plain = "abcdefghijklmnopqrstuvwxyz";
	printf("Source:\n");
	printf("%s\n", plain);

	mpz_t* encoded = encode(plain, 27, key_pair->public_key);
	printf("Encode:\n");
	for (int i = 0; i < 27; i++)
	{
		gmp_printf("%Zx ", encoded[i]);
	}
	printf("\n");

	char* decoded = decode(encoded, 27, key_pair->private_key);
	printf("Decode:\n");
	for (int i = 0; i < 27; i++)
	{
		printf("%x ", decoded[i]);
	}
	printf("\n\n");

	printf("Decryption:\n");
	printf("%s\n", decoded);
	system("pause");
	return 0;
}

