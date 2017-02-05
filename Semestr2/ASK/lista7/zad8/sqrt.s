.globl approx_sqrt
.text

approx_sqrt: #%xmm0 = x,   %xmm1 = epsilon
	movsd	%xmm0, %xmm2

loop:
	movsd	%xmm0, %xmm3
	divsd	%xmm2, %xmm3   #xmm2 = xn
	addsd	%xmm2, %xmm3	
	mulsd	half, %xmm3
bp:
	movsd	%xmm3, %xmm4
	subsd	%xmm2, %xmm4
	comisd	zero, %xmm4
	jae		continue
	mulsd 	minus_one, %xmm4
continue:
	comisd	%xmm1, %xmm4
	jb		exit
	movsd	%xmm3, %xmm2
	jmp 	loop
exit:
	movsd	%xmm3, %xmm0
	ret

.section .rodata
half: .double 0.5
zero: .double 0.0
minus_one: .double -1.0
