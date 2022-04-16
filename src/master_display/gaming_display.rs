extern crate pancurses;
extern crate savesys;

use pancurses::{Input};
use savesys::{reader, writer, generate};
use crate::batteries::{bp_sleep, screen_smash, var_filler, game_version, stats_gen, get_enemy_race};
use crate::disp_submods::{scr_items, scr_spare, scr_attack}; 	
use crate::nommes::{SAVE_NAME, SAVE_LENGTH};

fn board_again(win: &pancurses::Window) -> bool {
	let begin = 7;
	let depth = 14;
	let mut y = 9;
	let x = 6;
	screen_smash(&win, begin, depth);
	win.mv(begin, 0);
	win.printw("Play again?\n\n[YES]\n[NO ]");
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
					if y == 9 { y += 1; continue }
					if y == 10 { y -= 1; continue }
				},
				Some(Input::KeyUp) | 
				Some(Input::Character('w')) |
				Some(Input::Character('i')) => {
					win.mv(y, x);
					win.printw("\n");
					if y == 10 { y -= 1; continue }
					if y == 9 { y += 1; continue }
				},
				Some(Input::Character('q')) |
				Some(Input::KeyDC) => { break }
				Some(Input::Character('\n')) => {
					match y {
						9 => { return true },
						10 => { return false },
						_ => { return false }
					}
				},
				Some(_) => (),
				None => ()				
			}
		}
	}
}

fn board_header(win: &pancurses::Window) {
	let version = &game_version().to_string();
	let mut itr: i32;
	let line_one = vec![
		"Butterfly ",
		version,
		" | KILLS: ",
		"",
		"   | DEATHS: ",
		"",
		"   | SPARES: ",
		""
	];
	let line_two = vec![
		"PLAYR: ",
		"",
		" | HP: ",
		" ",
		"  | STR: ",
		" ",
	];
	let line_three = vec![
		"ENEMY: ",
		"",
		" | HP: ",
		" ",
		"  | STR: ",
		" "
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
	for i in ["kills", "deaths", "spares", "race:player", 
	"race:enemy", "player:health", "player:strength", 
	"enemy:health", "enemy:strength"] {
		var_filler(&win, i);
	}
}

pub fn board_main(win: &pancurses::Window) {
	let x = 8;
	let mut y = 7; // max 10
	let mut inc = 0;
	let begin = 1;
	let depth = 11;
	let mut result;
	let mut sav: Vec<i32>;
	screen_smash(&win, 0, 12); // clear screen, let's get this going!
	board_header(&win);
	loop { // double loops cuz i just like them okay?
		sav = reader(SAVE_NAME);
		if sav[4] == 0 || sav[1] == 0 {
			if board_again(&win) == true {
				generate(SAVE_NAME, SAVE_LENGTH);
				for i in reader(SAVE_NAME) {
				if inc == 5 { break }
				if i == 0 { stats_gen(); break }
					inc += 1;
				}
				y = 7;
				board_header(&win);
				continue;
			}
		}
		match sav[10] {
			1 | 2 | 3 => { 
				writer(SAVE_NAME, 4, sav[4]-3);
				writer(SAVE_NAME, 10, sav[10]+1);
				var_filler(&win, "enemy:health");
				screen_smash(&win, 6, 11);
				win.mv(7, 0);
				win.printw("The ");
				win.printw(get_enemy_race());
				win.printw(" loses 3HP from the poison!");
				win.refresh();
				bp_sleep(500);
				screen_smash(&win, 7, 8);
			}
			4 => { 
				writer(SAVE_NAME, 10, 0);
				screen_smash(&win, 6, 11);
				win.mv(7, 0);
				win.printw("The ");
				win.printw(get_enemy_race());
				win.printw(" shakes off the poison.");
				win.refresh();
				bp_sleep(500);
				screen_smash(&win, 7, 8);
			}
			0 | _ => {}
		}
		win.mv(7, 0);
		win.printw("[FIGHT]\n[ITEMS]\n[SPARE]\n[EXIT ]");
		loop {
			win.mv(y, x);
			win.printw("<");
			match win.getch() {
				Some(Input::KeyDown) |
				Some(Input::Character('s')) |
				Some(Input::Character('k')) => {
					win.mv(y, x);
					win.printw("\n");
					if y == 10 { y = 7 } else { y += 1 }
				},
				Some(Input::KeyUp) | 
				Some(Input::Character('w')) |
				Some(Input::Character('i')) => {
					win.mv(y, x);
					win.printw("\n");
					if y == 7 { y = 10 } else { y -= 1 }
				},
				Some(Input::Character('q')) |
				Some(Input::KeyDC) => { result = 1; break },
				Some(Input::Character('\n')) => {
					match y {
						7 => { scr_attack(&win, "all"); result = 2; break }
						8 => { if scr_items(&win) == true { scr_attack(&win, "player") }; result = 2; break }
						9 => { 
							if scr_spare(&win) == true { 
								if board_again(&win) == true {
									result = 2;
									generate(SAVE_NAME, 20);
									for i in reader(SAVE_NAME) {
										if inc == 5 { break }
										if i == 0 { stats_gen(); break }
										inc += 1;
									}
									y = 7;
									board_header(&win);
								} else {
									result = 1;
								}
								break; 
							} else {
								scr_attack(&win, "player");
								result = 2;
								break; 
							} 
						}
						10 => { result = 1; break }
						_ => {continue}
					}
				}
				Some(_) => (),
				None => ()
			}
		}
		match result {
			1 => {break}
			2 => {continue}
			_ => {continue}
		}
	}
	screen_smash(&win, begin, depth);
}