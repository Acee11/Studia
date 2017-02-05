
public class Const extends Wyrazenie
{
	public int val;
	
	
	
	public Const(int v)
	{
		val = v;		
	}
	
	public void print() 
	{
		System.out.print(val);
	}

	public int oblicz() 
	{
		return val;
	}
	
}
