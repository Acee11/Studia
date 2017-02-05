	.file	"zad2.c"
	.comm	A,3640,32
	.text
	.globl	store_elem
	.type	store_elem, @function
store_elem:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdx, %r8
	movq	%rsi, %rax
	addq	%rax, %rax
	addq	%rsi, %rax
	salq	$2, %rax
	addq	%rsi, %rax
	movq	%rdi, %rdx
	salq	$6, %rdx
	addq	%rdi, %rdx
	addq	%rdx, %rax
	addq	%r8, %rax
	movq	A(,%rax,8), %rax
	movq	%rax, (%rcx)
	movl	$3640, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	store_elem, .-store_elem
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.2.1-22ubuntu2) 5.2.1 20151010"
	.section	.note.GNU-stack,"",@progbits
