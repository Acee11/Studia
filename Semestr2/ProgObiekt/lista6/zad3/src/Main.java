
public class Main 
{
	public static void main(String[] args) 
	{
		Bufor<String> bufor = new Bufor(10);
		Producent prod = new Producent(bufor, "Produkt", 5000);
		Consumer cons = new Consumer(bufor, 1000);
		prod.start();
		cons.start();

	}

}
