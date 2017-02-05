
public class Producent implements Runnable 
{
	private String product;
	private int delay;
	private Bufor<String> buf;
	private Thread t;
	
	public Producent(Bufor<String> b, String p, int d)
	{
		buf = b;
		product = p;
		delay = d;
	}
	
	public void run()
	{
		System.out.println("Producing...\n");
		while(true)
		{
			if(!buf.full())
				buf.add(product);
			try 
			{
				Thread.sleep(delay);
			} 
			catch (InterruptedException e) 
			{
				e.printStackTrace();
			}
		}
	}
	
	public void start()
	{
		if(t == null)
		{
			t = new Thread(this, "ProducentThread");
			t.start();
		}
	}
}
