#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int32_t global;

void foo();

int main(void)
{
	printf("================================\n");
	printf("Uninitialized variables\n");
	printf("================================\n");

	foo();
	

	return 0;
}

void foo()
{
	int32_t local;
	static int32_t static_local;

	if (local % 2)
	{
		printf("TRUE : global = %d, local = %d, static_local = %d\n", global, local, static_local);
	}
	else
	{
		printf("FALSE : global = %d, local = %d, static_local = %d\n", global, local, static_local);
	}
}