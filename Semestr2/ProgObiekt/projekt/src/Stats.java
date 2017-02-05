public class Stats implements Benefits
{
	
	private int strength;
	private int agility;
	private int intelligence;
	
	Stats()
	{
		this(1,1,1);
	}
	
	Stats(int str, int agi, int intel)
	{
		this.strength = str;
		this.agility = agi;
		this.intelligence = intel;
	}
	
	public int getStrength() 
	{
		return strength;
	}
	public void setStrength(int strength) 
	{
		this.strength = strength;
	}
	public int getAgility() 
	{
		return agility;
	}
	public void setAgility(int agility) 
	{
		this.agility = agility;
	}
	public int getIntelligence() 
	{
		return intelligence;
	}
	public void setIntelligence(int intelligence) 
	{
		this.intelligence = intelligence;
	}
	
	public void addStats(int str, int agi, int intell)
	{
		strength += str;
		agility += agi;
		intelligence += intell;
	}
	
	@Override
	public int getHpBenefit() 
	{
		return 3 * strength;
	}
	@Override
	public int getManaBenefit() 
	{
		return 3 * intelligence;
	}
	@Override
	public int getDmgBenefit() 
	{
		return 3 * agility;
	}
}
