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
		int rand = (ran.nextInt(16) + 1);
		int res, itres, spret;
		vis.main_options();
		switch (tool.user_input(1, 4, 0)) {
			case 1:
				switch (rand) {
					case 8:
						res = att.to_enemy_crit();
						break;
					default:
						res = att.to_enemy();
						break;
				}
				switch (res) {
					case 0:
						att.to_you(1);
						break;
				}
				hy.hopper(0);
				break;
			case 2:
				switch(ait.menu(0)) {
					case 2:
						att.to_you(2);
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
						att.to_you(1);
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
		save_management save = new save_management();
		record_management rec = new record_management();
		int[] i = save.read();
		int Player_Health = i[1];
		int Enemy_Health = i[4];
		if (Player_Health < 0) {
			Player_Health = 0;
		}
		if (Enemy_Health < 0) {
			Enemy_Health = 0;
		}
		if (Player_Health <= 0) {
			if (Enemy_Health > 0) {
				rec.write(1);
				hy.hopper(1);
				System.out.println("\nYou died!");
				tool.pause(1000);
				play_again();
			}
			if (Enemy_Health <= 0) {
				System.out.println("\nAn old-fashioned stalemate...");
				tool.pause(1000);
				play_again();
			}
		}
		if (Player_Health > 0) {
			if (Enemy_Health <= 0) {
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
		File fi = new File("temp.txt");
		System.out.println("\nPlay again?\n\nYES [1]\nNO [2]\n");
		switch (tool.user_input(1, 2, 0)) {
			case 1:
				fi.delete();
				hy.hopper(0);
				break;
			case 2:
				sp.splash_screen();
				break;
		}
	}
}
