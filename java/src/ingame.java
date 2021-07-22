import java.io.File;
import java.util.Random;

class ingame {
	public static void battle_action() {
		all_items ait = new all_items();
		all_spares asp = new all_spares();
		all_attacks att = new all_attacks();
		hypersurf hy = new hypersurf();
		tools tool = new tools();
		splash sp = new splash();
		visuals vis = new visuals();
		Random ran = new Random();
		int attack_result;
		vis.main_options();
		switch (tool.user_input(1, 4, 0)) {
			case 1:
				switch ((ran.nextInt(16) + 1)) {
					case 8:
						attack_result = att.to_enemy_crit();
						break;
					default:
						attack_result = att.attack(1, 0);
						break;
				}
				switch (attack_result) {
					case 0:
						att.attack(1, 1);
						break;
				}
				hy.hopper(0);
				break;
			case 2:
				switch(ait.menu(0)) {
					case 2:
						att.attack(2, 1);
						break;
				}
				hy.hopper(0);
				break;
			case 3:
				switch (asp.spare()) {
					case 0:
						tool.clear_screen();
						vis.battle_header();
						vis.race_info();
						play_again();
						break;
					case 1:
						att.attack(3, 1);
						hy.hopper(0);
						break;
				}
				break;
			case 4:
				sp.splash_screen();
				break;
		}
	}
	public static void battle_conditions() {
		tools tool = new tools();
		hypersurf hy = new hypersurf();
		save_management sav = new save_management();
		record_management rec = new record_management();
		if (sav.read()[1] <= 0) {
			if (sav.read()[4] > 0) {
				rec.write(1);
				hy.hopper(1);
				System.out.println("\nYou died!");
				tool.pause(1000);
				play_again();
			}
			if (sav.read()[4] <= 0) {
				System.out.println("\nAn old-fashioned stalemate...");
				tool.pause(1000);
				play_again();
			}
		}
		if (sav.read()[1] > 0) {
			if (sav.read()[4] <= 0) {
				rec.write(0);
				hy.hopper(1);
				System.out.println("\nYou win!");
				tool.pause(1000);
				play_again();
			}
		}
	}
	public static void play_again() {
		tools tool = new tools();
		hypersurf hy = new hypersurf();
		splash sp = new splash();
		System.out.println("\nPlay again?\n\nYES [1]\nNO [2]\n");
		switch (tool.user_input(1, 2, 0)) {
			case 1:
				new File("temp.txt").delete();
				hy.hopper(0);
				break;
			case 2:
				sp.splash_screen();
				break;
		}
	}
}
