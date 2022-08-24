mod nommes;
mod routine;
mod interacters;

use crate::{
	routine::batteries::{screen_up, screen_down},
	interacters::splash::splash_screen
};

use pancurses::{initscr, endwin};

fn main() {
	let screen = initscr();
	screen_up(&screen);
	splash_screen(&screen);
	screen_down();
	endwin();
}
