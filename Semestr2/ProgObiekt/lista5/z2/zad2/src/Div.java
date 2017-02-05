
public class Div extends Wyrazenie {

	public Div(Wyrazenie l, Wyrazenie r) 
	{
		super(l, r);
	}

	public void print() 
	{
		System.out.print("(");
		left.print();
		System.out.println(" / ");
		right.print();
		System.out.print(")");
	}

	public int oblicz() 
	{
		return left.oblicz() / right.oblicz();
	}

}
