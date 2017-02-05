
public class Collection<T extends Comparable<T>>
{
	private Elem<T> first;
	private Elem<T> last;
	
	public void add(T val)
	{
		Elem<T> e = new Elem<T>(val);
		if(first == null)
		{
			first = last = e;
			return;
		}
		if(first == last)
		{
			if(first.val.compareTo(val) > 0)
				first = e;
			else
				last = e;
			first.next = last;
			last.prev = first;
			return;
		}
		if(last.val.compareTo(val) <= 0)
		{
			last.next = e;
			e.prev = last;
			last = e;
			return;
		}
		Elem<T> it = first;
		
		
		while(it != null)
		{
			if(val.compareTo(it.val) <= 0)
			{
				if(it == first)
				{
					first.prev = e;
					e.next = first;
					first = e;
				}
				else
				{
					e.prev = it.prev;
					e.next = it;
					it.prev.next = e;
					it.prev = e;
				}
				return;
			}
			it = it.next;
		}
		
	}
	
	public T getMin()
	{
		if (first == null)
			throw new RuntimeException();
		T min;
		if(first == last)
		{
			min = first.val;
			first = last = null;
		}
		else
		{
			min = first.val;
			first.next.prev = null;
			first = first.next;
		}
		return min;
	}
		
		
}
	

