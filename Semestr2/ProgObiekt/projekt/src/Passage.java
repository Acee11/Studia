
public class Passage implements Info
{
	private Room dest;
	private boolean isLocked;
	
	
	Passage()
	{
		this(new Room(), false);
	}
	Passage(Room dest, boolean isLocked)
	{
		this.dest = dest;
		this.isLocked = isLocked;
	}
	
	public Room getDest() 
	{
		return dest;
	}
	public void setDest(Room dest) 
	{
		this.dest = dest;
	}
	public boolean getIsLocked() 
	{
		return isLocked;
	}
	public void setIsLocked(boolean isLocked) 
	{
		this.isLocked = isLocked;
	}
	
	public String getInfo()
	{
		if(isLocked)
		{
			return "These doors are locked. You can open it with a key";
		}
		else
		{
			return "You can go there";
		}
	}
}
