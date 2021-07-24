class all_items {
	public static int menu(int x) {
		save_management sav = new save_management();
		tools tool = new tools();
		hypersurf hy = new hypersurf();
		visuals vi = new visuals();
		int potion_status, spear_status;
		switch (sav.read()[6]) {
			case 0:
				potion_status = 1;
				break;
			default:
				potion_status = 0;
				break;
		}
		switch (sav.read()[7]) {
			case 0:
				spear_status = 1;
				break;
			default:
				spear_status = 0;
				break;
		}
		System.out.println();
		System.out.print(potion_status + "x POTION [1] (restores 10HP)\n");
		System.out.print(spear_status + "x SPEAR [2] (deals 9 damage)\nBACK [3]");
		System.out.println("\n");
		if (x == 0) {
			switch (tool.user_input(1, 3, 0)) {
				case 1:
					switch (potion_status) {
						case 1:
							sav.write(1, (sav.read()[1] + 10));
							sav.write(6, 1);
							tool.clear_screen();
							vi.battle_header();
							vi.race_info();
							vi.fake_main(2);
							menu(1);
							vi.fake_input(1);
							System.out.println("\n\nYou drink the potion, gaining 10HP!");
							tool.pause(1000);
							hy.hopper(2);
							return 2;
						case 0:
							System.out.println("\nYou don't have any potions left.");
							tool.pause(1000);
							hy.hopper(0);
							break;
					}
				case 2:
					switch (spear_status) {
						case 1:
							sav.write(4, (sav.read()[4] - 9));
							sav.write(7, 1);
							tool.clear_screen();
							vi.battle_header();
							vi.race_info();
							vi.fake_main(2);
							menu(1);
							vi.fake_input(2);
							System.out.println("\n\nYou throw the spear, dealing 9 damage!");
							tool.pause(1000);
							hy.hopper(2);
							if ((sav.read()[4] - 9) <= 0) {
								return 3; // Enemy is dead, bypass return hit
							}
							return 2; // Enemy is not dead, allow return hit
						case 0:
							System.out.println("\nYou don't have any spears left.");
							tool.pause(1000);
							hy.hopper(0);
					}
				case 3:
					hy.hopper(0);
			}
		}
		return 0;
	}
}