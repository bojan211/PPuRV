#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main()
{
	int32_t i = 0;
	int32_t x = 10;
	int32_t y = 20;

	for (i=0; i<5; i++)
	{
		int32_t x = 0;
		static int32_t y = 0;
		printf("x=%"PRId32", y=%"PRId32"\n", x++, y++);
	}

	printf("\nx=%"PRId32", y=%"PRId32"\n", x++, y++);
	
	return 0;
}
