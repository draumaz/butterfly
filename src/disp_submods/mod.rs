extern crate pancurses;
extern crate savesys;

use pancurses::{Input};
use rand::Rng;
use savesys::{reader, writer};
use crate::batteries::{screen_smash, bp_sleep, var_filler, get_enemy_race};
use crate::nommes::{SAVE_NAME, RECORD_NAME};

fn items_fill(win: &pancurses::Window, item: &'static str) {
	let sav = reader(SAVE_NAME);
	match item {
		"potion" => { win.mv(12, 1); win.printw(sav[7].to_string()); }
		"spear" => { win.mv(13, 1); win.printw(sav[8].to_string()); }
		"poison" => { win.mv(14, 1); win.printw(sav[9].to_string()); }
		_ => {}
	}
	win.refresh();
}

pub fn scr_spare(win: &pancurses::Window) -> bool {
	let result: bool;
	let rec = reader(RECORD_NAME);
	let mut rng = rand::thread_rng();
	let begin = 12;
	let depth = 15;
	win.mv(begin, 0);
	win.printw("You attempt to spare the ");
	win.printw(get_enemy_race());
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
	let sav = reader(SAVE_NAME);
	let rec = reader(RECORD_NAME);
	let mut rng = rand::thread_rng();
	let damage: i32;
	if sav[2] >= sav[5] { 
		damage = sav[2] / 4 + rng.gen_range(1..7);
	} else {
		damage = sav[2] / 4 + rng.gen_range(1..4);
	}
	let to_file: i32;
	let top_text: &'static str;
	if sav[4] - damage <= 0 {
		writer(RECORD_NAME, 0, rec[0]+1);
		var_filler(&win, "kills");
		top_text = "You deal a death blow to the ";
		to_file = 0;
	} else {
		top_text = "You attack the ";
		to_file = sav[4] - damage;
	}
	writer(SAVE_NAME, 4, to_file);
	var_filler(&win, "enemy:health");
	win.mv(12, 0);
	win.printw(top_text);
	win.printw(get_enemy_race());
	win.printw(", dealing ");
	win.printw(damage.to_string());
	win.printw(" damage!");
	win.refresh();
	bp_sleep(1000);
}

fn scr_attack_player(win: &pancurses::Window, action: bool) {
	let sav = reader(SAVE_NAME);
	let rec = reader(RECORD_NAME);
	let mut rng = rand::thread_rng();
	let damage: i32;
	if sav[5] >= sav[2] { 
		damage = sav[5] / 4 + rng.gen_range(1..7);
	} else {
		damage = sav[5] / 4 + rng.gen_range(1..4);
	}
	let to_file: i32;
	let top_text: &'static str;
	let mut txt_pos = 13;
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
	writer(SAVE_NAME, 1, to_file);
	var_filler(&win, "player:health");
	win.mv(txt_pos, 0);
	win.printw("The ");
	win.printw(get_enemy_race());
	win.printw(top_text);
	win.printw(damage.to_string());
	win.printw(" damage!");
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
			if reader("save/data.txt")[4] > 0 { scr_attack_player(&win, false) }
			screen_smash(&win, 12, 14);
		}
		_ => {}
	}
}

pub fn scr_items(win: &pancurses::Window) -> bool {
	let begin = 12;
	let action: bool;
	let sav = reader(SAVE_NAME);
	let mut result: i32;
	let mut depth = 14;
	let x = 12;
	let mut y = 12;
	win.mv(begin, 0);
	win.printw("[ x POTION]\n[ x SPEAR ]\n[ x POISON]\n[BACK     ]");
	for i in ["potion", "spear", "poison"] { items_fill(&win, i) }
	loop {
		loop {
			win.mv(y, x);
			win.printw("<");
			match win.getch() {
				Some(Input::KeyDown) |
					Some(Input::Character('s')) |
					Some(Input::Character('k')) => {
						win.mv(y, x);
						win.printw("\n");
						if y == 15 { y = 12 } else { y += 1 }
					},
					Some(Input::KeyUp) | 
					Some(Input::Character('w')) |
					Some(Input::Character('i')) => {
						win.mv(y, x);
						win.printw("\n");
						if y == 12 { y = 15 } else { y -= 1 }   
					},
					Some(Input::Character('q')) |
					Some(Input::KeyDC) => { result = 4; depth = 16; break }
					Some(Input::Character('\n')) => {
						match y {
							12 => { result = 1 }
							13 => { result = 2 }
							14 => { result = 3 }
							15 => { depth = 16; result = 4 },
							_ => { result = 0 }
						}
						break;
					}
					Some(_) => (),
					None => ()
			}
		}
		match result {
			1 => { // potion
				match sav[7] {
					0 => {
						win.mv(17, 0);
						win.printw("You don't have any potions left.");
						action = false;
						win.refresh();
						depth = 18;
						bp_sleep(750);
						break;
					}
					1 => {
						writer(SAVE_NAME, 7, sav[7]-1);
						writer(SAVE_NAME, 1, sav[1]+10);
						items_fill(&win, "potion");
						var_filler(&win, "player:health");
						action = true;
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
			2 => { // spear
				match sav[8] {
					0 => {
						win.mv(17, 0);
						action = false;
						win.printw("You don't have any spears left.");
						win.refresh();
						depth = 18;
						bp_sleep(750);
						break;
					}
					1 => {
						writer(SAVE_NAME, 8, sav[8]-1);
						writer(SAVE_NAME, 4, sav[4]-9);
						items_fill(&win, "spear");
						var_filler(&win, "enemy:health");
						action = true;
						win.mv(17, 0);
						win.printw("You throw a spear at the ");
						win.printw(get_enemy_race());
						win.printw(", dealing 9 damage!");
						win.refresh();
						bp_sleep(750);
						depth = 18;
						break;
					}
					_ => { continue }
				}
			}
			3 => { // poison
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
						win.printw("You douse the ");
						win.printw(get_enemy_race());
						win.printw(" in poison!");
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
			4 => { action = false; break }
			_ => { continue }
		}
	}
	for i in begin..depth {
		win.mv(i, 0); 
		win.printw("\n");
	}
	return action;
}