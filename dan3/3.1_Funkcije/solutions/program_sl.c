#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

static const int_least32_t treshold = 20;


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


static int_least16_t print(const int_least32_t* values, const int_least16_t* indexes, int_least16_t n, int_least32_t* matchedValues, int_least16_t* matchedIndexes)
{
	int_least16_t i = 0;
	int_least16_t mi = 0;
	printf("Up to the first treshold: ");
	for (i = 0; i < n; i++)
	{
		int_least32_t x = values[i];
		if (x < treshold)
		{
			if (x % 2 == 0)
			{
				matchedValues[mi] = x;
				matchedIndexes[mi++] = indexes[i];
			}
		}
	}

	printf("\n");

	return mi;
}


void main()
{
	int_least32_t values[4000];
	int_least16_t indexes[4000];
	int_least32_t matchedValues[4000];
	int_least16_t matchedIndexes[4000];
	int_least16_t matchedIndexesSize = 0;
	int_least16_t i;
	int_least16_t n;

	printf("Number of elements: ");
	scanf("%"SCNdLEAST16, &n);
	printf("\n");
	for (i = 0; i < n; i++)
	{
		printf("%"PRIdLEAST16". element: ", i);
		scanf("%"SCNdLEAST16, &values[i]);
		indexes[i] = i;
		printf("\n");
	}

	sort(values, indexes, n);

	matchedIndexesSize = print(values, indexes, n, matchedValues, matchedIndexes);

	for (i = 0; i < matchedIndexesSize; ++i)
	{
		printf("%"PRIdLEAST32"(%"PRIdLEAST16") ", matchedValues[i], matchedIndexes[i]);
	}
}
