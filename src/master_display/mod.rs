extern crate pancurses;
extern crate savesys;

mod gaming_display;

use std::fs::{remove_file, remove_dir_all, create_dir};
use pancurses::{Input};
use savesys::{exists, generate, reader};
use gaming_display::{board_main};
use crate::batteries::{screen_smash, shreader, splash_ascii, bp_sleep, stats_gen};
use crate::nommes::{SAVE_DIR, SAVE_NAME, SAVE_LENGTH, RECORD_NAME, RECORD_LENGTH, BUTTERFLY_VERSION};

fn splash_reset(win: &pancurses::Window) {
	let mut y = 15;
	let x = 6;
	let mut result = 0;
	let mut begin = 13;
	let mut depth = 13;
	let mut entry = false;
	win.mv(depth, 0);
	if exists(SAVE_NAME) == false && 
	exists(RECORD_NAME) == false && 
	exists(SAVE_DIR) == false {
		begin = 13;
		depth = 14;
		win.printw("No save files to speak of.");
		win.refresh();
		bp_sleep(300);
	} else {
		win.printw("Just to verify, you want to reset all your save files?\n\n[YES]\n[NO ]");
		entry = true;
	}
	if entry == true {
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
						if y == 15 { y += 1; continue }
						if y == 16 { y -= 1; continue }
					},
					Some(Input::KeyUp) | 
					Some(Input::Character('w')) |
					Some(Input::Character('i')) => {
						win.mv(y, x);
						win.printw("\n");
						if y == 16 { y -= 1; continue }
						if y == 15 { y += 1; continue }
					},
					Some(Input::Character('q')) |
					Some(Input::KeyDC) => { break }
					Some(Input::Character('\n')) => {
						match y {
							15 => { result = 1 },
							16 => { result = 2 },
							_ => { result = 3 }
						}
						break;
					}
					Some(_) => (),
					None => ()
				}
			}
			match result {
				1 => {
					depth += 6;
					remove_file(SAVE_NAME).unwrap(); // bad boy!
					remove_file(RECORD_NAME).unwrap();
					remove_dir_all(SAVE_DIR).unwrap();
					win.mv(18, 0);
					win.printw("Successfully deleted.");
					win.refresh();
					bp_sleep(300);
					break;
				}
				2 => { depth += 4; break },
				_ => { continue }
			}
		}
	}
	screen_smash(&win, begin, depth);
}

fn splash_credits(win: &pancurses::Window) {
	let credits = vec![
		"Butterfly, ",
		"Developed by draumaz",
		" in Rust! ",
		"[with the lovely pancurses library]",
		"Contributors",
		"------------",
		"DELTADOVE",
		"--> ARMv8 testing, potion design, bugtesting, naming",
		"BRYCE CANO",
		"--> Character design"
	];
	win.mv(1, 0);
	shreader(win, credits[0].to_string(), 20);
	bp_sleep(250);
	shreader(win, String::from(BUTTERFLY_VERSION), 20);
	bp_sleep(500);
	win.mv(3, 0);
	for i in 1..3 {
		shreader(win, credits[i].to_string(), 20);
		bp_sleep(350);
	}
	win.mv(4, 0);
	shreader(win, credits[3].to_string(), 20);
	bp_sleep(750);
	win.mv(6, 0);
	for i in 6..8 {
		win.mv((i) as i32, 0);
		shreader(win, credits[i-2].to_string(), 20);
	}
	win.mv(9, 0);
	shreader(win, credits[6].to_string(), 20);
	win.mv(10, 0);
	bp_sleep(250);
	shreader(win, credits[7].to_string(), 20);
	bp_sleep(350);
	win.mv(12, 0);
	shreader(win, credits[8].to_string(), 20);
	win.mv(13, 0);
	bp_sleep(250);
	shreader(win, credits[9].to_string(), 20);
	bp_sleep(1000);
	screen_smash(&win, 1, 15);
}

pub fn splash_screen(win: &pancurses::Window) {
	let mut result;
	win.clear();
	loop {
		splash_ascii(&win);
		let x = 10;
		let mut y = 8;
		win.mv(8, 0);
		win.printw("[PLAY   ]\n[RESET  ]\n[CREDITS]\n[QUIT   ]");
		loop {
			win.mv(y, x);
			win.printw("<");
			match win.getch() {
				Some(Input::KeyDown) |
				Some(Input::Character('s')) |
				Some(Input::Character('k')) => {
					win.mv(y, x);
					win.printw("\n");
					if y == 11 { y = 8 } else { y += 1 }
				},
				Some(Input::KeyUp) | 
				Some(Input::Character('w')) |
				Some(Input::Character('i')) => {
					win.mv(y, x);
					win.printw("\n");
					if y == 8 { y = 11 } else { y -= 1 }
				},
				Some(Input::Character('q')) |
				Some(Input::KeyDC) => { result = 1; break },
				Some(Input::Character('\n')) => {
					match y {
						8 => { // play
							let mut inc = 0;
							if exists(SAVE_DIR) == false { create_dir(SAVE_DIR).unwrap() }
							if exists(RECORD_NAME) == false { generate(RECORD_NAME, RECORD_LENGTH) }
							if exists(SAVE_NAME) == false { generate(SAVE_NAME, SAVE_LENGTH) }
							for i in reader(SAVE_NAME) {
								if inc == 5 { break }
								if i == 0 { stats_gen(); break }
								inc += 1;
							}
							board_main(&win); // begin!
							screen_smash(&win, 0, 14);
							result = 2; // loop back to splash on board exit
							break;
						}
						9 => { // options
							splash_reset(win); 
							result = 2;
							break;
						}
						10 => { // credits
							screen_smash(&win, 0, 12);
							splash_credits(win);
							screen_smash(&win, 0, 14);
							result = 2;
							break;
						}
						11 => { // exit
							result = 1;
							break;
						}
						_ => {},
					}
				},
				Some(_) => (),
				None => ()
			}
		}
		match result {
			1 => { break }
			2 => { continue }
			_ => { continue }
		}
	}
}
