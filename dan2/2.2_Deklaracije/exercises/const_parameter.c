#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void modifyChar(char* ch);
void modifyString1(const char* sp);
void modifyString2(char const* sp);
void modifyString3(char* const sp);
void modifyString4(const char* const sp);

char globalString[20] = "The global string";

int main()
{
	printf("================================\n");
	printf("Const in function parameter list\n");
	printf("================================\n");

	char string1[20] = "text 1";
	char string2[20] = "text 2";
	char string3[20] = "text 3";
	char string4[20] = "text 4";

	modifyString1(string1);
	modifyString2(string2);
	modifyString3(string3);
	modifyString4(string4);

	printf("modifyString1 -> %s\n", string1);
	printf("modifyString2 -> %s\n", string2);
	printf("modifyString3 -> %s\n", string3);
	printf("modifyString4 -> %s\n", string4);

	return 0;
}


void modifyString1(const char* sp)
{
	modifyChar(sp + 3);
	sp = globalString;
	*(sp + 3) = '\0';
}

void modifyChar(char* ch)
{
	*ch = '\0';
}

void modifyString2(char const* sp)
{
	strcpy(sp, globalString);
	sp = globalString;
	*(sp + 3) = '\0';
}

void modifyString3(char* const sp)
{
	*(sp + 3) = '\0';
	sp = globalString;
}

void modifyString4(const char* const sp)
{
	sp = globalString;
	*(sp + 3) = '\0';
}

