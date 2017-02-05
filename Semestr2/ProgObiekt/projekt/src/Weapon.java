
public class Weapon extends Equipment 
{
	
	@Override
	public EqType getType() 
	{
		return EqType.WEAPON;
	}

	public Weapon() 
	{
		super();
	}

	public Weapon(int hpBenefit, int manaBenefit, int dmgBenefit, String name, ItemQuality quality, String info) 
	{
		super(hpBenefit, manaBenefit, dmgBenefit, name, quality, info);
	}
}
