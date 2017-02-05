.globl _start
.lcomm buf, 1
.text



_start:
	mov		$0, %rax # syscall number
	mov		$1, %rdi # stdin
	mov		$buf, %rsi
	mov		$1, %rdx
	syscall 			# read
	cmp		$0, %rax
	je exit
	jmp		toUpper
continue:
	mov 	$1, %rax #syscall number
	mov		$1, %rdi # stdout
	mov		$buf, %rsi # &
	mov		$1, %rdx # bytes
	syscall				# write
	jmp _start
	exit:
	mov		$60, %rax
	mov		$0, %rdi
	syscall

toUpper:		# 96 < %cl < 123
	cmp 	$96, (buf)
	jbe		toLower
	cmp 	$123, (buf)
	jae		toLower
	sub		$32, (buf)
	jmp 	continue

toLower:		# 64 < %cl < 91
	cmp 	$64, (buf)
	jbe		continue
	cmp 	$91, (buf)
	jae		continue
	add		$32, (buf)
	jmp 	continue

.data
str: .ascii "abcd"
