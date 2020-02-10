import java.util.*;

public class Main {
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        long N, Sp, Sq;
        while (scanner.hasNext()) {
            N = Integer.parseInt(scanner.next());
            Sp = Integer.parseInt(scanner.next());
            Sq = Integer.parseInt(scanner.next());
            long A = 0;
            long B = 0;
            long K = Long.MAX_VALUE;
            for (int a = 0; a <= 31; ++a) {
                for (int b = 0; b <= 31; ++b) {
                    long tempK = (((N - 1) * Sp + (((N - 1) * Sp) << a)) >> b) + Sq;
                    if (tempK >= N * Sq && K > tempK) {
                        K = tempK;
                        A = a;
                        B = b;
                    }
                }
            }
            System.out.println(K + " " + A + " " + B);
        }
    }
}