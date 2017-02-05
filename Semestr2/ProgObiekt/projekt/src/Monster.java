
public class Monster implements Info
{
	private String name;
	private int hp;
	private int dmg;
	private int exp;
	
	
	Monster()
	{
		this("Basic Monster", 10, 4, 50);
	}
	Monster(String name, int hp, int dmg, int exp)
	{
		this.name = name;
		this.hp = hp;
		this.dmg = dmg;
		this.exp = exp;
	}
	
	public String getName() 
	{
		return name;
	}
	public void setName(String name) 
	{
		this.name = name;
	}
	public int getHp() 
	{
		return hp;
	}
	public void setHp(int hp) 
	{
		this.hp = hp;
	}
	public int getDmg() 
	{
		return dmg;
	}
	public void setDmg(int dmg) 
	{
		this.dmg = dmg;
	}
	public int getExp() 
	{
		return exp;
	}
	public void setExp(int exp) 
	{
		this.exp = exp;
	}
	public String getInfo()
	{
		return "Monster: " + name + "\n" + "HP: " + hp + "\n" + "DMG: " + dmg + "\n";
	}
}
