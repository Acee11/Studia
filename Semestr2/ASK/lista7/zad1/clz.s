.globl clz
.type clz, @function
.text

clz:	#%rdi = n
	mov	 	$0, %rax
	mov		$64, %cl
	mov		$0xFFFFFFFFFFFFFFFF, %rbx
loop:
	test	%cl, %cl
	jz 		zero
	mov		%rdi, %rdx
	and		%rbx, %rdx
	jz 		zero
	mov 	%rdi, %rdx
	sar		$1, %cl
	sal 	%cl, %rbx
	and		%rbx, %rdx
	jz		nh_zero
	sar		$1, %cl
	sal 	%cl, %rbx
	jmp 	loop
nh_zero:
	add		%cl, %al
	sal	 	%cl, %rdi
	jmp 	loop
zero:
	add		%cl, %al
	ret

# n = [nH | nL]
# clz(n) = |n| , n = 0
# clz(n) = |nH| + clz(nL) , nH = 0
# clz(n) = clz(nH), nH =/= 0 


	