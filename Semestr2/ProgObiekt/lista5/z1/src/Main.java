import java.util.Random;


public class Main 
{
	public static void main(String[] args) 
	{
		Collection<Integer> c = new Collection<Integer>();
		Random gen = new Random();
		for(int i = 0; i < 2000; i++)
		{
			c.add(gen.nextInt(100));
		}
		
		for(int i = 0; i < 2000; i++)
		{
			System.out.print(c.getMin() + " ");
		}
	}

}
