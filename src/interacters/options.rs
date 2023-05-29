use crate::{
	routine::batteries::{
		screen_smash,
		bp_sleep,
		var_filler,
		entity_race_get,
		universal_tabler
	},
	nommes::*
};

use rand::Rng;
use savesys::{reader, writer};

fn items_fill(win: &pancurses::Window, item: &'static str) {
	match item {
		"potion" => { win.mv(12, 1); win.printw(reader(SAVE_NAME)[7].to_string()); }
		"spear" =>  { win.mv(13, 1); win.printw(reader(SAVE_NAME)[8].to_string()); }
		"poison" => { win.mv(14, 1); win.printw(reader(SAVE_NAME)[9].to_string()); }
		_ => {}
	}; win.refresh();
}

pub fn scr_spare(win: &pancurses::Window) -> bool {
	let begin = 12; let depth = 15;
	
	let mut rng = rand::thread_rng();
	let rec = reader(RECORD_NAME);
	let result: bool;
	
	win.mv(begin, 0);
	win.printw("You attempt to spare the ");
	win.printw(entity_race_get("enemy"));
	win.refresh();
	bp_sleep(500);
	
	for _ in 0..3 {
		win.printw(".");
		win.refresh();
		bp_sleep(150);
	}
	bp_sleep(750);
	
	if rng.gen_range(0..2) >= 1  {
		writer(RECORD_NAME, 2, rec[2]+1);
		var_filler(&win, "spares");
		win.mv(14, 0);
		win.printw("It worked!");
		result = true;
	} else {
		win.mv(14, 0);
		win.printw("It didn't work.");
		result = false;
	}
	
	win.refresh();
	bp_sleep(1000);
	screen_smash(&win, begin, depth);
	
	return result;
}

fn scr_attack_enemy(win: &pancurses::Window) {
	let damage: i32;
	let to_file: i32;
	let top_text: &'static str;
	
	let sav = reader(SAVE_NAME);
	let rec = reader(RECORD_NAME);
	
	let mut rng = rand::thread_rng();
	
	if sav[2] >= sav[5] { 
		damage = sav[2] / 4 + rng.gen_range(1..7);
	} else {
		damage = sav[2] / 4 + rng.gen_range(1..4);
	}
	
	if sav[4] - damage <= 0 {
		writer(RECORD_NAME, 0, rec[0]+1);
		var_filler(&win, "kills");
		top_text = "You deal a death blow to the ";
		to_file = 0;
	} else {
		top_text = "You attack the ";
		to_file = sav[4] - damage;
	}
	for i in (to_file..sav[4]).rev() {
		if i == 9 { win.mv(5, 21); win.printw(" "); }
		win.mv(5, 20);
		win.printw(i.to_string());
		win.refresh();
		bp_sleep(50);
	}
	writer(SAVE_NAME, 4, to_file);
	var_filler(&win, "enemy:health");
	win.mv(12, 0);
  for i in [
    top_text,
    entity_race_get("enemy"),
    ", dealing ",
    &damage.to_string(),
    " damage!"
  ] { win.printw(i); }
	win.refresh();
	bp_sleep(1000);
}

fn scr_attack_player(win: &pancurses::Window, action: bool) {
	let damage: i32;
	let to_file: i32;
	let top_text: &'static str;
	let mut txt_pos = 13;
	
	let sav = reader(SAVE_NAME);
	let rec = reader(RECORD_NAME);
	
	let mut rng = rand::thread_rng();

	if sav[5] >= sav[2] { 
		damage = sav[5] / 2 + rng.gen_range(1..7);
	} else {
		damage = sav[5] / 2 + rng.gen_range(1..4);
	}

	if action == true { txt_pos = 12 }
	
	if sav[1] - damage <= 0 {
		writer(RECORD_NAME, 1, rec[1]+1);
		var_filler(&win, "deaths");
		top_text = " fatally attacks you, dealing ";
		to_file = 0;
	} else {
		top_text = " attacks you, dealing ";
		to_file = sav[1] - damage;
	}
	for i in (to_file..sav[1]).rev() {
		if i == 9 { win.mv(3, 21); win.printw("  "); }		
		win.mv(3, 20);
		win.printw(i.to_string());
		win.refresh();
		bp_sleep(50);
	}
	writer(SAVE_NAME, 1, to_file);
	var_filler(&win, "player:health");
	win.mv(txt_pos, 0);
  for i in [
    "The ",
    entity_race_get("enemy"),
    top_text,
    &damage.to_string(),
    "damage!"
  ] { win.printw(i); }
	win.refresh();
	bp_sleep(1000);
}

pub fn scr_attack(win: &pancurses::Window, dir: &'static str) {
	match dir {
		"enemy" => {
			scr_attack_enemy(&win);
			screen_smash(&win, 12, 13);
		}
		"player" => {
			scr_attack_player(&win, true);
			screen_smash(&win, 12, 13);
		}
		"all" => {
			scr_attack_enemy(&win);
			if reader(SAVE_NAME)[4] > 0 { scr_attack_player(&win, false) }
			screen_smash(&win, 12, 14);
		}
		_ => {}
	}
}

pub fn scr_items(win: &pancurses::Window) -> bool {
	let action: bool;
	let to_file: i32;
	let begin = 12;
	
	let mut depth = 16;
	
	let sav = reader(SAVE_NAME);
	
	win.mv(begin, 0);
	win.printw("[ x POTION]\n[ x SPEAR ]\n[ x POISON]\n[BACK     ]");
	for i in ["potion", "spear", "poison"] { items_fill(&win, i) }
	
	loop {
		match universal_tabler(&win, 12, 15, 12, 12) {
			12 => { // potion
				match sav[7] {
					0 => {
						action = false;
						
						win.mv(17, 0);
						win.printw("You don't have any potions left.");
						win.refresh();
						depth = 18;
						bp_sleep(750);
						break;
					}
					1 => {
						action = true;
						
						writer(SAVE_NAME, 7, sav[7]-1);
						writer(SAVE_NAME, 1, sav[1]+10);
						items_fill(&win, "potion");
						var_filler(&win, "player:health");
						win.mv(17, 0);
						win.printw("You drink the potion, gaining 10HP!");
						win.refresh();
						bp_sleep(750);
						depth = 18;
						break;
					}
					_ => { continue }
				}
			}
			13 => { // spear
				match sav[8] {
					0 => {
						action = false;
						
						win.mv(17, 0);
						win.printw("You don't have any spears left.");
						win.refresh();
						depth = 18;
						bp_sleep(750);
						break;
					}
					1 => {
						action = true;

						if sav[4]-9 <= 0 {
							to_file = 0;
						} else {
							to_file = sav[4]-9;
						}
						
						writer(SAVE_NAME, 8, sav[8]-1);
						writer(SAVE_NAME, 4, to_file);
						
						items_fill(&win, "spear");
						var_filler(&win, "enemy:health");
						
						win.mv(17, 0);
						win.printw("You throw a spear at the ");
						win.printw(entity_race_get("enemy"));
						win.printw(", dealing 9 damage!");
						win.refresh();
						bp_sleep(750);
						depth = 18;
						break;
					}
					_ => { continue }
				}
			}
			14 => { // poison
				match sav[9] {
					0 => {
						action = false;
						
						win.mv(17, 0);
						win.printw("You don't have any poison left.");
						win.refresh();
						depth = 18;
						bp_sleep(750);
						break;
					}
					1 => {
						action = true;
						
						writer(SAVE_NAME, 9, sav[9]-1);
						writer(SAVE_NAME, 10, 1);
						items_fill(&win, "poison");
						win.mv(17, 0);
            for i in [
              "You douse the ",
              entity_race_get("enemy"),
              " in poison!"
            ] { win.printw(i); }
						win.refresh();
						bp_sleep(500);
						win.mv(18, 0);
						win.printw("It feels the burn...");
						win.refresh();
						bp_sleep(1000);
						depth = 19;
						break;
					}
					_ => { continue }
				}
			}
			15 => { action = false; break }
			_ => { continue }
		}
	}
	screen_smash(&win, begin, depth);
	return action;
}
