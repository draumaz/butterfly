extern crate pancurses;
extern crate savesys;

use pancurses::{resize_term, curs_set, noecho, echo};
use savesys::{reader, writer};
use rand::Rng;
use std::{thread, time};

use crate::nommes::{SAVE_NAME, RECORD_NAME};


pub fn game_version() -> String { return String::from("v0.16_01") }

pub fn get_player_race() -> &'static str {
	match reader("save/data.txt")[0] {
		1 => { return "Vuleen" },
		2 => { return "Aradi" },
		3 => { return "Human" },
		4 => { return "Lycan" },
		5 => { return "Jodum" },
		_ => { return "NULL" }
	}
}

pub fn get_enemy_race() -> &'static str {
	match reader("save/data.txt")[3] {
		1 => { return "Darak" },
		2 => { return "Goblin" },
		3 => { return "Arcran" },
		4 => { return "Sleech" },
		5 => { return "Wimble" },
		_ => { return "NULL" }
	}
}

fn player_stats_gen(i: i32) -> Vec<i32> {
	match i {
		1 => { return [1, 20, 10].to_vec() },
		2 => { return [2, 30, 15].to_vec() },
		3 => { return [3, 20, 7].to_vec() },
		4 => { return [4, 16, 14].to_vec() },
		5 => { return [5, 24, 16].to_vec() },
		_ => { return [0, 0, 0].to_vec() }
	}
}

fn enemy_stats_gen(i: i32) -> Vec<i32> {
	match i {
		1 => { return [1, 25, 10].to_vec() },
		2 => { return [2, 12, 7].to_vec() },
		3 => { return [3, 30, 5].to_vec() },
		4 => { return [4, 12, 13].to_vec() },
		5 => { return [5, 27, 10].to_vec() }
		_ => { return [0, 0, 0].to_vec() }
	}
}

pub fn stats_gen() {
	let mut rng = rand::thread_rng();
	let stat_p = player_stats_gen(rng.gen_range(1..5));
	let stat_e = enemy_stats_gen(rng.gen_range(1..5));
	for i in 0..3 { // player stats from line 0 to 2
		writer(SAVE_NAME, i, stat_p[i]);
	}
	for i in 3..6 { // enemy stats from line 3 to 5
		writer(SAVE_NAME, i, stat_e[i-3]);
	}
	// line 6 is current menu position
	for i in 7..10 {  // fill inventories (potion, spear, poison)
		writer(SAVE_NAME, i, 1);
	}
	writer(SAVE_NAME, 10, 0); // poison incrementer
}

pub fn var_filler(win: &pancurses::Window, switch: &str) {
	let sav = reader(SAVE_NAME);
	let rec = reader(RECORD_NAME);
	match switch {
		"kills" => { win.mv(1, 28); win.printw("  "); win.mv(1, 28); win.printw(rec[0].to_string()); },
		"deaths" => { win.mv(1, 41); win.printw("  "); win.mv(1, 41); win.printw(rec[1].to_string()); },
		"spares" => { win.mv(1, 54); win.printw("  "); win.mv(1, 54); win.printw(rec[2].to_string()); },
		"race:player" => { win.mv(3, 7); win.printw("      "); win.mv(3, 7); win.printw(get_player_race()); },
		"race:enemy" => { win.mv(5, 7); win.printw("      "); win.mv(5, 7); win.printw(get_enemy_race()); },
		"player:health" => { win.mv(3, 20); win.printw("  "); win.mv(3, 20); win.printw(sav[1].to_string()); },
		"player:strength" => { win.mv(3, 30); win.printw("  "); win.mv(3, 30); win.printw(sav[2].to_string()); }
		"enemy:health" => { win.mv(5, 20); win.printw("  "); win.mv(5, 20); win.printw(sav[4].to_string()); },
		"enemy:strength" => { win.mv(5, 30); win.printw("  "); win.mv(5, 30); win.printw(sav[5].to_string()); },
		_ => { return }
	}
	win.refresh();
}

pub fn bp_sleep(time: u64) { 
	thread::spawn(move || { thread::sleep(time::Duration::from_millis(time)); }).join().unwrap();
}

pub fn shreader(win: &pancurses::Window, s: String, t: u64) {
	for i in s.chars() {
		win.printw(i.to_string());
		win.refresh();
		bp_sleep(t);
	}
}

pub fn splash_ascii(win: &pancurses::Window) {
	let ascii = vec![
	"______ _   _ _____ _____ _________________ _   __   __ |",
	"| ___ | | | |_   _|_   _|  ___| ___ |  ___| |  \\ \\ / / |",
	"| |_/ | | | | | |   | | | |__ | |_/ | |_  | |   \\ V /  |",
	"| ___ | | | | | |   | | |  __||    /|  _| | |    \\ /   |",
	"| |_/ | |_| | | |   | | | |___| |\\ \\| |   | |____| |   |",
	"\\____/ \\___/  \\_/   \\_/ \\____/\\_| \\_\\_|   \\_____/\\_/   |",
	"-------------------------------------------------------|"
	];
	for i in 0..ascii.len() {
		win.mv(i as i32, 0);
		win.printw(ascii[i]);
	}
}

pub fn screen_smash(win: &pancurses::Window, min: i32, max: i32) {
	for i in min..max {
		win.mv(i, 0);
		win.printw("\n");
		win.refresh();
	}
}

pub fn screen_up(s: &pancurses::Window) {
	s.keypad(true);
	resize_term(25, 80);
	curs_set(0);
	noecho();
}

pub fn screen_down() {
	curs_set(1);
	echo();
}
