extern crate pancurses;

mod master_display;
mod disp_submods;
mod batteries;
mod nommes;

use batteries::{screen_up, screen_down};
use master_display::splash_screen;
use pancurses::{initscr, endwin};

fn main() {
	let screen = initscr();
	screen_up(&screen);
	splash_screen(&screen);
	screen_down();
	endwin();
}
