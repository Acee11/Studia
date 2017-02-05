import java.util.LinkedList;


public class Bufor<T>
{
	private LinkedList<T> bufor;
	private int capacity;
	public Bufor(int n)
	{
		bufor = new LinkedList<T>();
		capacity = n;
	}
	
	public synchronized boolean add(T elem)
	{
		if(bufor.size() >= capacity)
			return false;
		
		bufor.add(elem);
		return true;
	}
	
	public synchronized T get() throws Exception
	{
		if(bufor.size() == 0)
			throw new Exception();
		
		
		return bufor.removeFirst();
	}
	
	public synchronized int size()
	{
		return bufor.size();
	}
	
	public synchronized boolean empty()
	{
		return size() == 0;
	}
	
	public synchronized boolean full()
	{
		return size() == capacity;
	}
}
