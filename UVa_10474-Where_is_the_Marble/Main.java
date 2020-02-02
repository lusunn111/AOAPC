import java.util.Scanner;

public class Main {
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        int kase = 0;
        int N, Q;
        //用scanner.nextInt()一直TLE，怀疑读取数据有问题
        N = Integer.parseInt(scanner.next());
        Q = Integer.parseInt(scanner.next());
        while (N != 0 && Q != 0) {
            ++kase;
            int[] marble_count = new int[10001];
            for(int i=0; i<N; ++i){
                int marble = Integer.parseInt(scanner.next());
                ++marble_count[marble];
            }
            System.out.println("CASE# " + kase + ":");
            for (int i = 0; i < Q; ++i) {
                int q = Integer.parseInt(scanner.next());

                if (marble_count[q] == 0) {
                    System.out.println(q + " not found");
                } else {
                    int pos = 1;
                    for(int j=0; j<q; ++j){
                        pos += marble_count[j];
                    }
                    System.out.println(q + " found at " + pos);
                }
            }
            N = Integer.parseInt(scanner.next());
            Q = Integer.parseInt(scanner.next());
        }
    }
}