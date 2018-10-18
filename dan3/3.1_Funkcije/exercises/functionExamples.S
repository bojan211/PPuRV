	.include "defines.h"

	.data
hello:
	.string "hello from assembly function\n"

	.globl	printMessage
	.global sumAsm

printMessage:
	movl	$SYS_write,%eax
	movl	$STDOUT,%ebx
	movl	$hello,%ecx
	movl	$29,%edx
	int	$0x80
	ret

sumAsm:
	pushl	%ebp;
	movl	%esp, %ebp;
	movl	0x8(%ebp), %eax;
	movl	0xC(%ebp), %ecx;
	addl	%ecx, %eax;
	popl	%ebp;
	ret
