#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int_least8_t foo(int_least8_t x);

int main(void)
{
	printf("Local variable scope\n");
	int_least8_t x;

	x = 42;
	foo(x);
	printf("After calling foo: x = %d\n", x);

	return EXIT_SUCCESS;
}

int_least8_t foo(int_least8_t x)
{
	x = 101;
	printf("Inside foo: x = %d\n", x);
	return x;
}
