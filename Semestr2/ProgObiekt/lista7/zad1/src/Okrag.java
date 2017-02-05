
public class Okrag extends Figura 
{
	private double r;
	private double x, y;
	

	
	public Okrag(double x, double y, double r, String name)
	{
		super(name);
		this.x = x;
		this.y = y;
		this.r = r;
	}
	
	public String toString() 
	{
		return "Okrag " + name + ".\nSrodek w punkcie (" + x + ", " + y + ").\nPromien: " + r + "\n"; 
	}
	
	public void setx(double x)
	{
		this.x = x;
	}
	
	public void sety(double y)
	{
		this.y = y;
	}
	
	public void setr(double r)
	{
		this.r = r;
	}

	public void setName(String name)
	{
		this.name = name;
	}
}
