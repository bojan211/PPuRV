#include <stdio.h>


int main(void)
{
	printf("================================\n");
	printf("Exercise2\n");
	printf("================================\n");

	int high = 0x11112222;
	int low = 0x33334444;
	long long big = 0LL;
	long long lowMask = 0x00000000FFFFFFFFLL;

	big = high;
	printf("added high : %llX", big);
	big = big << 32;
	printf("shifted by 32 : %llX", big);
	big += lowMask & low;
	printf("added low %llX", big);

	return 0;
}
