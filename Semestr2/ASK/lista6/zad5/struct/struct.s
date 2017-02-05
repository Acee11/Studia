	.file	"struct.c"
	.data
	.align 16
	.type	baz, @object
	.size	baz, 24
baz:
	.ascii	"abc"
	.zero	1
	.long	42
	.quad	-3
	.long	1068827777
	.zero	4
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	baz+8(%rip), %rdx
	movl	baz+4(%rip), %eax
	cltq
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, baz+8(%rip)
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.2.1-22ubuntu2) 5.2.1 20151010"
	.section	.note.GNU-stack,"",@progbits
