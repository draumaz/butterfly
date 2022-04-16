extern crate pancurses;
extern crate savesys;

use pancurses::{Input};
use savesys::{reader, writer, generate};
use crate::batteries::{bp_sleep, screen_smash, var_filler, game_version, stats_gen, entity_race_get};
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
	win.refresh();
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

fn board_header(win: &pancurses::Window, fill: bool) {
	let version = &game_version().to_string();
	let mut itr: i32;
	let line_one = vec![
		"Butterfly ",
		version,
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
	let x = 8;
	let mut y = 7; // max 10
	let mut inc = 0;
	let begin = 1;
	let depth = 11;
	let mut result = 0;
	let mut sav: Vec<i32>;
	screen_smash(&win, 0, 12); // clear screen, let's get this going!
	board_header(&win, true);
	loop { // double loops cuz i just like them okay?
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
					screen_smash(&win, 6, 11);
					win.mv(7, 0);
					win.printw("The ");
					win.printw(entity_race_get("enemy"));
					win.printw(" loses 3HP from the poison!");
					win.refresh();
					bp_sleep(750);
					screen_smash(&win, 7, 8);
				}
				4 => { 
					if sav[1] <= 0 || sav[4] <= 0 {continue}
					writer(SAVE_NAME, 10, 0);
					screen_smash(&win, 6, 11);
					win.mv(7, 0);
					win.printw("The ");
					win.printw(entity_race_get("enemys"));
					win.printw(" shakes off the poison.");
					win.refresh();
					bp_sleep(750);
					screen_smash(&win, 7, 8);
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
				y = 7;
				board_header(&win, true);
				continue;
			} else {
				break;
			}
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
						7 => {
							scr_attack(&win, "all");
							result = 3;
							break;
						}
						8 => {
							if scr_items(&win) == true { 
								sav = reader(SAVE_NAME);
								if sav[4] > 0 { scr_attack(&win, "player") }
								result = 3; 
							} else {
								result = 2;
							}
							break;
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
									y = 7;
									board_header(&win, true);
								} else {
									result = 1;
									break;
								}
								break; 
							} else {
								scr_attack(&win, "player");
								result = 3;
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
			2 => {continue} // begin full loop
			3 => {continue} // full loop begin
			_ => {continue}
		}
	}
	screen_smash(&win, begin, depth);
}