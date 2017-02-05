long adds(long x, long y)
{
	// %rdi = x		%rsi = y
	asm
	(    //Assmbler Template:
		"mov %%rdi, %%rdx\n"
		"add %%rsi, %%rdx\n"
		"mov %%rdx, %%rbx\n"
		"shr $63, %%rbx\n"
		"cmp $1, %%rbx\n"
		"je l1"
		""
	:	 			//Output Operands
	:	 			//Input Operands
	: "rdx", "rbx"			//Clobbers
	: "l1" 			//Goto Labels
	)
}