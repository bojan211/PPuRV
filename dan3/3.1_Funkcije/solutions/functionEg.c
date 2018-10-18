#include "functionEg.h"


int_least32_t factorial(int_least16_t n)
{
	if (n <= 1)
		return 1;
	else 
		return (n * factorial(n-1));
}

int_least32_t fibonacci(int_least16_t n)
{
	if (n <= 1)
		return n;
	else
		return (fibonacci(n-1) + fibonacci(n-2));
}

int_least32_t factorial_non_recursive(int_least16_t n)
{
	int_least32_t a = 1;
	while(n > 0)
	{
		a = a*n;
		n--;
	}
	return a;
}

int_least32_t fibonacci_non_recursive(int_least16_t n)
{
	int_least32_t f1=1;
	int_least32_t f2=0;
	
	while(n>=1)
	{
		int_least32_t temp = f2;
		f2 = f1;
		f1 = f1+temp;
		n--;
	}
	return f2;
}