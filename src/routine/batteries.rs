use pancurses::{Input, resize_term, curs_set, noecho, echo};
use savesys::{reader, writer};
use rand::Rng;
use std::{thread, time};

use crate::nommes::{SAVE_NAME, RECORD_NAME};

pub fn universal_tabler(
	win: &pancurses::Window,
	first: i32,
	last: i32,
	x:     i32,
	mut y: i32) 
-> i32 { 
	loop {
		win.mv(y, x);
		win.printw("<");
		match win.getch() {
			Some(Input::KeyUp) | 
			Some(Input::Character('w')) |
			Some(Input::Character('i')) => {
				win.mv(y, x);
				win.printw("\n");
				if y == first { y = last } else { y -= 1 }
			},
			Some(Input::KeyDown) |
			Some(Input::Character('s')) |
			Some(Input::Character('k')) => {
				win.mv(y, x);
				win.printw("\n");
				if y == last { y = first } else { y += 1 }
			},
			Some(Input::Character('\n')) => { return y },
			Some(_) => (),
			None => ()
		}
	} 
}

pub fn entity_race_get(point: &'static str) -> &'static str {
	match point {
		"player" => {
			match reader(SAVE_NAME)[0] {
				1 => { "Vuleen" },
				2 => { "Aradi" },
				3 => { "Human" },
				4 => { "Lycan" },
				5 => { "Jodum" },
				_ => { "NULL" }
			}
		}
		"enemy" => {
			match reader(SAVE_NAME)[3] {
				1 => { "Darak" },
				2 => { "Goblin" },
				3 => { "Arcran" },
				4 => { "Sleech" },
				5 => { "Wimble" },
				_ => { "NULL" }
			}
		}
		_ => { "ERROR" }
	}
}

fn entity_stats_gen(i: i32, switch: &str) -> Vec<i32> {
	match switch {
		"player" => {
			match i {
				1 => { [1, 20, 10].to_vec() },
				2 => { [2, 30, 15].to_vec() },
				3 => { [3, 20, 7].to_vec() },
				4 => { [4, 16, 14].to_vec() },
				5 => { [5, 24, 16].to_vec() },
				_ => { [6, 30, 5].to_vec() }
			}
		}
		"enemy" => {
			match i {
				1 => { [1, 25, 10].to_vec() },
				2 => { [2, 12, 7].to_vec() },
				3 => { [3, 30, 5].to_vec() },
				4 => { [4, 12, 13].to_vec() },
				5 => { [5, 27, 10].to_vec() }
				_ => { [999, 999, 999].to_vec() }
			}
		}
		_ => { [999, 999, 999].to_vec() }
	}
}

pub fn stats_gen() {
	let mut rng = rand::thread_rng();
	let stat_p = entity_stats_gen(rng.gen_range(1..5), "player");
	let stat_e = entity_stats_gen(rng.gen_range(1..5), "enemy");
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
	let y: i32;
	let x: i32;
	match switch {
		"kills" => { y = 1; x = 28; win.mv(y, x); win.printw("  "); win.mv(y, x); win.printw(rec[0].to_string()); },
		"deaths" => { y = 1; x = 42; win.mv(y, x); win.printw("  "); win.mv(y, x); win.printw(rec[1].to_string()); },
		"spares" => { y = 1; x = 56; win.mv(y, x); win.printw("  "); win.mv(y, x); win.printw(rec[2].to_string()); },
		"player:race" => { y = 3; x = 7; win.mv(y, x); win.printw("      "); win.mv(y, x); win.printw(entity_race_get("player")); },
		"player:health" => { y = 3; x = 20; win.mv(y, x); win.printw("  "); win.mv(y, x); win.printw(sav[1].to_string()); },
		"player:strength" => { y = 3; x = 31; win.mv(y, x); win.printw("  "); win.mv(y, x); win.printw(sav[2].to_string()); }
		"enemy:race" => { y = 5; x = 7; win.mv(y, x); win.printw("      "); win.mv(y, x); win.printw(entity_race_get("enemy")); },
		"enemy:health" => { y = 5; x = 20; win.mv(y, x); win.printw("  "); win.mv(y, x); win.printw(sav[4].to_string()); },
		"enemy:strength" => { y = 5; x = 31; win.mv(y, x); win.printw("  "); win.mv(y, x); win.printw(sav[5].to_string()); },
		_ => {}
	}
	win.refresh();
}

pub fn bp_sleep(time: u64) { 
	thread::spawn(
		move || { 
			thread::sleep(time::Duration::from_millis(time)); 
		}
	).join().unwrap();
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
	let mut y: i32 = 0;
	for i in &ascii { 
		win.mv(y, 0);
		win.printw(i);
		y += 1;
	}
}

pub fn screen_smash(
	win: &pancurses::Window, 
	min: i32, 
	max: i32) 
{
	for i in min..max {
		win.mv(i, 0);
		win.printw("\n");
		win.refresh();
	}
}

pub fn obo_blitter(win: &pancurses::Window, text: String, pos: i32, stop: u64, pause: u64) {
	win.mv(pos, 0);
	for c in text.chars() { win.printw(c.to_string()); win.refresh(); bp_sleep(stop); }
	if pause == 0 {return}
	bp_sleep(pause);
	for i in (0..text.len() as i32).rev() {
		win.mv(pos, i);
		win.printw(" ");
		win.refresh();
		bp_sleep(stop);
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
