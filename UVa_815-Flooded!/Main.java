import java.util.*;

public class Main {
    private static Scanner scanner = new Scanner(System.in);
    private static int m;
    private static int n;
    private static List<Integer> elevations;
    private static double water;

    private static void readElevations() {
        elevations = new ArrayList<>();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                elevations.add(Integer.parseInt(scanner.next()));
            }
        }
    }

    public static void main(String[] args) {
        int kase = 0;
        while (scanner.hasNext()) {
            ++kase;
            m = Integer.parseInt(scanner.next());
            n = Integer.parseInt(scanner.next());
            if (m == 0 && n == 0) break;
            readElevations();
            water = Integer.parseInt(scanner.next()) * 1.0;//归一化为底为1x1的方块

            //简化的lambda
            elevations.sort((o1, o2) -> o1 - o2);

            double final_ele = 0;
            double percentage = 0.0;
            //特殊情况
            if (water == 0) {
                final_ele = elevations.get(0);
                percentage = 0.0;
            }
            int i;
            double last = 0.0;
            for (i = 1; i < m * n && water > 0; ++i) {
                last = water;
                water -= 100.0 * i * (elevations.get(i) - elevations.get(i - 1));
            }

            if (i == m * n && water > 0) {
                //水没用完
                final_ele = elevations.get(i - 1) + water / (m * n * 100.0);
                percentage = 100.0;
            } else {
                //水中途用完
                final_ele = elevations.get(i - 2) + last / ((i - 1) * 100.0);
                percentage = (i - 1) * 1.0 / (m * n) * 100;
            }
            System.out.println("Region " + kase);
            System.out.printf("Water level is %.2f meters.\n", final_ele);
            System.out.printf("%.2f percent of the region is under water.\n", percentage);
            System.out.println();//每个测试用例输出结束之后输出一个空行！！！而不是两次输出中间有一个空行
        }
    }
}