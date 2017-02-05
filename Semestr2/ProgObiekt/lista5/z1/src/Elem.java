
public class Elem<T> 
{
	public Elem<T> prev;
	public T val;
	public Elem<T> next;
	
	public Elem(T v)
	{
		val = v;
	}
}
