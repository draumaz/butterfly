public class hypersurf {
	public void hopper(int fake) {
		save_management save = new save_management();
		record_management rec = new record_management();
		char_data chardat = new char_data();
		ingame ig = new ingame();
		tools tool = new tools();
		visuals vis = new visuals();
		save.exist();
		rec.exist();
		save.read();
		tool.clear_screen();
		vis.battle_header();
		vis.race_info();
		switch (fake) {
			case 0:
				ig.battle_conditions();
				ig.battle_action();
				break;
		}
	}
}