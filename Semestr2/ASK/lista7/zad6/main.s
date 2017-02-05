.globl main
.type main, @function 
.lcomm buf, 19

main:
	push	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp	# (%rbp-8) = min    (%rbp-16) = max  
	movq	$0x7fffffffffffffff, %r8
	movq    %r8, -8(%rbp)
	movq	$0x8000000000000000, %r8
	movq   	%r8, -16(%rbp)

loop:
	movq	$0, %rax # syscall number
	movq	$1, %rdi # stdin
	movq	$buf, %rsi
	movq	$20, %rdx
	syscall 		# read
	cmp		$0, %rax
	je 		exit
	movq	$buf, %rdi
	call 	atol # %rax = atol(buf)
	cmp		$0, %rax
	je  	exit
	cmp		-8(%rbp), %rax
	jge		check_max
	movq	%rax, -8(%rbp)
check_max:
	cmp		-16(%rbp), %rax
	jle		continue
	movq	%rax, -16(%rbp)
continue:
	pushq	%rax
	jmp loop

exit:
	
	mov     $print_str, %rdi
	movq    -8(%rbp), %rsi
	xor		%rax, %rax
	call 	printf
	
	mov     $print_str, %rdi
	movq    -16(%rbp), %rsi
	xor		%rax, %rax
	call 	printf
bp:
	movq	$60, %rax
	movq	$0, %rdi
	syscall

.data
	print_str: .string "%d\n"
