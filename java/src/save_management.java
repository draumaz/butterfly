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
		int[] z = ch.stats_gen();
		try {
			boolean i = new File("temp.txt").createNewFile();
		}
		catch (IOException i) {}
		try {
			PrintWriter wr = new PrintWriter("temp.txt");
			wr.println(z[0]);
			wr.println(z[1]);
			wr.println(z[2]);
			wr.println(z[3]);
			wr.println(z[4]);
			wr.println(z[5]);
			wr.println(z[6]);
			wr.println(z[7]);
			wr.println(z[8]);
			wr.close();
		}
		catch (FileNotFoundException o) {}
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
		}
		catch (IOException i) {}
		catch (ArrayIndexOutOfBoundsException a) {
			generate();
			System.out.println("\nSave corrupted. Continuing with a new save."); // Consider adding to a pre-game splash screen?
			tool.pause(1000);
			hy.hopper(0);
		}
		return y;
	}
	public static void write(int line, int state) {
		int[] i = read();
		if (state <= 0) {
			state = 0;
		}
		i[line] = state;
		try {
			BufferedWriter out = null;
			out = new BufferedWriter(new FileWriter("temp.txt"));
			for (int x = 0; x < i.length; x++) {
				out.write(i[x]+"\n");
			}
			out.flush();
			out.close();
		}
		catch (IOException f) {}
	}
}
