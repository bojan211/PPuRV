#include "vigenere.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void encryptVigenere(const char* in, const char* key, char* out)
{
	size_t inLength = strlen(in);
	size_t keyLength = strlen(key);
	size_t i = 0;
	size_t j = 0;

	for (i = 0; i < inLength; i++)
	{
		if (j >= keyLength)
		{
			j = 0;
		}
		char c = in[i];
		char k = key[j];
		if ((c>='a' && c<='z') || (c>='A' && c<='Z'))
		{
			c = tolower(c);
			k = tolower(k);
			out[i] = ((c -'a') + (key[j] -'a')) % 26 + 'a';
			j++;
		}
		else
		{
			out[i] = in[i];
		}
	}
	out[i] = '\0';
}

void decryptVigenere(const char* in, const char* key, char* out)
{
	size_t inLength = strlen(in);
	size_t keyLength = strlen(key);
	size_t i = 0;
	size_t j = 0;

	for (i = 0; i < inLength; i++)
	{
		if (j >= keyLength)
		{
			j = 0;
		}
		char c = in[i];
		char k = key[j];
		if ((c>='a' && c<='z') || (c>='A' && c<='Z'))
		{
			c= tolower(c);
			k= tolower(k);
			if ((c = (c - 'a') - (k - 'a')) < 0)
			{
				c += 26;
			}
			out[i] = c % 26 + 'a';
			j++;
		}
		else
		{
			out[i] = in[i];
		}
	}
	out[i] = '\0';
}
