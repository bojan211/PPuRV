#include "file3.h" 

int_least8_t global_variable = 10;
//static int_least8_t global_variable;

void Increment()
{
	global_variable++;
}

void Init()
{
	global_variable = 15;
}

