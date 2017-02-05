
public class Consumer implements Runnable 
{
	private Bufor<String> buf;
	private int delay;
	private Thread t;
	
	public Consumer(Bufor<String> b, int d)
	{
		buf = b;
		delay = d;
	}
	
	public void run()
	{
		System.out.println("Consuming...\n");
		while(true)
		{
			if(!buf.empty())
			{
				try 
				{
					System.out.println(buf.get() + ' ' + buf.size() + '\n');
				}
				catch (Exception e) 
				{
					System.out.println("Bufor is empty\n");
				}
			}
			
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
			t = new Thread(this, "ConsumerThread");
			t.start();
		}
		
	}
}
