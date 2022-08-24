use crate::{routine::batteries::*, nommes::*};
use savesys::{reader, writer, generate};
use super::options::{scr_items, scr_spare, scr_attack}; 	

fn board_again(win: &pancurses::Window) -> bool {
	screen_smash(&win, 7, 14);
	win.mv(7, 0);
	win.printw("Play again?\n\n[YES]\n[NO ]");
	win.refresh();
	loop { match universal_tabler(&win, 9, 10, 6, 9) {
		9 => { return true }
		10|_ => { return false }
	} }
}

fn board_header(win: &pancurses::Window, fill: bool) {
	let mut itr: i32;
	let line_one = vec![
		"Butterfly ",
		BUTTERFLY_VERSION,
		" | KILLS: ",
		"-",
		"   | DEATHS: ",
		"-",
		"   | SPARES: ",
		"-"
	];
	let line_two = vec![
		"PLAYR: ",
		"------",
		" | HP: ",
		"--",
		"  | STR: ",
		"--",
	];
	let line_three = vec![
		"ENEMY: ",
		"------",
		" | HP: ",
		"--",
		"  | STR: ",
		"--"
	];
	win.mv(1, 0);
	for i in line_one {
		win.printw(i);
	}
	win.mv(3, 0);
	itr = 0;
	for i in line_two {
		if itr == 2 { win.mv(3, 13); } // safely print race name
		win.printw(i);
		itr += 1;
	}
	win.mv(5, 0);
	itr = 0;
	for i in line_three {
		if itr == 2 { win.mv(5, 13); }
		win.printw(i);
		itr += 1;
	}
	for i in ["kills", "deaths", "spares"] { var_filler(&win, i) }
	if fill == true {
		for i in ["player:race", "player:health", "player:strength", 
		"enemy:race", "enemy:health", "enemy:strength"] {
			var_filler(&win, i);
		}
	}
}

pub fn board_main(win: &pancurses::Window) {
	let mut inc = 0;
	let mut result = 0;
	let enemy_race = entity_race_get("enemy");
	let mut sav: Vec<i32>;
	screen_smash(&win, 0, 12); // clear screen, let's get this going!
	board_header(&win, true);
	loop {
		sav = reader(SAVE_NAME);
		if result == 3 {
			match sav[10] {
				1 | 2 | 3 => {
					if sav[1] <= 0 || sav[4] <= 0 {continue}
					let to_file: i32;
					if sav[4]-3 <= 0 { to_file = 0 } else { to_file = sav[4]-3 }
					writer(SAVE_NAME, 4, to_file);
					writer(SAVE_NAME, 10, sav[10]+1);
					var_filler(&win, "enemy:health");
					obo_blitter(&win, format!("The {enemy_race} loses 3HP from the poison!"), 12, 5, 750);
				}
				4 => { 
					if sav[1] <= 0 || sav[4] <= 0 {continue}
					writer(SAVE_NAME, 10, 0);
					obo_blitter(&win, format!("The {enemy_race} shakes off the poison."), 12, 5, 750);
				}
				0 | _ => {}
			}
		}
		sav = reader(SAVE_NAME);
		if sav[4] == 0 || sav[1] == 0 {
			board_header(&win, false);
			if board_again(&win) == true {
				generate(SAVE_NAME, SAVE_LENGTH);
				for i in reader(SAVE_NAME) {
				if inc == 5 { break }
				if i == 0 { stats_gen(); break }
					inc += 1;
				}
				board_header(&win, true);
				continue;
			} else {
				break;
			}
		}
		win.mv(7, 0);
		win.printw("[FIGHT]\n[ITEMS]\n[SPARE]\n[EXIT ]");
		match universal_tabler(&win, 7, 10, 8, 7) {
			7 => {
				scr_attack(&win, "all"); result = 3;
			}
			8 => {
				if scr_items(&win) == true { 
					sav = reader(SAVE_NAME);
					if sav[4] > 0 { scr_attack(&win, "player") }
					result = 3; 
				} else {
					result = 2;
				}
			}
			9 => {
				if scr_spare(&win) == true {
					board_header(&win, false);
					if board_again(&win) == true {
						result = 2;
						generate(SAVE_NAME, 20);
						for i in reader(SAVE_NAME) {
							if inc == 5 { break }
							if i == 0 { stats_gen(); break }
							inc += 1;
						}
						board_header(&win, true);
					} else {
						result = 1;
					}
				} else {
					scr_attack(&win, "player");
					result = 3;
				} 
			}
			10 => { result = 1 }
			_ => {continue}
		}
		match result {
			1 => {break}
			2 => {continue} // begin full loop
			3 => {continue} // full loop begin
			_ => {continue}
		}
	}
}