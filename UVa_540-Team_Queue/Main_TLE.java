import java.util.*;

public class Main {
    private static Scanner scanner = new Scanner(System.in);
    private static List<Set<Integer>> teams;
    private static List<Queue<Integer>> team_queue;

    private static void readTeams(int team_num) {
        teams = new ArrayList<>();
        for (int i = 0; i < team_num; ++i) {
            Set<Integer> team = new HashSet<>();
            int member_num = Integer.parseInt(scanner.next());
            for (int j = 0; j < member_num; ++j) {
                team.add(Integer.parseInt(scanner.next()));
            }
            teams.add(team);
        }
    }

    private static void dequeue() {
        System.out.println(team_queue.get(0).poll());
        if(team_queue.get(0).size() == 0){
            team_queue.remove(0);
        }
    }

    private static void enqueue(String command) {
        String[] cmds = command.split(" ");
        for(int i=0; i<team_queue.size(); ++i){
            for(int j=0; j<teams.size(); ++j){
                //找到team_queue.get(i)所在的组teams.get(j)
                if(teams.get(j).contains(team_queue.get(i).peek())){
                    if(teams.get(j).contains(Integer.parseInt(cmds[1]))){
                        team_queue.get(i).add(Integer.parseInt(cmds[1]));
                        return;
                    }
                }
            }
        }
        //没有teammate
        Queue<Integer> q = new ArrayDeque<>();
        q.add(Integer.parseInt(cmds[1]));
        team_queue.add(q);
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
            scanner.nextLine();//回车符
            team_queue = new ArrayList<>();
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