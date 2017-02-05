
public enum CharacterClass 
{
	WARRIOR(2,1,1), ROGUE(1,2,1), MAGE(1,1,2);
	private int strBonus;
	private int agiBonus;
	private int intBonus;
	
	private CharacterClass(int str, int agi, int intel)
	{
		this.strBonus = str;
		this.agiBonus = agi;
		this.intBonus = intel;
	}
	
	public int getStrBonus() 
	{
		return strBonus;
	}

	public int getAgiBonus() 
	{
		return agiBonus;
	}

	public int getIntBonus() 
	{
		return intBonus;
	}
	
	public static CharacterClass getCharacterClassByNum(int n)
	{
		switch(n)
		{
		case 1:
			return WARRIOR;
		case 2:
			return ROGUE;
		case 3:
			return MAGE;
		default:
			return null;
		}
	}
}
