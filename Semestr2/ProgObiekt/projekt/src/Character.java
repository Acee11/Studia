
public class Character implements Info
{
	private CharacterClass charClass;
	
	

	private int level;
	private int experience;
	private int expToNextLvl;
	
	private int hp;
	private int mana;
	private int baseDmg;
	
	private Stats stats;
	private CharacterEquipment equipment;
	private int keyCounter;
	
	

	Character()
	{
		this(CharacterClass.WARRIOR, 1, 0, 100, 100, 100, 10,
				new Stats(CharacterClass.WARRIOR.getStrBonus(), CharacterClass.WARRIOR.getAgiBonus(), CharacterClass.WARRIOR.getIntBonus()),
				new CharacterEquipment(), 0);
	}
	
	Character(CharacterClass charClass)
	{
		this(charClass, 1, 0, 100, 100, 100, 10,
				new Stats(charClass.getStrBonus(), charClass.getAgiBonus(), charClass.getIntBonus()),
				new CharacterEquipment(), 0);
		
	}
	
	Character(CharacterClass charClass, int level, int experience, int expToNextLvl, int hp, int mana, int baseDmg,
			Stats stats, CharacterEquipment equipment, int keyCounter)
	{
		this.level = level;
		this.experience = experience;
		this.expToNextLvl = expToNextLvl;
		this.baseDmg = baseDmg;
		this.stats = stats;
		this.equipment = equipment;
		this.charClass = charClass;
		this.keyCounter = keyCounter;
		this.hp = getMaxHp();
		this.mana = getMaxMana();
	}
	public int getKeyCounter() 
	{
		return keyCounter;
	}

	public void setKeyCounter(int keyCounter) 
	{
		this.keyCounter = keyCounter;
	}
	public int getLevel() 
	{
		return level;
	}
	public void setLevel(int level) 
	{
		this.level = level;
	}
	public int getExperience() 
	{
		return experience;
	}
	public void setExperience(int experience) 
	{
		this.experience = experience;
	}
	public int getExpToNextLvl() 
	{
		return expToNextLvl;
	}
	public int getMaxDmg()
	{
		return baseDmg + stats.getDmgBenefit() + equipment.getDmgBenefit();
	}
	public int getMaxHp() 
	{
		return 100 + stats.getHpBenefit() + equipment.getHpBenefit();
	}
	public int getMaxMana() 
	{
		return 100 + stats.getManaBenefit() + equipment.getManaBenefit();
	}
	public int getBaseDmg() 
	{
		return baseDmg;
	}
	public void setBaseDmg(int baseDmg) 
	{
		this.baseDmg = baseDmg;
	}
	public int getHp() 
	{
		return hp;
	}
	public void setHp(int hp) 
	{
		this.hp = hp;
	}
	public int getMana() 
	{
		return mana;
	}
	public void setMana(int mana) 
	{
		this.mana = mana;
	}
	public CharacterEquipment getEquipment() 
	{
		return equipment;
	}
	public void setEquipment(CharacterEquipment equipment) 
	{
		this.equipment = equipment;
	}
	public Stats getStats() 
	{
		return stats;
	}
	public void setStats(Stats stats) 
	{
		this.stats = stats;
	}
	
	public void heal()
	{
		if(mana >= 50)
		{
			hp = Math.max(hp + 35 + stats.getIntelligence(), getMaxHp());
			mana -= 50;
		}
	}

	public void levelUp()
	{
		++level;
		System.out.println("Congratulations! You leveled up to level " + level + "\n");
		expToNextLvl *= 2;
		stats.addStats(charClass.getStrBonus(), charClass.getAgiBonus(), charClass.getIntBonus());
		hp = getMaxHp();
		mana = getMaxMana();
	}
	public String getInfo()
	{
		String info = "";
		info += "Level: " + level + "\nExperience: " + experience + " / " + expToNextLvl + "\n";
		info += "HP: " + hp + " / " + getMaxHp() + "\n";
		info += "Mana: " + mana + " / " + getMaxMana() + "\n";
		info += "\n" + equipment.getInfo() + "\n";
		info += "Keys: " + keyCounter + "\n";
		return info;
	}
	
	
}
