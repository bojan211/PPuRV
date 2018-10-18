#include <stdio.h>
#include <stdint.h>


void main()
{
	long y = 0x7FFFFFFA;
	float x = y;
	printf("%d\n%f", y, x);
	getchar();
}
