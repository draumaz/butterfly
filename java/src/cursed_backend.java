class cursed_backend {
	public static void credit_loops(int which) {
		tools tool = new tools();
		int loop;
		switch (which) {
			case 0:
				for (loop = 0; loop < loopers(2).length; loop++) {
					System.out.print(loopers(2)[loop]);
					tool.pause(10);
				}
				tool.pause(500);
				break;
			case 1:
				System.out.print(" ");
				for (loop = 0; loop < loopers(3).length; loop++) {
					System.out.print(loopers(3)[loop]);
					tool.pause(10);
				}
				System.out.print(tool.version());
				tool.pause(650);
				break;
			case 2:
				System.out.println("\n");
				for (loop = 0; loop < loopers(4).length; loop++) {
					System.out.print(loopers(4)[loop]);
					tool.pause(10);
				}
				tool.pause(250);
				break;
			case 3:
				for (loop = 0; loop < loopers(1).length; loop++) {
					System.out.print(loopers(1)[loop]);
					tool.pause(100);
				}
				tool.pause(1000);
				break;
			case 4:
				System.out.println("\n");
				for (loop = 0; loop < loopers(5).length; loop++) {
					System.out.print(loopers(5)[loop]);
					tool.pause(10);
				}
				break;
			case 5:
				System.out.print(" ");
				for (loop = 0; loop < loopers(6).length; loop++) {
					System.out.print(loopers(6)[loop]);
					tool.pause(80);
				}
				break;
			case 6:
				for (loop = 0; loop < loopers(7).length; loop++) {
					System.out.print(loopers(7)[loop]);
					tool.pause(8);
				}
				break;
			default:
				break;
		}
	}
	public static String[] loopers(int which) {
		switch (which) {
			case 1:
				String[] b = {"i","n"," ","J","a","v","a","!"};
				return b;
			case 2:
				String[] c = {"B","u","t","t","e","r","f","l","y",","};
				return c;
			case 3:
				String[] d = {"v","e","r","s","i","o","n"," "};
				return d;
			case 4:
				String[] e = {"D","e","v","e","l","o","p","e","d"," ","b","y"," ","d","r","a","u","m","a","z"," "};
				return e;
			case 5:
				String[] f = {"P","l","a","y","t","e","s","t","e","d"," ","b","y"};
				return f;
			case 6:
				String[] g = {"T","H","E"," ","B","O","Y","S"};
				return g;
			case 7:
				String[] h = {"h","t","t","p","s",":","/","/","g","i","t","h","u","b",".","c","o","m","/","d","r","a","u","m","a","z","/","b","u","t","t","e","r","f","l","y"};
				return h;
			case 8:
				String[] i = {"C","R","I","T","I","C","A","L"," ","H","I","T","!"};
				return i;
			case 9:
				String[] j = {".",".","."};
				return j;
			case 10:
				String[] k = {"A","C","T","I","O","N"," ",">",">"," "};
				return k;
		}
		String[] fail = {"INV","ALID"};
		return fail;
	}
}