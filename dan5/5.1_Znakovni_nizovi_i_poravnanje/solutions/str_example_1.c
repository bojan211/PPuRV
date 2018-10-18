#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint_least32_t stringLength(const char str[])
{
	uint_least32_t i;
	for (i = 0 ; str[i]!='\0' ; i++);
	return i;
}


void stringTrim(char str[])
{
	uint_least32_t i;
	while (str[0]==' ')
	{
		for (i = 0 ; i < stringLength(str) ; str[i]=str[i+1] , i++);
		str[i] = '\0';
	}

	for (i = (stringLength(str)-1) ; str[i]==' ' ; str[i--]='\0');
}


uint_least8_t extractSubstring(const char *inStr, char * outStr, size_t beginning, size_t end)
{
	if ((end < stringLength(inStr)) && (beginning <= end))
	{
		uint_least32_t i;
		for(i = beginning ; i <= end ; outStr[i - beginning] = inStr[i] , i++);
		outStr[i - beginning] = '\0';
		return 1;
	}
	return 0;
}

uint_least8_t concateStrings(char * str1, const char * str2)
{
	uint_least32_t i,str1_length, str2_length;
	str1_length = stringLength(str1);
	str2_length = stringLength(str2);
	for (i = str1_length; i<(str1_length + str2_length) ; str1[i] = str2[i - str1_length], i++);
	return 1;
}



int main(void)
{
	char string[40] = "   Petar Bojanic    ";
	char string2[20];
	printf ("*****%s*****\n", string);
	printf ("*****%"PRIuPTR"*****\n", stringLength(string));
	stringTrim(string);
	printf ("*****%s*****\n", string);
	if (extractSubstring(string, string2, 5, 10))
		printf ("*****%s*****\n", string2);
	if (concateStrings(string, string2))
		printf ("*****%s*****\n", string);
	
	return 0;
}
