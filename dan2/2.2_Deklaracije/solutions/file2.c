#include "file3.h"
#include <stdio.h>
#include <inttypes.h>

int_least8_t global_variable;

void Printf_Increment()
{
	printf("[file2] global_variable = %"PRIdLEAST8"\n", global_variable++);
}

