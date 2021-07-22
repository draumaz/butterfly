class visuals {
	public static void battle_header() {
		tools tool = new tools();
		record_management rec = new record_management();
		System.out.print("\nButterfly v" + tool.version());
		System.out.print(" | KILLS: " + rec.read()[0]);
		System.out.print(" | DEATHS: " + rec.read()[1]);
		System.out.print(" | SPARES: " + rec.read()[2]);
		System.out.println();
	}
	public static void race_info() {
		save_management sav = new save_management();
		char_data chr = new char_data();
		System.out.print("\nRACE: " + chr.get_player_race());
		System.out.print(" | HP: " + sav.read()[1]);
		System.out.print(" | STR: " + sav.read()[2]);
		System.out.println("\n");
		System.out.print("ENEMY RACE: " + chr.get_enemy_race(1));
		System.out.print(" | HP: " + sav.read()[4]);
		System.out.print(" | STR: " + sav.read()[5]);
		System.out.println();
	}
	public void main_options() {
		System.out.print("\nFIGHT [1]\nITEMS [2]\nSPARE [3]\nEXIT  [4]\n\n");
	}
	public static void action_anim() {
		tools tool = new tools();
		String[] x = {"A","C","T","I","O","N"," ",">",">"," "};
		for (int o = 0; o < x.length; o++) {
			System.out.print(x[o]);
			tool.pause(8);
		}
	}
	public void fake_main(int i) {
		main_options();
		System.out.print("ACTION >> " + i);
		System.out.println();
	}
	public void fake_input(int i) {
		visuals vis = new visuals();
		vis.action_anim();
		System.out.print(i);
	}
}
