.globl insert_sort
.type insert_sort, @function
.size .insert_sort, .-insert_sort

insert_sort: #%rdi = &poczatek  %rsi = &koniec
	addq	$8, %rsi
	movq	%rdi, %rax	# %rax = x

# stan poczatkowy:
#  | | | | | | | | |
#    ^             ^
#  %rax	          %rsi

# petla:
#  posortowane
#  \/ \/ \/
#  | | | | | | | | | | | | |
#            ^     ^       ^
#   	 <--%rdx  %rax    %rsi


#rax - x        rdx - iterator

loop:
	addq	$8, %rax
	cmp		%rax, %rsi
	jz 		exit
	movq	%rax, %rdx
inner_loop:
	cmp		%rdx, %rdi
	je      f
	movq	-8(%rdx), %r8
	cmp		%r8, (%rax)
	jge		f
	subq	$8, %rdx
	jmp 	inner_loop
f:
	movq	(%rdx), %r8
	movq	(%rax), %r9
	movq	%r9, (%rdx)
	addq	$8, %rdx
found_loop:
	cmp		%rax, %rdx
	jg 		loop
	movq	(%rdx), %r9
	movq	%r8, (%rdx)
	movq	%r9, %r8
	addq	$8, %rdx
bp:
	jmp found_loop
exit:
	retq


	