import java.util.Vector;

public class Room implements Info
{
	private Passage left;
	private Passage right;
	private Passage up;
	private Passage down;
	
	private Vector<Equipment> eqItems;
	private Vector<Monster> monsters;
	private int keyCounter;

	Room()
	{
		monsters = new Vector<Monster>();
		eqItems = new Vector<Equipment>();
		keyCounter = 0;
	}
	
	public Passage getLeft()
	{
		return left;
	}

	public void setLeft(Passage left) 
	{
		this.left = left;
	}

	public Passage getRight() 
	{
		return right;
	}

	public void setRight(Passage right) 
	{
		this.right = right;
	}

	public Passage getUp() 
	{
		return up;
	}

	public void setUp(Passage up) 
	{
		this.up = up;
	}

	public Passage getDown() 
	{
		return down;
	}

	public void setDown(Passage down) 
	{
		this.down = down;
	}

	public Vector<Equipment> getEqItems() 
	{
		return eqItems;
	}

	public void setEqItems(Vector<Equipment> items) 
	{
		this.eqItems = items;
	}
	
	public Vector<Monster> getMonsters() 
	{
		return monsters;
	}

	public void setMonsters(Vector<Monster> monsters) 
	{
		this.monsters = monsters;
	}

	public int getKeyCounter() 
	{
		return keyCounter;
	}

	public void setKeyCounter(int keyCounter) 
	{
		this.keyCounter = keyCounter;
	}
	
	public String getInfo()
	{
		String info = "";
		if(left != null)
		{
			info += "Left: " + left.getInfo() + "\n";
		}
		if(right != null)
		{
			info += "Right: " + right.getInfo() + "\n";
		}
		if(up != null)
		{
			info += "Up: " + up.getInfo() + "\n";
		}
		if(down != null)
		{
			info += "Down: " + down.getInfo() + "\n";
		}
		System.out.println("\nItems in this room:\n");
		for(Equipment item : eqItems)
			info += item.getInfo() + "\n";
		info += "Keys in this room: " + keyCounter;
		return info;
	}
	
	
	
}
