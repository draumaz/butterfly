import java.util.Scanner;
import java.util.InputMismatchException;
import java.io.IOException;

public class tools {
	public String version() {
		return "0.06";
	}
	public static void clear_screen() {
		if (System.getProperty("os.name").toLowerCase().indexOf("win") >= 0) {
			try { // Untested
				new ProcessBuilder("cmd","/c","cls").inheritIO().start().waitFor();
				} catch (Exception e) {}
		} else {
			try {
				new ProcessBuilder("/bin/sh","-c","clear").inheritIO().start().waitFor();
			} catch (Exception e) {}
		}
	}
	public static void pause(int ms) {
		try {
			Thread.sleep(ms);
		} catch (InterruptedException e) {}
	}
	public int user_input(int min, int max, int screen_mode) { // in-game - screen_mode = 0; main menu - screen_mode = 1;
		int i = 0;
		boolean x = false;
		tools tool = new tools();
		visuals vis = new visuals();
		splash sp = new splash();
		hypersurf hy = new hypersurf();
		vis.action_anim();
		while (!x) {
			try {
				Scanner sc = new Scanner(System.in);
				i = sc.nextInt();
				x = true;
			} catch (InputMismatchException in) {
				input_err_handle();
				clear_screen();
				switch (screen_mode) {
					case 0:
						hy.hopper(0);
					case 1:
						sp.splash_screen();
				}
				continue;
			}
			if (i < min || i > max) {
				if (i == 420 || i == 69) {
					System.out.println("\nBased.");
					pause(500);
					clear_screen();
					switch (screen_mode) {
						case 0:
							hy.hopper(0);
						case 1:
							sp.splash_screen();
					}
					continue;
				}
				input_err_handle();
				clear_screen();
				switch (screen_mode) {
					case 0:
						hy.hopper(0);
					case 1:
						sp.splash_screen();
				}
				continue;
			}
		}
		return i;
	}
	public void input_err_handle() {
		System.out.println("\nDid you mean something else?");
		pause(200);
	}
}
