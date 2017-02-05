.globl	lcm_gcd
.type 	lcm_gcd, @function
.size	lcm_gcd, .-lcm_gcd

.text
lcm_gcd:	#rdi -> a	#rsi -> b
	pushq	%rsi
	pushq	%rdi
gcd:
	testq	%rsi, %rsi
	jz		lcm
	movq 	$0, %rdx
	movq	%rdi, %rax
	divq	%rsi	#%rdx = a % b
	xchg	%rdi, %rsi
	movq	%rdx, %rsi
	jmp gcd
lcm:	#%rdi = gcd(a,b)
	popq	%rax
	imulq	(%rsp), %rax #rax = a * b
	movq	$0, %rdx
	idiv	%rdi #%rax = a * b / gcd(a,b)
	movq	%rdi, %rdx
	addq	$8, %rsp
	retq
