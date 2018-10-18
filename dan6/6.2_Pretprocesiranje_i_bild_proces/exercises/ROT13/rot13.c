#include "rot13.h"
#include "ceasar.h"

void encryptROT13(const char* in, char* out)
{
	encryptCeasar(in, out, ROT13);
}

void decryptROT13(const char* in, char* out)
{
	encryptCeasar(in, out, ROT13);
}
