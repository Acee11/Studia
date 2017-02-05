import java.util.Scanner;
import java.util.Vector;

public class Game 
{
	private static final Scanner SCANNER = new Scanner(System.in);
	private static final CommandParser commandParser = new CommandParser();
	private Character character;
	private Room currentRoom;
	
	public void init(Room currentRoom)
	{
		this.currentRoom = currentRoom;
		int option = 0;
		System.out.println("Welcome!\n");
		while(option == 0)
		{
			System.out.println(
					 "What would you like to do?\n"
					+ "1.Start\n"
					+ "2.Help\n"
					+ "3.Exit\n");
			option = SCANNER.nextInt();
			
			switch(option)
			{
			case 1:
				start();
				break;
			case 2:
				writeHelp();
				option = 0;
				break;
			case 3:
				System.exit(0);
			default:
				System.out.println("Please select correct option!\n");
				option = 0;
			}
		}
	}
	
	public void start()
	{
		System.out.println("Please choose your class: \n"
				+ "1. Warrior\n"
				+ "2. Rogue\n"
				+ "3. Mage\n");
		int option = SCANNER.nextInt();
		character = new Character(CharacterClass.getCharacterClassByNum(option));
		System.out.println("To get help about command you can type \"help\"\nGood luck and have fun!\n");
		run();
	}
	
	public void writeHelp()
	{
		System.out.println("To look around and get information about the room you are in,\n type \"look around\"\n"
				+ "To go left/right/up/down type \"go left/right/up/down \"\n"
				+ "If doors are locked type \"unlock left/right/up/down\"\n"
				+ "To get information abouts you character type \"status\"\n"
				+ "To get information about item type \"info <item name>\"\n"
				+ "To take an item type \"take <item_name>\""
				);
	}
	
	public void run()
	{
		SCANNER.nextLine();
		while(true)
		{
			String command = SCANNER.nextLine();
			Token token = commandParser.parse(command.toLowerCase());
			executeToken(token);
		}
		
	}
	
	public void fight(Monster monster)
	{
		System.out.println("Fighting with:\n");
		System.out.println(monster.getInfo());
		while(true)
		{
			System.out.println("What do you want to do?");
			System.out.println("1.Attack");
			System.out.println("2.Heal Yourself");
			int option = SCANNER.nextInt();
			SCANNER.nextLine();
			if(option == 1)
			{
				monster.setHp(monster.getHp() - character.getMaxDmg());
				if(monster.getHp() <= 0)
				{
					System.out.println("You won! Exp gained: " + monster.getExp() + "\n");
					character.setExperience(character.getExperience() + monster.getExp());
					return;
				}
			}
			else if(option == 2)
			{
				character.heal();
			}
			else
			{
				System.out.println("Please select correct option!\n");
				continue;
			}
				
			character.setHp(character.getHp() - monster.getDmg());
			if(character.getHp() <= 0)
			{
				System.out.println("You are dead");
				System.out.println("Game Over");
				System.exit(0);
			}
			System.out.println("Your HP: " + character.getHp() + "/" + character.getMaxHp());
			System.out.println("Opponent HP: " + monster.getHp());
		}
	}
	
	public void executeToken(Token token)
	{
		if(token == null)
		{
			System.out.println("Please use correct command!");
		}
		else if(token.getType() == TokenType.STATUS)
		{
			System.out.println(character.getInfo());
		}
		else if(token.getType() == TokenType.EXIT)
		{
			System.exit(0);
		}
		else if(token.getType() == TokenType.LOOK_AROUND)
		{
			System.out.println(currentRoom.getInfo());
		}
		else if(token.getType() == TokenType.TAKE)
		{
			if(token.getAttr().equals("key"))
			{
				if(currentRoom.getKeyCounter() == 0)
				{
					System.out.println("No keys in this room");
				}
				else
				{
					System.out.println("Your took the key\n");
					currentRoom.setKeyCounter(currentRoom.getKeyCounter() - 1);
					character.setKeyCounter(character.getKeyCounter() + 1);
				}
				return;
			}
			Equipment item = null;
			for(int i = 0; i < currentRoom.getEqItems().size(); ++i)
			{
				Equipment itemTmp = currentRoom.getEqItems().get(i);
				if (itemTmp.getName().toLowerCase().equals(token.getAttr().toLowerCase()))
				{
					item = itemTmp;
					currentRoom.getEqItems().remove(i);
					break;
				}
			}
			if(item == null)
				System.out.println("No such item in this room!");
			else
			{
				System.out.println("You took the " + item.getName() + "\n");
				Equipment retItem;
				switch(item.getType())
				{
				case WEAPON:
					retItem = character.getEquipment().equip((Weapon)item);
					break;
				case BREASTPLATE:
					retItem = character.getEquipment().equip((Breastplate)item);
					break;
				case GREAVES:
					retItem = character.getEquipment().equip((Greaves)item);
					break;
				case GLOVES:
					retItem = character.getEquipment().equip((Gloves)item);
					break;
				case BOOTS:
					retItem = character.getEquipment().equip((Boots)item);
					break;
				default:
					retItem = null;
				}
				if(retItem != null)
					currentRoom.getEqItems().add(retItem);
			}
		}
		else if(token.getType() == TokenType.INFO)
		{
			for(Equipment eq : currentRoom.getEqItems())
			{
				if(token.getAttr().toLowerCase().equals(eq.getName().toLowerCase()))
				{
					System.out.println(eq.getInfo());
					break;
				}
			}
		}
		else if(token.getType() == TokenType.OPEN)
		{
			if(character.getKeyCounter() == 0)
			{
				System.out.println("You don't have enough keys!");
				return;
			}
			Passage pass;
			switch(token.getAttr())
			{
			case "up":
				pass = currentRoom.getUp();
				break;
			case "down":
				pass = currentRoom.getDown();
				break;
			case "left":
				pass = currentRoom.getLeft();
				break;
			case "right":
				pass = currentRoom.getRight();
				break;
			default:
				pass = null;
			}
			if(!pass.getIsLocked())
				System.out.println("These doors are not locked");
			else
			{
				System.out.println("Succesfully unlocked!");
				character.setKeyCounter(character.getKeyCounter() - 1);
				pass.setIsLocked(false);
			}
		}
		else if(token.getType() == TokenType.GO)
		{
			Passage pass;
			switch(token.getAttr())
			{
			case "up":
				pass = currentRoom.getUp();
				break;
			case "down":
				pass = currentRoom.getDown();
				break;
			case "left":
				pass = currentRoom.getLeft();
				break;
			case "right":
				pass = currentRoom.getRight();
				break;
			default:
				pass = null;
			}
			if(pass.getIsLocked())
				System.out.println("These doors are locked!");
			else
			{
				System.out.println("Going " + token.getAttr() + "...");
				currentRoom = pass.getDest();
				for(Monster monster : currentRoom.getMonsters())
				{
					fight(monster);
					while(character.getExperience() > character.getExpToNextLvl())
						character.levelUp();
				}
				currentRoom.setMonsters(new Vector<Monster>());
			}
		}
		else if(token.getType() == TokenType.HELP)
		{
			writeHelp();
		}
		else
		{
			System.out.println("Please use correct command!");
		}
	}
}
