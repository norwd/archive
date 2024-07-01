#cpuid2.s Sample program to exteact the processor Vendor ID

#compile with either: 
# as -arch i386 -o cpuid2.o cpuid2.s
# ld -e _main -o cpuid2 cpuid2.o
# or
# gcc -gstabs -arch i386 cpuid2.s -o cpuid2
#
# run via ./cpuid2

#.section .data did not work
.data
output:
.asciz "The processor Vendor ID is '%s' \n"

.lcomm buffer, 13

#.section .text did not work
.text

.globl _main

	
_main:

	nop
	movl $0, %eax	# define cpuid output option
	cpuid			
	movl $buffer, %edi  # put values in string
	movl %ebx, 0(%edi)
	movl %edx, 4(%edi)
	movl %ecx, 8(%edi)
	movl $0, %ecx
	movl %ecx, 12(%edi)
	
	#From Mac OS X ABI Function Call Guide:  
	# "The stack is 16-byte aligned at the point of function calls.".

	subl $0x4, %esp #padding stack :/ !
	pushl $buffer
	pushl $output
	
	
	
	call _printf	#macosx need libc  pre_
	
	# ESP is at 0xXXXXXXX0 now, 
	# with MacOS X Special stub it will be at 0xXXXXXXXC 
	
    call _exit
	nop
	
	
