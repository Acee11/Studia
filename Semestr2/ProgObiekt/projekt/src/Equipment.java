
public abstract class Equipment implements Benefits, Info
{
	protected String name;
	protected int hpBenefit;
	protected int manaBenefit;
	protected int dmgBenefit;
	protected ItemQuality quality;
	protected String info;
	
	
	Equipment()
	{
		this(0, 0, 0, "No Item", ItemQuality.POOR, "No Item");
	}
	Equipment(int hpBenefit, int manaBenefit, int dmgBenefit, String name, ItemQuality quality, String info)
	{
		this.hpBenefit = hpBenefit;
		this.manaBenefit = manaBenefit;
		this.dmgBenefit = dmgBenefit;
		this.name = name;
		this.quality = quality;
		this.info = info;
	}
	
	public String getName() 
	{
		return name;
	}
	public void setName(String name) 
	{
		this.name = name;
	}
	public int getHpBenefit() 
	{
		return hpBenefit;
	}
	public void setHpBenefit(int hpBenefit) 
	{
		this.hpBenefit = hpBenefit;
	}
	public int getManaBenefit() 
	{
		return manaBenefit;
	}
	public void setManaBenefit(int manaBenefit) 
	{
		this.manaBenefit = manaBenefit;
	}
	public int getDmgBenefit() 
	{
		return dmgBenefit;
	}
	public void setDmgBenefit(int dmgBenefit) 
	{
		this.dmgBenefit = dmgBenefit;
	}
	public ItemQuality getQuality() 
	{
		return quality;
	}
	public void setQuality(ItemQuality quality) 
	{
		this.quality = quality;
	}
	public String getInfo() 
	{
		return info;
	}
	public abstract EqType getType();
	
}
