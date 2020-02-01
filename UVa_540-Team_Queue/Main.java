import java.util.*;

public class Main {
    private static Scanner scanner = new Scanner(System.in);
    private static Map<Integer, Integer> team;//key存element，value存队号
    private static Queue<Integer> team_queue;//存放队号的queue
    private static List<Queue<Integer>> queues;

    private static void readTeams(int team_num) {
        team = new HashMap<>();
        for (int i = 0; i < team_num; ++i) {
            int member_num = Integer.parseInt(scanner.next());
            for (int j = 0; j < member_num; ++j) {
                team.put(Integer.parseInt(scanner.next()), i);
            }
        }
    }

    private static void initQueues(int team_num) {
        team_queue = new ArrayDeque<>();
        queues = new ArrayList<>();
        for (int i = 0; i < team_num; ++i) {
            queues.add(new ArrayDeque<>());
        }
    }

    private static void dequeue() {
        int team_num = team_queue.peek();
        System.out.println(queues.get(team_num).poll());
        if (queues.get(team_num).isEmpty())
            team_queue.poll();
    }

    private static void enqueue(String command) {
        String[] cmds = command.split(" ");
        int x = Integer.parseInt(cmds[1]);
        int team_num = team.get(x);
        if (queues.get(team_num).isEmpty())
            team_queue.add(team_num);
        queues.get(team_num).add(x);
    }

    public static void main(String[] args) {
        int kase = 0;
        while (scanner.hasNext()) {
            int team_num = Integer.parseInt(scanner.next());
            if (team_num == 0)
                break;
            ++kase;
            /*if(kase!=1)
                System.out.println();*/
            System.out.println("Scenario #" + kase);
            readTeams(team_num);
            initQueues(team_num);
            scanner.nextLine();//回车符
            while (scanner.hasNext()) {
                String command = scanner.nextLine();
                if ("STOP".equals(command))
                    break;
                else if ("DEQUEUE".equals(command)) {
                    dequeue();
                } else {
                    enqueue(command);
                }
            }
            System.out.println();
        }
    }
}