int relo3(int val) 
{
	switch (val) 
	{
		case 100:
		return(val);
		case 101:
		return(val+1);
		case 103: case 104:
		return(val+3);
		case 105:
		return(val+5);
		default:
		return(val+6);
	}
}

/*
0000000000000000 <relo3>:
   0:   8d 47 9c                lea    -0x64(%rdi),%eax
   3:   83 f8 05                cmp    $0x5,%eax
   6:   77 15                   ja     1d <relo3+0x1d>
   8:   89 c0                   mov    %eax,%eax
   a:   ff 24 c5 00 00 00 00    jmpq   *0x0(,%rax,8)
  11:   8d 47 01                lea    0x1(%rdi),%eax	case 101
  14:   c3                      retq   
  15:   8d 47 03                lea    0x3(%rdi),%eax	case 103,104
  18:   c3                      retq   
  19:   8d 47 05                lea    0x5(%rdi),%eax	case 105
  1c:   c3                      retq   
  1d:   8d 47 06                lea    0x6(%rdi),%eax	default
  20:   c3                      retq   
  21:   89 f8                   mov    %edi,%eax		case 100
  23:   c3                      retq
  */