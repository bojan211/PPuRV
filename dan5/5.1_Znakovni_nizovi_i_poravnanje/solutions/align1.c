#include <stdio.h>
#include <stdint.h>

//#pragma pack(push)  /* push current alignment to stack */
//#pragma pack(2)     /* set alignment to 1 byte boundary */

typedef struct _example_struct
{
	uint8_t   char_a;
	uint32_t  uint_b;
	uint16_t  short_c;
	uint16_t  short_d;
} example_struct;
//} __attribute__ ((packed)) example_struct;

//#pragma pack(pop)   /* restore original alignment from stack */

typedef union _my_union
{
	uint32_t  uint_a;
	uint16_t  ushort_s[2]; 
	uint8_t   uchar_c[5];
  
} my_union;


int main(void)
{	
	int8_t          arr1[3];
	int8_t          arr2[1];
	example_struct  ex_struct;
	my_union        ex_union;
	
	ex_union.uint_a       = 0xFFFFEEDD;
	ex_union.ushort_s[0]  = 0XDD; 
	ex_union.ushort_s[1]  = 0XEE;
	ex_union.uchar_c [0]  = 0XDD;
	ex_union.uchar_c [1]  = 0XEE;
	ex_union.uchar_c [2]  = 0XAA;
	ex_union.uchar_c [3]  = 0XFF;
	ex_union.uchar_c [4]  = 0X77;
	
	printf ("Printing information about structure------------------------------------\n");	
	printf("arr1     size %d  \taddr: %p (4-byte alligned: %s)\n", sizeof(arr1),  &arr1,      ((uintptr_t)(&arr1)%4)      ? "NO" : "YES");
	printf("arr2     size %d  \taddr: %p (4-byte alligned: %s)\n", sizeof(arr2),  &arr2,      ((uintptr_t)(&arr2)%4)      ? "NO" : "YES");
	printf("struct   size %d  \taddr: %p (4-byte alligned: %s)\n", sizeof(example_struct), &ex_struct, ((uintptr_t)(&ex_struct)%4) ? "NO" : "YES");
	
	printf ("Printing information about union------------------------------------\n");
	printf ("union addres: %p\t union size %d\t address of uint_a uniom member: %p\tvalue of uint_a: %x\n", \
	       &ex_union, sizeof(ex_union), &(ex_union.uint_a), ex_union.uint_a);
	       
	printf ("union addres: %p\t union size %d\t address of ushort_s uniom member: %p\tvalue of ushort_s[1]: %x\t"\
	       "value of ushort_s[0]: %x\n", &ex_union, sizeof(ex_union), &(ex_union.ushort_s), ex_union.ushort_s[1],\
	       ex_union.ushort_s[0]);
	       
	printf ("union addres: %p\t union size %d\t address of uchar_c uniom member: %p\tvalue of uchar_c[4]: %x\t"\
	       "\tvalue of ushort_s[3]: %x\nvalue of ushort_s[2]: %x\tvalue of ushort_s[1]: %x\tvalue of ushort_s[0]: %x\n", &ex_union, \
	       sizeof(ex_union), &(ex_union.uchar_c),ex_union.uchar_c[4], ex_union.uchar_c[3], ex_union.uchar_c[2], ex_union.uchar_c[1],\
	        ex_union.uchar_c[0]);
	       	
	
	return 0;
}

