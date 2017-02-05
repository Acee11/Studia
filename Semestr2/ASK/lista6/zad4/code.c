int function(int x1, int x2)
{
	return x1 & x2;
}

void g()
{
	int n = 10;
	while(n > 0)
		n--;
}

int main()
{
	g();
	function(13, 37);
	g();
	return 0;
}