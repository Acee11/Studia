
public class Main 
{

	public static void main(String[] args) 
	{
		Wyrazenie w = new Mult(new Sub(new Var("ef iks delta iks",1), new Const(2)), new Add(new Const(3) ,new Const(4)) );
		w.print();
		System.out.println();
		System.out.println(w.oblicz());
	}

}
