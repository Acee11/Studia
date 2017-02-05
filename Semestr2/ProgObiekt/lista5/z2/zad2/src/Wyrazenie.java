import java.util.HashMap;
import java.util.Map;


public abstract class Wyrazenie
{
	protected Wyrazenie left;
	protected Wyrazenie right;
	protected static Map<String, Integer> varValues = new HashMap<String, Integer>();
	public Wyrazenie()
	{
		super();
	}
	public Wyrazenie(Wyrazenie l, Wyrazenie r)
	{
		left = l;
		right = r;
	}
	public static void setVarValue(String var, int val)
	{
		varValues.put(var, val);
	}
	public static int getVarValue(String var)
	{
		return varValues.get(var);
	}
	public abstract void print();
	public abstract int oblicz();
	
}
