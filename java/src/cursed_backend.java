class cursed_backend {
	public static void credit_loops(int which) {
		tools tool = new tools();
		String[] inter = {"","","\n\n","","\n"," ","",""};
		String[] inter2 = {" ",tool.version(),"","\n","","","",""};
		int[] pau1 = {10, 10, 10, 100, 10, 80, 8, 35};
		int[] pau2 = {500, 650, 250, 1000, 0, 0, 0, 0};
		System.out.print(inter[which]);
		for (int i = 0; i < loopers(which).length; i++) {
			System.out.print(loopers(which)[i]);
			tool.pause(pau1[which]);	
		}
		System.out.print(inter2[which]);
		tool.pause(pau2[which]);
	}
	public static String[] loopers(int which) {
		switch (which) {
			case 0:
				String[] c = {"B","u","t","t","e","r","f","l","y",","};
				return c;
			case 1:
				String[] d = {"v","e","r","s","i","o","n"," "};
				return d;
			case 2:
				String[] e = {"D","e","v","e","l","o","p","e","d"," ","b","y"," ","d","r","a","u","m","a","z"," "};
				return e;
			case 3:
				String[] b = {"i","n"," ","J","a","v","a","!"};
				return b;
			case 4:
				String[] f = {"P","l","a","y","t","e","s","t","e","d"," ","b","y"};
				return f;
			case 5:
				String[] g = {"T","H","E"," ","B","O","Y","S"};
				return g;
			case 6:
				String[] h = {"h","t","t","p","s",":","/","/","g","i","t","h","u","b",".","c","o","m","/","d","r","a","u","m","a","z","/","b","u","t","t","e","r","f","l","y"};
				return h;
			case 7:
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