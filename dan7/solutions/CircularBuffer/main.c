#include <stdio.h>

#include "CircularBuffer.h"

int main (void)
{
	static buffer_struct buffer;
	static buffer_struct buffer2;

	Init(&buffer);
	Init(&buffer2);
	
	if (isEmpty(&buffer)) printf("buffer EMPTY\n");
	else printf("buffer NOT EMPTY\n");
	if (isFull(&buffer)) printf("buffer FULL\n");
	else printf("buffer NOT FULL\n");

	printf("putting 1 2 3 4 5\n");
	put(&buffer, 1);
	put(&buffer, 2);
	put(&buffer, 3);
	put(&buffer, 4);
	put(&buffer, 5);
	
	if (isEmpty(&buffer))
	{
		printf("buffer EMPTY\n");
	}
	else 
	{
		printf("buffer NOT EMPTY\n");
	}
	if (isFull(&buffer))
	{
		printf("buffer FULL\n");
	}
	else 
	{
		printf("buffer NOT FULL\n");
	}

	printf("%d\n", get(&buffer));
	printf("%d\n", get(&buffer));

	printf("putting 10 11 12 13 14 15 in buffer 2\n");
	put(&buffer2, 10);
	put(&buffer2, 11);
	put(&buffer2, 12);
	put(&buffer2, 13);
	put(&buffer2, 14);

	printf("putting 6 7 8 9\n");
	put(&buffer, 6);
	put(&buffer, 7);
	put(&buffer, 8);
	put(&buffer, 9);

	printf("dump buffer....\n");
	dump(&buffer);

	printf("putting 10 11 12 13 14\n");
	put(&buffer, 10);
	put(&buffer, 11);
	put(&buffer, 12);
	put(&buffer, 13);
	put(&buffer, 14);

	printf("dump buffer....\n");
	dump(&buffer);
	
	if (isFull(&buffer))
	{
		printf("buffer FULL\n");
	}
	else 
	{
		printf("buffer NOT FULL\n");
	}

	printf("%d\n", get(&buffer));
	printf("%d\n", get(&buffer));
	printf("%d\n", get(&buffer));

	printf("dump buffer....\n");
	dump(&buffer);

	printf("%d\n", get(&buffer));
	printf("%d\n", get(&buffer));
	printf("%d\n", get(&buffer));
	printf("%d\n", get(&buffer));
	printf("%d\n", get(&buffer));
	printf("%d\n", get(&buffer));
	printf("%d\n", get(&buffer));

	printf("dump buffer 2....\n");
	dump(&buffer2);

	printf("%d\n", get(&buffer));
	printf("%d\n", get(&buffer));
	printf("%d\n", get(&buffer));
	printf("%d\n", get(&buffer));
	printf("%d\n", get(&buffer));
	printf("%d\n", get(&buffer));
	printf("%d\n", get(&buffer));
	printf("%d\n", get(&buffer));
	
	printf("dump buffer....\n");
	dump(&buffer);

	printf("dump buffer 2....\n");
	dump(&buffer2);

	if (isEmpty(&buffer))
	{
		printf("buffer EMPTY\n");
	}
	else
	{
		printf("buffer NOT EMPTY\n");
	}
	if (isFull(&buffer))
	{
		printf("buffer FULL\n");
	}
	else 
	{
		printf("buffer NOT FULL\n");
	}

	if (isEmpty(&buffer2)) 
	{
		printf("buffer 2 EMPTY\n");
	}
	else 
	{
		printf("buffer 2 NOT EMPTY\n");
	}
	
	if (isFull(&buffer2))
	{
		printf("buffer 2 FULL\n");
	}
	else 
	{
		printf("buffer 2 NOT FULL\n");
	}

	return 0;
}

