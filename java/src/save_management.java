import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

class save_management {
	public static void exist() {
		if (new File("temp.txt").exists());
		else
			generate();
	}
	public static void generate() {
		char_data ch = new char_data();
		tools tool = new tools();
		int[] z = ch.stats_gen();
		try {
			boolean i = new File("temp.txt").createNewFile();
		} catch (IOException i) {}
		try {
			BufferedWriter out = null;
			out = new BufferedWriter(new FileWriter("temp.txt"));
			for (int x = 0; x < ch.stats_gen().length; x++) {
				out.write(z[x]+"\n");
			}
			out.flush();
			out.close();
		} catch (IOException o) {}
	}
	public static int[] read() {
		hypersurf hy = new hypersurf();
		tools tool = new tools();
		int[] y = new int[9];
		try {
			List<String> z = Files.readAllLines(Paths.get("temp.txt"));
			String[] x = z.stream().toArray(String[]::new);
			for (int i = 0; i < y.length; i++) {
				y[i] = Integer.parseInt(x[i]);
			}
		} catch (IOException i) {}
		  catch (ArrayIndexOutOfBoundsException a) {
		  	generate();
			System.out.println("\nSave corrupted. Continuing with a new save."); // Consider adding to a pre-game splash screen?
			tool.pause(1000);
			hy.hopper(0);
		}
		return y;
	}
	public static void write(int line, int state) {
		int[] z = read();
		state = state < 0? 0 : state;
		z[line] = Math.round((int)(state));
		try {
			BufferedWriter out = null;
			out = new BufferedWriter(new FileWriter("temp.txt"));
			for (int x = 0; x < z.length; x++) {
				out.write(z[x]+"\n");
			}
			out.flush();
			out.close();
		} catch (IOException f) {}
	}
}
