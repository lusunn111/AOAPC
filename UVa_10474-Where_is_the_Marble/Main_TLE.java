import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    private static Scanner scanner = new Scanner(System.in);
    private static List<Integer> marbles;

    private static void readMarble(int N) {
        marbles = new ArrayList<>();
        for (int i = 0; i < N; ++i) {
            marbles.add(scanner.nextInt());
        }
        //marbles.sort((o1, o2) -> o1 - o2);
    }

    /**TLE
     *
     * @param q
     * @return
     */
    private static int findPos_1(int q) {
        for(int i=1; i<=marbles.size(); ++i){
            if(marbles.get(i-1) == q)
                return i;
        }
        return -1;
    }

    /**TLE
     *
     * @param q
     * @return
     */
    private static int findPos_2(int q) {
        boolean q_exist = false;
        int count = 0;
        for (int i = 0; i < marbles.size(); ++i) {
            if (marbles.get(i) == q) {
                q_exist = true;
            } else if (marbles.get(i) < q) {
                ++count;
            }
        }
        if (!q_exist)
            return -1;
        else
            return count + 1;
    }

    public static void main(String[] args) {
        int j = 1;
        int kase = 0;
        int N, Q;
        N = scanner.nextInt();
        Q = scanner.nextInt();
        while (N != 0 && Q != 0) {
            ++kase;
            readMarble(N);
            System.out.println("CASE# " + kase + ":");
            ++j;
            for (int i = 0; i < Q; ++i) {
                int q = scanner.nextInt();
                int pos = findPos_2(q);
                if (pos == -1) {
                    System.out.println(q + " not found");
                    ++j;
                } else {
                    System.out.println(q + " found at " + pos);
                    ++j;
                }
            }
            N = scanner.nextInt();
            Q = scanner.nextInt();
        }
    }
}