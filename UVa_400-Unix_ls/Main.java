import java.nio.charset.IllegalCharsetNameException;
import java.util.*;

public class Main {
    private static Scanner scanner = new Scanner(System.in);
    private static List<String> files;

    private static int readFiles() {
        files = new ArrayList<>();
        int file_num = Integer.parseInt(scanner.nextLine());
        int max_length = 0;
        for (int i = 0; i < file_num; ++i) {
            String file = scanner.nextLine();
            if (file.length() > max_length)
                max_length = file.length();
            files.add(file);
        }
        files.sort(String::compareTo);
        return max_length;
    }

    private static void printLine() {
        for (int i = 0; i < 6; ++i) {
            System.out.print("----------");
        }
        System.out.println();
    }

    private static void print(int rows, int cols, int max_length) {
        int rows_last_col = files.size() - (cols - 1) * rows;
        for (int i = 0; i < rows; ++i) {
            int columns = cols;
            if (i >= rows_last_col)
                columns = cols - 1;
            for (int j = 0; j < columns; ++j) {
                if (j != columns - 1)
                    System.out.printf("%-" + (max_length + 2) + "s", files.get(rows * j + i));
                else
                    System.out.printf("%-" + max_length + "s", files.get(rows * j + i));
            }
            System.out.println();
        }

    }

    public static void main(String[] args) {
        while (scanner.hasNext()) {
            printLine();
            int max_length = readFiles();
            //这是最多可存放的列数，实际的列数不一定是cols
            int columns = (60 - max_length) / (max_length + 2) + 1;
            int rows = (int) Math.ceil(1.0 * files.size() / columns);
            int cols = (int) Math.ceil(1.0 * files.size() / rows);
            print(rows, cols, max_length);
        }
    }
}