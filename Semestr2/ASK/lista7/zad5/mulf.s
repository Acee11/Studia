.globl mulf
.type mulf. @function

mulf:	# %edi = a    %esi = b
	mov		%edi, %eax
	shl		$9, %eax
	and		$0xfffffe00, %eax
	mov		%esi, %ebx
	shl		$9, %ebx
	and		$0xfffffe00, %ebx
	xor		%rdx, %rdx  # Mantysa:
	mul		%ebx	# %edx = M1 * M2
	add		%ebx, %edx	# %edx = M1 * M2 + M2
	mov		%edi, %ebx
	shl		$9, %ebx
	and		$0xfffffe00, %ebx
	add		%ebx, %edx  # %edx = M1 * M2 + M1 + M2

	mov		%edx, %eax # %eax = M1 * M2 + M1 + M2
					   # Wykladnik:
	shr		$9, %eax
	mov		%edi, %ebx 
	shr		$23, %ebx
	#and	$0x7f800000, %ebx
	mov		%esi, %ecx 
	shr		$23, %ecx
	add		%cl, %bl
	#shr	$23, %ebx
	sub		$127, %bl
	shl		$23, %ebx
	and		$0x7fffff, %eax
	and		$0x7f800000, %ebx
	or		%ebx, %eax

	xor		%edi, %esi
	and		$0x80000000, %esi
	and 	$0x7fffffff, %eax
	or		%esi, %eax
bp:
	ret
