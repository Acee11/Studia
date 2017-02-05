
public class CommandParser 
{
	
	public Token parse(String text)
	{
		String[] parts = text.split(" ");
		
		if(parts.length == 1)
		{
			switch(parts[0])
			{
			case "status":
				return new Token(TokenType.STATUS);
			case "exit":
				return new Token(TokenType.EXIT);
			case "help":
				return new Token(TokenType.HELP);
			default:
				return null;
			}
		}
		
		else if(parts.length > 1)
		{
			if(parts[0].equals("go"))
					return new Token(TokenType.GO, parts[1]);
			else if(parts[0].equals("look"))
				return new Token(TokenType.LOOK_AROUND);
			else if(parts[0].equals("take"))
			{
				String p = parts[1];
				for(int i = 2; i < parts.length; ++i)
					p += " " + parts[i];
				return new Token(TokenType.TAKE, p);
			}
			else if(parts[0].equals("info"))
			{
				String p = parts[1];
				for(int i = 2; i < parts.length; ++i)
					p += " " + parts[i];
				return new Token(TokenType.INFO, p);
			}
			else if(parts[0].equals("open"))
			{
				return new Token(TokenType.OPEN,parts[1]);
			}
				
		}
		
		return null;
	}
}
