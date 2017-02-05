.globl fibbonaci
.type fibbonaci, @function
.size fibbonaci, .-fibbonaci
.text

fibbonaci:
	push	%rbp
	mov		%rsp, %rbp
	cmp		$2, %rdi
	jbe		base
	push	%rdi
	sub		$1, %rdi
	call	fibbonaci #%rax = fibbonaci(n - 1)
	pop		%rdi
	push	%rax
	sub		$2, %rdi
	call 	fibbonaci
	add		-8(%rbp), %rax
	add		$8, %rsp
	jmp 	ret
base:
	mov		$1, %rax
ret:
	pop		%rbp
	ret
	