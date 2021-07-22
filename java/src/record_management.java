import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

class record_management {
	public static void exist() {
		if (new File("record.txt").exists());
		else
			generate();
	}
	public static void generate() {
		try {
			FileWriter f = new FileWriter("record.txt");
			f.write("0\n0\n0");
			f.close();
		}
		catch (IOException f) {}
	}
	public static int[] read() {
		int[] y = new int[3];
		try {
			List<String> z = Files.readAllLines(Paths.get("record.txt"));
			String[] x  = z.stream().toArray(String[]::new);
			for (int i = 0; i < y.length; i++) {
				y[i] = Integer.parseInt(x[i]);
			}
		}
		catch (IOException i) {}
		catch (ArrayIndexOutOfBoundsException a) {
			System.out.println("Fatal file read error encountered. Exiting.");
			System.exit(0);
		}
		return y;
	}
	public static void write(int line) {
		int[] i = read();
		i[line] += 1;
		try {
			BufferedWriter out = null;
			out = new BufferedWriter(new FileWriter("record.txt"));
			for (int x = 0; x < i.length; x++) {
				out.write(i[x]+"\n");
			}
			out.flush();
			out.close();
		}
		catch (IOException io) {}
	}
}