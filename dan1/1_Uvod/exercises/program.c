#include <stdio.h>


#define TRESHOLD 2000000000u


// Sortira niz values i niz indexes, koji sadrzi prvobitne indekse vrednosti
// Niz se uredjuje u nerastucem poretku, koricenjem "bubble sort" algoritma
void sort(int* values, int* indexes, int n)
{
	int i;
	int j;
	for (i = 0; i < (n - 1); i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (values[i] - values[j] < 0)
			{
				int tmp;
				tmp = values[i];
				values[i] = values[j];
				values[j] = tmp;

				tmp = indexes[i];
				indexes[i] = indexes[j];
				indexes[j] = tmp;
			}
		}
	}
}


// stampa na ekran vrednosti i njihove prvobitne indekse
// dokle god su vece od vrednosti definisane simbolom TRESHOLD
void print(int* values, int* indexes, int n)
{
	int i = 0;
	printf("Up to the first treshold: ");
	while (values[i] > TRESHOLD)
	{
		printf("%d(%d) ", values[i], indexes[i]);
		i++;
	}
	printf("\n");
}


void main()
{
	int values[10] = {2123874386, -2047433648, 2147287536, 2147000000, -2000021030, 2107487649, 2137433633, 2113426428, 2012345678, 2147182248};
	int indexes[10];
	int n = 10;
	int i;

	for (i = 0; i < n; i++)
	{
		printf("%d. element: %d", i, values[i]);
		indexes[i] = i;
		printf("\n");
	}

	sort(values, indexes, n);

	print(values, indexes, n);
}
