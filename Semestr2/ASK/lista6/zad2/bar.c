#include <stdio.h>

char main;

void p2() 
{
	//main = 0x55;
	printf("0x%x\n", main);
}

/*

0000000000400536 <main>:
  400536:       55                      push   %rbp
  400537:       48 89 e5                mov    %rsp,%rbp
  40053a:       e8 07 00 00 00          callq  400546 <p2>
  40053f:       b8 00 00 00 00          mov    $0x0,%eax
  400544:       5d                      pop    %rbp
  400545:       c3                      retq   

*/