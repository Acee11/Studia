
public class Token 
{
	private TokenType type;
	private String attr;
	
	Token()
	{
		this(null,null);
	}
	
	Token(TokenType type)
	{
		this(type, null);
	}
	
	Token(TokenType type, String attr)
	{
		this.type = type;
		this.attr = attr;
	}

	public TokenType getType() 
	{
		return type;
	}

	public String getAttr() 
	{
		return attr;
	}
}
