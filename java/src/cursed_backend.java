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
				return "Butterfly,".split("");
			case 1:
				return "version ".split("");
			case 2:
				return "Developed by draumaz ".split("");
			case 3:
				return "in Java!".split("");
			case 4:
				return "Playtested by".split("");
			case 5:
				return "THE BOYS".split("");
			case 6:
				return "https://github.com/draumaz/butterfly".split("");
			case 7:
				return "C R I T I C A L  H I T!".split("");
			case 9:
				return "...".split("");
			case 10:
				return "ACTION >> ".split("");
		}
		String[] fail = {"INV","ALID"};
		return fail;
	}
}