#include "CircularBuffer.h"

#include <stdio.h>
#include <stddef.h>


void Init(buffer_struct* buf)
{
	buf->rear = buf->buffer;
	buf->front = buf->buffer;
}


bool isEmpty(buffer_struct* buf)
{
	if (buf->front == buf->rear)
		return true;
	return false; 
}


bool isFull(buffer_struct* buf)
{
	if (buf->front == (buf->rear + 1))
		return true;
	if ((buf->rear == &(buf->buffer[BUFFER_SIZE - 1])) && (buf->front == &(buf->buffer[0])))
		return true;
	return false; 
}


bool put(buffer_struct* buf, buffer_type x)
{
	if (isFull(buf))
		return false;
	*(buf->rear) = x;
	buf->rear++;
	if (buf->rear == &(buf->buffer[BUFFER_SIZE]))
		buf->rear = &(buf->buffer[0]);
	return true;
}


buffer_type get(buffer_struct* buf)
{
	if (isEmpty(buf))
		return BUFFER_GET_ERROR;
	buffer_type x;
	x = *(buf->front);
	buf->front++;
	if (buf->front == &(buf->buffer[BUFFER_SIZE]))
		buf->front = &(buf->buffer[0]);
	return x;
}


void empty(buffer_struct* buf)
{
	(buf->front) = (buf->rear) = &(buf->buffer[0]);
}


void dump(buffer_struct* buf)
{
	if (isEmpty(buf))
		return;
	buffer_type* current = NULL;
	current = buf->front;
	do
	{
		printf ("element: %"BUFFER_TYPE_PRINT"\n",*current);
		current++;
		if (current == &(buf->buffer[BUFFER_SIZE]))
			current = &(buf->buffer[0]);
	}
	while (!(current == (buf->rear)));
}
