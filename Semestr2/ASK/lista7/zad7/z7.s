.globl _start
.lcomm buf, 1
.text



_start:
	sub		$1, %rsp
	mov		$0, %rax # syscall number
	mov		$1, %rdi # stdin
	mov		%rsp, %rsi
	mov		$1, %rdx
	syscall 			# read
continue:
	mov 	$1, %rax #syscall number
	mov		$1, %rdi # stdout
	mov		%rsp, %rsi # &
	mov		$1, %rdx # bytes
	syscall				# write
	jmp _start
	exit:
	mov		$1, %rax
	mov		$0, %rdi
	syscall

.data
str: .ascii "abcd"
