extern int x;
void g()
{
	x = 5;
}

void f()
{
	g();
	x++;
}