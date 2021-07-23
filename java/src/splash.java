import java.io.File;

class splash {
	public static void splash_screen() {
		cursed_backend crs = new cursed_backend();
		hypersurf hy = new hypersurf();
		tools tool = new tools();
		tool.clear_screen();
		System.out.print("\nButterfly v" + tool.version());
		System.out.println("\n\nPLAY  [1] | CREDITS [3]\nRESET [2] | EXIT    [4]\n");
		switch (tool.user_input(1, 4, 1)) {
			case 1:
				hy.hopper(0);
				break;
			case 2:
				reset();
				splash_screen();
				break;
			case 3:
				credits();
				splash_screen();
				break;
			case 4:
				exit();
				System.exit(0);
				break;
		}
	}
	public static void credits() {
		cursed_backend crs = new cursed_backend();
		hypersurf hy = new hypersurf();
		tools tool = new tools();
		int loop;
		tool.clear_screen();
		System.out.println();
		for (int i = 0; i < 6; i++) {
			crs.credit_loops(i);
		}
		System.out.print(":");
		tool.pause(500);
		System.out.println("\n\nBryce Cano <3");
		tool.pause(1000);
		System.out.println("catboy6969 <3");
		tool.pause(3000);
	}
	public static void reset() {
		tools tool = new tools();
		System.out.println("\nJust to verify, you want to reset your temp file?\n\nYES [1]\nNO  [2]\n");
		switch (tool.user_input(1, 2, 1)) {
			case 1:
				if (new File("temp.txt").delete()) {
					System.out.println("\nTemp file successfully deleted.");
					tool.pause(350);
				} else {
					System.out.println("\nUnable to delete temp file.");
					tool.pause(350);
				}
				break;
		}
		splash_screen();
	}
	public static void exit() {
		cursed_backend crs = new cursed_backend();
		tools tool = new tools();
		tool.clear_screen();
		System.out.print("\nThanks for playing my game!\n\n");
		tool.pause(250);
		System.out.print("Keep up with development at ");
		crs.credit_loops(6);
		System.out.print(".");
		tool.pause(500);
		System.out.println("\n");
	}
}