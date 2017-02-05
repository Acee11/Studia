	.file	"zad2.c"
	.text
	.globl	randwalk
	.type	randwalk, @function
randwalk:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16					# k   | -24(%rbp)
	.cfi_offset 6, -16						# dir | -8(%rbp)
											# sum | -28(%rbp)
	movq	%rsp, %rbp						# d   | -12(%rbp)
	.cfi_def_cfa_register 6					# i   | -20(%rbp)
	subq	$48, %rsp						# arr | -40(%rbp)
	movl	%esi, -44(%rbp)					# n   | -44(%rbp)
	movl	%edx, -48(%rbp)					# len | -48(%rbp)
	movq	%rdi, -40(%rbp)					# j   | -16(%rbp)
	movl	$0, -28(%rbp)
	movl	$0, -24(%rbp)
	movq	$0, -8(%rbp)
	movl	$0, %eax
	call	fast_random
	cltd
	idivl	-44(%rbp)
	movl	%edx, -20(%rbp)
	movl	$0, %eax
	call	fast_random
	cltd
	idivl	-44(%rbp)
	movl	%edx, -16(%rbp)
.L10:
	subl	$2, -24(%rbp)		#k -= 2
	cmpl	$0, -24(%rbp)		
								# if k >= 0 goto .L2
	cmovll	$62, -24(%rbp)		# k = 62
	movl	$0, %eax			
	call	fast_random
	cltq
	movl    -24(%rbp), %esi
	subl    $62, %esi
	cmpl	$0, %esi	
	cmovql	%rax, -8(%rbp)		# dir = fast_random()


	movl	-24(%rbp), %eax
	movq	-8(%rbp), %rdx
	movl	%eax, %ecx		#dir = rdx
	shrq	%cl, %rdx		
	movq	%rdx, %rax
	andl	$3, %eax
	movl	%eax, -12(%rbp)

	movl	-20(%rbp), %eax
	imull	-44(%rbp), %eax #eax = i * n
	movl	%eax, %edx
	movl	-16(%rbp), %eax
	addl	%edx, %eax		#eax - i * n + j
	movslq	%eax, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	addl	%eax, -28(%rbp) # sum += arr[i * n + j]

	# if (d == 0)	
	cmpl	$0, -12(%rbp) # if (d != 0) goto .L3
	cmovle   $1, %esi
	cmovlnz  $0, %esi
	cmpl	$0, -20(%rbp)
	cmovlg   $1, %edi
	cmovlle  $0, %edi
	imull   %edi, %esi
	subl    %esi, -20(%rbp)

	# if (d == 1)
	cmpl	$1, -12(%rbp)  	
	cmovle   $1, %esi
	cmovlnz  $0, %esi
	movl	-44(%rbp), %eax
	subl	$1, %eax
	cmpl	-20(%rbp), %eax
	cmovlg   $1, %edi
	cmovlle  $0, %edi
	imull	%edi, %esi
	addl	%esi, -20(%rbp)

	# if (d == 2)
	cmpl	$2, -12(%rbp)
	cmovle   $1, %esi
	cmovlnz  $0, %esi
	cmpl	$0, -16(%rbp)
	cmovlg   $1, %edi
	cmovlle  $0, %edi
	imull   %edi, %esi
	subl	%esi, -16(%rbp)

	#else
	movl	-44(%rbp), %eax
	subl	$1, %eax
	cmpl	-16(%rbp), %eax
	cmovlg	$1, %edi			
	cmovlel  $0, %edi
	addl	%edi, -16(%rbp)

	#koniec petli
	subl	$1, -48(%rbp)
	cmpl	$0, -48(%rbp)
	jne	.L10				# if (--len != 0) goto .L10

	movl	-28(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	randwalk, .-randwalk
	.ident	"GCC: (Ubuntu 5.2.1-22ubuntu2) 5.2.1 20151010"
	.section	.note.GNU-stack,"",@progbits
