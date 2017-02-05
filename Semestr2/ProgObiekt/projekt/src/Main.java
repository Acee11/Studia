
public class Main {

	public static void main(String[] args) 
	{
		String info = "Item: God's sword\nHP Bonus: 999\nMP BOnus: 999\nDMG Bonus: 999\nQuality: Legendary";
		Weapon GodWeapon = new Weapon(999, 999, 999, "God's sword", ItemQuality.LEGENDARY, info);
		Room room = new Room();
		Game game = new Game();
		Room roomdown = new Room();
		roomdown.getMonsters().add(new Monster("Big Monster", 1000, 30, 1234));
		roomdown.getMonsters().add(new Monster());
		roomdown.getMonsters().add(new Monster());
		roomdown.getMonsters().add(new Monster());
		
		room.getEqItems().add(GodWeapon);
		room.setLeft(new Passage());
		room.setDown(new Passage(roomdown,true));
		room.setUp(new Passage());
		room.setKeyCounter(3);
		
		game.init(room);
	}

}
