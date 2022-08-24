use crate::{
	routine::batteries::*,
	nommes::*,	
};

use std::fs::{
	remove_file,
	remove_dir_all,
	create_dir
};

use savesys::{exists, generate, reader};
use super::board::board_main;

fn splash_reset(win: &pancurses::Window) {
	let mut depth = 13;
	let mut entry = false;
	win.mv(depth, 0);
	if ! exists(SAVE_NAME) && ! exists(RECORD_NAME) && ! exists(SAVE_DIR) {
		obo_blitter(&win, String::from("No save files to speak of."), 13, 10, 300);
		return;
	} else {
		obo_blitter(&win, String::from("Are you sure you want to reset your save files?\n\n[YES]\n[NO ]"), 13, 10, 0);
	}
	loop {
		match universal_tabler(&win, 15, 16, 6, 15) {
			15 => {
				remove_file(SAVE_NAME).unwrap(); // bad boy!
				remove_file(RECORD_NAME).unwrap();
				remove_dir_all(SAVE_DIR).unwrap();
				obo_blitter(&win, String::from("Successfully deleted."), 18, 10, 300);
				break;
			}
			16 => { break },
			_ => { continue }
		}
	}
	screen_smash(&win, 13, 18);
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
		"--> Character design, error handling mechanics"
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
	let mut result = 0;
	win.clear();
	loop {
		splash_ascii(&win);
		win.mv(8, 0);
		win.printw("[PLAY   ]\n[RESET  ]\n[CREDITS]\n[QUIT   ]");
		match universal_tabler(&win, 8, 11, 10, 8) {
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
				result = 2; // loop back to splash on board exit
			}
			9 => { // options
				splash_reset(win); 
				result = 2;
			}
			10 => { // credits
				screen_smash(&win, 0, 12);
				splash_credits(win);
				result = 2;
			}
			11 => { // exit
				result = 1;
			}
			_ => {}
		}
		match result {
			2 => { screen_smash(&win, 0, 14); continue }
			1|_ => { break }
		}
	}
}
