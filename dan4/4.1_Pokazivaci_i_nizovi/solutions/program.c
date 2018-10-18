#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>


static const int_least32_t treshold_array[] = {20, 30, 40};


typedef struct _s
{
	int_least32_t value;
	int_least16_t index;
} val_ind_struct_t;

static val_ind_struct_t struct_array[4000];


static void bubble_sort(val_ind_struct_t* str_array, int_least16_t n);
static void quick_sort(val_ind_struct_t* str_array, int_least16_t n);

static void (*sort_func_array[])(val_ind_struct_t* str_array, int_least16_t n) = {bubble_sort, quick_sort};


static void bubble_sort(val_ind_struct_t* str_array, int_least16_t n)
{
	int_least16_t i;
	int_least16_t j;
	for (i = 0; i < (n - 1); i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (str_array[i].value < str_array[j].value)
			{
				val_ind_struct_t tmp;
				
				tmp = str_array[i];
				str_array[i] = str_array[j];
				str_array[j] = tmp;
			}
		}
	}
}


static int compare(const void* px, const void* py)
{
	int_least32_t x = ((const val_ind_struct_t*)px)->value;
	int_least32_t y = ((const val_ind_struct_t*)py)->value;
	
	if (x < y)
		return 1;
	else
	{
		if (x == y)
			return 0;
		else
			return -1;
	}
}


static void quick_sort(val_ind_struct_t* str_array, int_least16_t n)
{
	// sort using qsort standard function
	void qsort(str_array, (size_t)n, sizeof(val_ind_struct_t), compare);
}


static void print(const val_ind_struct_t* str_array, int_least16_t n, int_fast8_t tr_index)
{
	int_least16_t i = 0;
	int_least32_t treshold;
	printf("Up to the %"PRIdFAST8". treshold: ", tr_index);

	treshold = treshold_array[tr_index - 1];

	while (str_array[i].value > treshold && i < n)
	{
		printf("%"PRIdLEAST32"(%"PRIdLEAST16") ", str_array[i].value, str_array[i].index);
		i++;
	}
	printf("\n");
}


void main()
{
	int_least16_t i;
	int_least16_t n;
	int_fast8_t treshold_index;
	int_fast8_t sort_index;
	printf("Number of elements: ");
	scanf("%"SCNdLEAST16, &n);
	printf("\n");
	for (i = 0; i < n; i++)
	{
		printf("%"PRIdLEAST16". element: ", i);
		scanf("%"SCNdLEAST32, &(struct_array[i].value));
		struct_array[i].index = i;
		printf("\n");
	}
	printf("Trashold you want to use (1, 2, or 3): ");
	scanf("%"SCNdFAST8, &treshold_index);
	printf("\n");
	printf("Sorting algorithm you want to use (1- bubble, 2- quick): ");
	scanf("%"SCNdFAST8, &sort_index);
	printf("\n");

	sort_func_array[sort_index - 1](struct_array, n);

	print(struct_array, n, treshold_index);
}
