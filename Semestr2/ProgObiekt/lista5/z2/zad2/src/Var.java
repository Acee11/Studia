
public class Var extends Wyrazenie 
{
	String s;
	
	public Var(String str)
	{
		s = str;
		setVarValue(str, 0);
	}
	
	public Var(String str, int val)
	{
		s = str;
		setVarValue(str, val);
	}
	
	public void print()
	{
		System.out.print(s);
	}
	
	public int oblicz()
	{
		return getVarValue(s);
	}
	
}
