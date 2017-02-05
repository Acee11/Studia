
public class Mult extends Wyrazenie {

	public Mult(Wyrazenie l, Wyrazenie r) 
	{
		super(l, r);
	}

	public void print() 
	{
		System.out.print("(");
		left.print();
		System.out.print(" * ");
		right.print();
		System.out.print(")");
	}

	public int oblicz() 
	{
		return left.oblicz() * right.oblicz();
	}

}
