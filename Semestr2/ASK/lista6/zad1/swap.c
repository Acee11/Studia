extern int buf[];

int *bufp0 = &buf[0];
static int *bufp1;


static void incr() 
{
	static int count = 0;
	count++;
}

void swap() 
{
	int temp;
	incr();
	bufp1 = &buf[1];
	temp = *bufp0;
	*bufp0 = *bufp1;
	*bufp1 = temp;
}

int main()
{
	return 0;
}


/*
	Symbole:
		swap.c     typ FILE     rozmiar: 0		   LOCAL    sekcja: ABS
		bufp1      typ OBJECT   rozmiar: 8 (int*)  LOCAL	sekcja: 5   (.bss)
		incr       typ FUNC     rozmiar: 22		   LOCAL	sekcja: 1   (.text)
		count.1835 typ OBJECT   rozmiar: 4 (int)   LOCAL	sekcja: 5   (.bss)
		bufp0	   typ OBJECT   rozmiar: 8 (int*)  GLOBAL	sekcja: 3   (.data)
		buf        typ NOTYPE   rozmiar: 0 (UND)   GLOBAL	sekcja: UND (?)
		swap	   typ FUNC	    rozmiar: 74		   GLOBAL	sekcja: 1   (.text)
*/

		