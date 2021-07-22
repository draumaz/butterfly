import java.util.Random;
import java.lang.Math;

class all_attacks {
	public static int to_you(int mode) { // Enemy attacks player
		Random ran = new Random();
		save_management sav = new save_management();
		char_data chr = new char_data();
		hypersurf hy = new hypersurf();
		visuals vi = new visuals();
		tools tool = new tools();
		int damage = Math.round((int)(sav.read()[2] / (ran.nextInt(3) + 1)));
		sav.write(1, (sav.read()[1] - damage));
		hy.hopper(1);
		vi.fake_main(mode);
		System.out.print("\nThe " + chr.get_enemy_race(0));
		System.out.print(" attacks you, dealing " + damage);
		System.out.print(" damage!");
		System.out.println();
		tool.pause(1000);
		if ((sav.read()[4] - damage) <= 0) {
			return 1;
		}
		return 0;
	}
	public static int to_enemy() { // Player attacks enemy
		Random ran = new Random();
		save_management sav = new save_management();
		char_data chr = new char_data();
		hypersurf hy = new hypersurf();
		visuals vi = new visuals();
		tools tool = new tools();
		int damage = Math.round((int)(sav.read()[2] / (ran.nextInt(3) + 1)));
		sav.write(4, (sav.read()[4] - damage));
		hy.hopper(1);
		vi.fake_main(1);
		System.out.print("\nYou attack the " + chr.get_enemy_race(0));
		System.out.print(", dealing " + damage);
		System.out.print(" damage!");
		System.out.println();
		tool.pause(1000);
		if (sav.read()[4] <= 0) {
			return 1;
		}
		return 0;
	}
	public static int to_enemy_crit() { // Critical
		save_management sav = new save_management();
		cursed_backend crs = new cursed_backend();
		char_data chr = new char_data();
		visuals vi = new visuals();
		hypersurf hy = new hypersurf();
		tools tool = new tools();
		sav.write(4, (sav.read()[4] - 20));
		hy.hopper(1);
		vi.fake_main(1);
		System.out.println();
		for (int i = 0; i < crs.loopers(8).length; i++) {
			System.out.print(crs.loopers(8)[i]);
			tool.pause(35);
		}
		tool.pause(500);
		System.out.print("\n\nYou attack the " + chr.get_enemy_race(0));
		System.out.print(", dealing 20 damage!");
		System.out.println();
		tool.pause(1000);
		if ((sav.read()[4] - 20) <= 0) {
			return 1;
		}
		return 0;
	}
}