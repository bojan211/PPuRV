


Конверзије типова

int foo(float x)
{
	return x;
}

float r;

void main()
{
	unsigned long y;
	
	y = 5;

	r = foo(y);
}


Колико овде има имплицитних конверзија
?















float foo_arg1;
int foo_ret;

void foo()
{
	foo_ret = foo_arg1;
}

float r;

void main()
{
	unsigned long y = 5;
	foo_arg1 = y;
	foo();
	r = foo_ret;
}
