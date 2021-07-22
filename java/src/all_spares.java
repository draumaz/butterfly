class all_spares {
	public static int spare() {
		save_management sav = new save_management();
		cursed_backend crs = new cursed_backend();
		record_management rec = new record_management();
		hypersurf hy = new hypersurf();
		visuals vi = new visuals();
		char_data chr = new char_data();
		tools tool = new tools();
		System.out.print("\nYou try to spare the " + chr.get_enemy_race(0));
		for (int x = 0; x < crs.loopers(9).length; x++) {
			System.out.print(crs.loopers(9)[x]);
			tool.pause(650);
		}
		tool.pause(700);
		if (sav.read()[1] > sav.read()[4]) {
			rec.write(2);
			hy.hopper(1);
			vi.fake_main(3);
			System.out.print("\nYou try to spare the " + chr.get_enemy_race(0));
			System.out.print("...");
			System.out.print("\n\nIt worked!");
			tool.pause(1000);
		}
		if (sav.read()[1] <= sav.read()[4]) {
			System.out.println("\n\nIt didn't work.");
			tool.pause(1000);
			return 1;
		}
		return 0;
	}
}