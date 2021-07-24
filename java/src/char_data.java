import java.util.Random;

class char_data {
	public int[] stats_gen() {
		Random ran = new Random();
		int[] i = new int[9];
		int ran1 = (ran.nextInt(5) + 1);
		int ran2 = (ran.nextInt(5) + 1);
		for (int x = 0; x < stats_player((ran.nextInt(5) + 1)).length; x++) {
			i[x] = stats_player(ran1)[x];
			i[(x + 3)] = stats_enemy(ran2)[x];
		}
		i[6] = 0;
		i[7] = 0;
		i[8] = 0;
		return i;
	}
	public static int[] stats_player(int i) {
		switch (i) {
			case 1:
				int[] a = {1, 20, 10};
				return a;
			case 2:
				int[] b = {2, 30, 15};
				return b;
			case 3:
				int[] c = {3, 20, 7};
				return c;
			case 4:
				int[] d = {4, 16, 32};
				return d;
			case 5:
				int[] e = {5, 24, 16};
				return e;
		}
		int[] fail = {64, 64};
		return fail;
	}
	public static int[] stats_enemy(int i) {
		switch (i) {
			case 1:
				int[] a = {1, 25, 10};
				return a;
			case 2:
				int[] b = {2, 12, 7};
				return b;
			case 3:
				int[] c = {3, 30, 5};
				return c;
			case 4:
				int[] d = {5, 12, 36};
				return d;
			case 5:
				int[] e = {6, 27, 10};
				return e;
		}
		int[] f = {64, 64};
		return f;
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
		switch (sav.read()[3]) {
			case 1:
				race = "darak";
				break;
			case 2:
				race = "goblin";
				break;
			case 3:
				race = "arcran";
				break;
			case 4:
				race = "ULTRA GOBLIN";
				break;
			case 5:
				race = "sleech";
				break;
			case 6:
				race = "wimble";
				break;
		}
		if (capital == 1) {
			return race.substring(0, 1).toUpperCase() + race.substring(1);
		}
		return race;
	}
}