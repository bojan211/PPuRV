#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>


static const int_least32_t treshold = 20;

static int_least32_t values[4000];
static int_least16_t indexes[4000];

static void sort(int_least32_t* values, int_least16_t* indexes, int_least16_t n)
{
	int_least16_t i;
	int_least16_t j;
	for (i = 0; i < (n - 1); i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (values[i] < values[j])
			{
				int_least32_t tmp;
				int_least16_t tmp1;

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


static void print(const int_least32_t* values, const int_least16_t* indexes, int_least16_t n)
{
	int_least16_t i = 0;
	printf("Up to the first treshold: ");
	while (values[i] > treshold && i < n)
	{
		printf("%"PRIdLEAST32"(%"PRIdLEAST16") ", values[i], indexes[i]);
		i++;
	}
	printf("\n");
}


void main()
{
	int_least16_t i;
	int_least16_t n;
	printf("Number of elements: ");
	scanf("%"SCNdLEAST16, &n);
	printf("\n");
	for (i = 0; i < n; i++)
	{
		printf("%"PRIdLEAST16". element: ", i);
		scanf("%"SCNdLEAST32, &values[i]);
		indexes[i] = i;
		printf("\n");
	}

	sort(values, indexes, n);

	print(values, indexes, n);
}
