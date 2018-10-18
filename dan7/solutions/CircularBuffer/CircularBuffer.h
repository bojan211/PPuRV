#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_

#include <stdbool.h>

#define BUFFER_SIZE 11
#define BUFFER_GET_ERROR (-1111111111)
#define BUFFER_TYPE_PRINT "d"

typedef int buffer_type;

typedef struct buffer_struct
{
	buffer_type buffer[BUFFER_SIZE];
	buffer_type* front;
	buffer_type* rear;
} buffer_struct;

void Init(buffer_struct* buf);

bool isEmpty(buffer_struct* buf);

bool isFull(buffer_struct* buf);

bool put(buffer_struct* buf, buffer_type x);

buffer_type get(buffer_struct* buf);

void empty(buffer_struct* buf);

void dump(buffer_struct* buf);

#endif /*CIRCULARBUFFER_H_*/
