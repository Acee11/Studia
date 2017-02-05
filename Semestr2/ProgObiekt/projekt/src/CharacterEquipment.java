
public class CharacterEquipment implements Benefits,Info
{
	
	private Weapon weapon;
	private Breastplate breastplate;
	private Greaves greaves;
	private Gloves gloves;
	private Boots boots;
	
	CharacterEquipment()
	{
		this(new Weapon(), new Breastplate(), new Greaves(), new Gloves(), new Boots());
	}
	CharacterEquipment(Weapon weapon, Breastplate breastplate, Greaves greaves, Gloves gloves, Boots boots)
	{
		this.weapon = weapon;
		this.breastplate = breastplate;
		this.greaves = greaves;
		this.gloves = gloves;
		this.boots = boots;
	}
	public Weapon getWeapon() 
	{
		return weapon;
	}
	public void setWeapon(Weapon weapon) 
	{
		this.weapon = weapon;
	}
	public Breastplate getBreastplate() 
	{
		return breastplate;
	}
	public void setBreastplate(Breastplate breastplate) 
	{
		this.breastplate = breastplate;
	}
	public Greaves getGreaves() 
	{
		return greaves;
	}
	public void setGreaves(Greaves greaves) 
	{
		this.greaves = greaves;
	}
	public Gloves getGloves() 
	{
		return gloves;
	}
	public void setGloves(Gloves gloves) 
	{
		this.gloves = gloves;
	}
	public Boots getBoots() 
	{
		return boots;
	}
	public void setBoots(Boots boots) 
	{
		this.boots = boots;
	}
	
	public Equipment equip(Weapon item)
	{
		Equipment retItem = weapon;
		weapon = item;
		if(retItem.getName().equals("No Item"))
			return null;
		return retItem;
	}
	public Equipment equip(Breastplate item)
	{
		Equipment retItem = breastplate;
		breastplate = item;
		if(retItem.getName().equals("No Item"))
			return null;
		return retItem;
	}
	public Equipment equip(Greaves item)
	{
		Equipment retItem = greaves;
		greaves = item;
		if(retItem.getName().equals("No Item"))
			return null;
		return retItem;
	}
	public Equipment equip(Gloves item)
	{
		Equipment retItem = gloves;
		gloves = item;
		if(retItem.getName().equals("No Item"))
			return null;
		return retItem;
	}
	public Equipment equip(Boots item)
	{
		Equipment retItem = boots;
		boots = item;
		if(retItem.getName().equals("No Item"))
			return null;
		return retItem;
	}
	
	public String getInfo()
	{
		return "Weapon:\n" + weapon.getInfo() + "\n"
				+ "Breastplate: \n" + breastplate.getInfo() + "\n"
				+ "Greaves: \n" + greaves.getInfo() + "\n"
				+ "Gloves: \n" + gloves.getInfo() + "\n"
				+ "Boots: \n" + boots.getInfo();
				
	}
	
	@Override
	public int getHpBenefit() 
	{
		return weapon.getHpBenefit() + breastplate.getHpBenefit() + greaves.getHpBenefit() + gloves.getHpBenefit() + boots.getHpBenefit();
	}
	@Override
	public int getManaBenefit() 
	{
		return weapon.getManaBenefit() + breastplate.getManaBenefit() + greaves.getManaBenefit() + gloves.getManaBenefit() + boots.getManaBenefit();
	}
	@Override
	public int getDmgBenefit() 
	{
		return weapon.getDmgBenefit() + breastplate.getDmgBenefit() + greaves.getDmgBenefit() + gloves.getDmgBenefit() + boots.getDmgBenefit();
	}
}
