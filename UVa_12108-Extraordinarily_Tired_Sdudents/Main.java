import java.util.*;

public class Main {
    private static Scanner scanner = new Scanner(System.in);
    private static List<Integer> as;
    private static List<Integer> bs;
    private static List<Integer> cs;
    private static List<Integer> dynamic_cs;
    private static List<Integer> status;//1 -> sleep, 0 -> awake

    private static void readInput(int num_stu) {
        as = new ArrayList<>();
        bs = new ArrayList<>();
        cs = new ArrayList<>();
        dynamic_cs = new ArrayList<>();
        status = new ArrayList<>();
        int a, b, c;
        for (int i = 0; i < num_stu; ++i) {
            a = Integer.parseInt(scanner.next());
            b = Integer.parseInt(scanner.next());
            c = Integer.parseInt(scanner.next());
            as.add(a);
            bs.add(b);
            cs.add(c);
            dynamic_cs.add(c);
            if (c > a) {
                status.add(1);
            } else {
                status.add(0);
            }
        }

    }

    private static int findAllAwake() {
        int t = 1;//time
        while (true) {
            if (t != 1 && dynamic_cs.equals(cs)) {
                //回到了初始状态，说明不会出现同时醒着的情况
                return -1;
            }
            List<Integer> next_t = new ArrayList<>();
            int sleep_num = status.stream().reduce(0, Integer::sum);
            int awake_num = status.size() - sleep_num;
            if (sleep_num == 0) {
                return t;
            }
            for (int i = 0; i < dynamic_cs.size(); ++i) {
                if (sleep_num > awake_num) {
                    //睡觉的人多
                    if (dynamic_cs.get(i) == as.get(i)) {
                        //且到达了struggle的最后一个时刻
                        status.set(i, 1);
                        next_t.add(dynamic_cs.get(i) + 1);
                    } else if (dynamic_cs.get(i) == as.get(i) + bs.get(i)) {
                        //到达了醒来的时刻
                        status.set(i, 0);
                        next_t.add(1);
                    } else {
                        //其他时刻，struggle或睡觉中途
                        next_t.add(dynamic_cs.get(i) + 1);
                    }
                } else {
                    //睡觉的人少
                    if (dynamic_cs.get(i) == as.get(i)) {
                        //到达了struggle的最后一个时刻，需要重新开始struggle
                        next_t.add(1);
                    } else if (dynamic_cs.get(i) == as.get(i) + bs.get(i)) {
                        //到达了醒来的时刻
                        status.set(i, 0);
                        next_t.add(1);
                    } else {
                        //其他时刻，struggle或睡觉中途
                        next_t.add(dynamic_cs.get(i) + 1);
                    }
                }
            }
            dynamic_cs = next_t;
            ++t;
        }
    }

    public static void main(String[] args) {
        int kase = 0;
        int num_stu = Integer.parseInt(scanner.next());
        while (num_stu != 0) {
            ++kase;
            readInput(num_stu);
            System.out.println("Case "+kase+": "+findAllAwake());
            num_stu = Integer.parseInt(scanner.next());
        }
    }
}