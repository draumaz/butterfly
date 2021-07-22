import java.util.Random;

class char_data {
	public int[] stats_gen() {
		Random ran = new Random();
		int[] i = new int[9];
		i[6] = 0;
		i[7] = 0;
		i[8] = 0;
		switch((ran.nextInt(5) + 1)) {
			case 1:
				i[0] = 1; // Vuleen
				i[1] = 20;
				i[2] = 10;
				break;
			case 2:
				i[0] = 2; // Aradi
				i[1] = 30;
				i[2] = 15;
				break;
			case 3:
				i[0] = 3; // Human
				i[1] = 20;
				i[2] = 7;
				break;
			case 4:
				i[0] = 4; // Lycan
				i[1] = 16;
				i[2] = 32;
				break;
			case 5:
				i[0] = 5; // Jodum
				i[1] = 24;
				i[2] = 16;
				break;
		}
		switch((ran.nextInt(5) + 1)) {
			case 1:
				i[3] = 1; // Darak
				i[4] = 25;
				i[5] = 10;
				break;
			case 2:
				i[3] = 2; // Goblin
				i[4] = 12;
				i[5] = 7;
				if ((ran.nextInt(14) + 1) == 12) {
					i[3] = 4; // ULTRA GOBLIN
					i[4] = 40;
					i[5] = 15;
				}
				break;
			case 3:
				i[3] = 3; // Arcran
				i[4] = 30;
				i[5] = 5;
				break;
			case 4:
				i[3] = 5; // Sleech
				i[4] = 12;
				i[5] = 36;
				break;
			case 5:
				i[3] = 6; // Wimble
				i[4] = 27;
				i[5] = 10;
				break;
		}
		return i;
	}
	public static String get_player_race() {
		save_management sav = new save_management();
		switch (sav.read()[0]) {
			case 1:
				return "Vuleen";
			case 2:
				return "Aradi";
			case 3:
				return "Human";
			case 4:
				return "Lycan";
			case 5:
				return "Jodum";
		}
		return "Error";
	}
	public static String get_enemy_race(int capital) {
		save_management sav = new save_management();
		String race = new String();
		String base = new String();
		String first = new String();
		switch (sav.read()[3]) {
			case 1:
				switch (capital) {
					case 0:
						first = "d";
						break;
					case 1:
						first = "D";
						break;
				}
				base = "arak";
				break;
			case 2:
				switch (capital) {
					case 0:
						first = "g";
						break;
					case 1:
						first = "G";
						break;
				}
				base = "oblin";
				break;
			case 3:
				switch (capital) {
					case 0:
						first = "a";
						break;
					case 1:
						first = "A";
						break;
				}
				base = "rcran";
				break;
			case 4:
				first = "U";
				base = "LTRA GOBLIN";
				break;
			case 5:
				switch (capital) {
					case 0:
						first = "s";
						break;
					case 1:
						first = "S";
						break;
				}
				base = "leech";
				break;
			case 6:
				switch (capital) {
					case 0:
						first = "w";
						break;
					case 1:
						first = "W";
						break;
				}
				base = "imble";
				break;
		}
		return first + base;
	}
}