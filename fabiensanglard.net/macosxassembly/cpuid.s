#cpuid.s Sample program to extract the processor Vendor ID

#compile with either: 
# as -arch i386 -o cpuid.o cpuid.s
# ld -e _main -o cpuid cpuid.o
# or
# gcc -arch i386 cpuid.s -o cpuid
#
# run via ./cpuid

#.section .data did not work
.data
output:
.ascii "The processor Vendor ID is 'xxxxxxxxxxxx'\n"
len = . - output

#.section .text did not work
.text

.globl _main

_syscall:
    int     $0x80   #   system interrupt
    ret
	
_main:
	movl $0, %eax		# define cpuid output option
	cpuid				# duh
	movl $output, %edi	# put values in the string
	movl %ebx, 28(%edi)
	movl %edx, 32(%edi)
	movl %ecx, 36(%edi)
    pushl   $len        #   push the length of the string on stack
    pushl   $output     #   push @ of the string on stack
    pushl   $1          #   output are sent on normal (1) use 2 for error
    movl    $4, %eax    # SYS_write (4)
    call    _syscall
	#int     $0x80

	
    add     $12, %esp   #   clear stack (we pushed 3 args)
    pushl   $0          #   we want to call exit(0), push 0
    movl    $1, %eax    # SYS_exit=1
    call    _syscall
	#int     $0x80
	
    leave
    ret
