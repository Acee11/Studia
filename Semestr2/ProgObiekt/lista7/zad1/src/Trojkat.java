
public class Trojkat extends Figura
{
	private double x1, y1, x2, y2, x3, y3;
	
	public Trojkat(double x1, double y1, double x2, double y2, double x3, double y3, String name)
	{
		super(name);
		this.x1 = x1;
		this.y1 = y1;
		this.x2 = x2;
		this.y2 = y2;
		this.x3 = x3;
		this.y3 = y3;
	}
	
	public String toString() 
	{
		return "Trojkat " + name + ".\nA = " + pkt(x1,y1) + "\nB = " + pkt(x2,y2) + "\nC = " + pkt(x3,y3);
	}
	
	public static String pkt(double x, double y)
	{
		return "(" + x + ", " + y + ")";
	}

	public void update(String name, double x1, double y1, double x2, double y2, double x3, double y3)
	{
		this.name = name;
		this.x1 = x1;
		this.y1 = y1;
		this.x2 = x2;
		this.y2 = y2;
		this.x3 = x3;
		this.y3 = y3;
	}
}
