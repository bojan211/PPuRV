#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define TRESHOLD 20


void sort(int_least32_t* values, uint_least16_t* indexes, uint_least16_t n)
{
	uint_least16_t i;
	uint_least16_t j;
	for (i = 0; i < (n - 1); i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (values[i] < values[j])
			{
				int_least32_t tmp;
				uint_least16_t tmp1;

				tmp = values[i];
				values[i] = values[j];
				values[j] = tmp;

				tmp1 = indexes[i];
				indexes[i] = indexes[j];
				indexes[j] = tmp1;
			}
		}
	}
}


void print(int_least32_t* values, uint_least16_t* indexes, uint_least16_t n)
{
	uint_least16_t i = 0;
	printf("Up to the first treshold: ");
	while (values[i] > TRESHOLD && i < n)
	{
		printf("%"PRIdLEAST32"(%"PRIuLEAST16") ", values[i], indexes[i]);
		i++;
	}
	printf("\n");
}


int_least32_t values[40000];
uint_least16_t indexes[40000];


void main()
{
	uint_least16_t i;
	uint_least16_t n;
	
	printf("Number of elements: ");
	scanf("%"SCNuLEAST16"", &n);
	printf("\n");
	for (i = 0; i < n; i++)
	{
		printf("%"PRIuLEAST16". element: ", i);
		scanf("%"SCNdLEAST32"", &values[i]);
		indexes[i] = i;
		printf("\n");
	}

	sort(values, indexes, n);

	print(values, indexes, n);
}
