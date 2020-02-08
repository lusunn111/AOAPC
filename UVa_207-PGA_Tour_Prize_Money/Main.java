import java.nio.charset.IllegalCharsetNameException;
import java.util.*;

/**
* udebug案例输出只有diqualified的player的顺序不一样，题目说了这个顺序时unimportant的
* 且此题的输出格式过于sb，放弃
*/
public class Main {
    private static Scanner scanner = new Scanner(System.in);
    private static List<Double> percentages;
    private static double purse;
    private static List<Player> players;

    private static class Player {
        String name;
        boolean amateur;
        int rd1, rd2, rd3, rd4;
        int first2rd, all4rd;
        String place;
        double money;

        Player() {
            this.name = "";
            this.amateur = false;
            this.rd1 = -1;
            this.rd2 = -1;
            this.rd3 = -1;
            this.rd4 = -1;
            this.first2rd = -1;
            this.all4rd = -1;
            this.place = "";
            this.money = -1.0;
        }
    }

    static Comparator<Player> comparator_first2rd = new Comparator<Player>() {
        @Override
        public int compare(Player o1, Player o2) {
            return o1.first2rd - o2.first2rd;
        }
    };

    static Comparator<Player> comparator_all4rd = new Comparator<Player>() {
        @Override
        public int compare(Player o1, Player o2) {
            //compare要满足可逆比较
            if (o1.all4rd == -1 && o2.all4rd == -1) {
                return o1.name.compareTo(o2.name);
            } else if (o1.all4rd == -1 && o2.all4rd != -1) {
                return 1;
            } else if (o1.all4rd != -1 && o2.all4rd == -1) {
                return -1;
            } else {
                if (o1.all4rd - o2.all4rd != 0)
                    return o1.all4rd - o2.all4rd;
                else
                    return o1.name.compareTo(o2.name);
            }
        }
    };

    private static void readPurseAndPercentages() {
        percentages = new ArrayList<>();
        purse = scanner.nextDouble();
        for (int i = 0; i < 70; ++i) {
            percentages.add(scanner.nextDouble());
        }
    }

    private static void readPlayers() {
        players = new ArrayList<>();
        int player_num = scanner.nextInt();
        scanner.nextLine();//回车符
        for (int i = 0; i < player_num; ++i) {
            Player player = new Player();
            String line = scanner.nextLine();
            player.name = line.substring(0, 20).trim();
            if (player.name.endsWith("*"))
                player.amateur = true;
            String rd1 = line.substring(20, 23).trim();
            if ("DQ".equals(rd1))
                continue;
            else
                player.rd1 = Integer.parseInt(rd1);
            String rd2 = line.substring(23, 26).trim();
            if ("DQ".equals(rd2))
                continue;
            else
                player.rd2 = Integer.parseInt(rd2);
            player.first2rd = player.rd1 + player.rd2;

            String rd3 = line.substring(26, 29).trim();
            if ("DQ".equals(rd3)) {
                players.add(player);
                continue;
            } else
                player.rd3 = Integer.parseInt(rd3);
            String rd4 = line.substring(29, 32).trim();
            if ("DQ".equals(rd4)) {
                players.add(player);
                continue;
            } else
                player.rd4 = Integer.parseInt(rd4);
            player.all4rd = player.first2rd + player.rd3 + player.rd4;
            players.add(player);
        }
    }

    private static void makeCut() {
        int cut_ind = players.size();//最后一个进入最后两轮的player在players中的索引
        if (players.size() <= 70)
            cut_ind = players.size() - 1;
        else {
            for (int i = 70; i < players.size(); ++i) {
                if (players.get(i - 1).first2rd != players.get(i).first2rd) {
                    cut_ind = i - 1;
                    break;
                }
            }
        }
        //Output from this program consists of names of all players who made the 36-hole cut
        for (int i = players.size() - 1; i >= cut_ind + 1; --i) {
            players.remove(i);
        }
    }

    private static void countPlace() {
        //题目保证第一位不会tie
        int place = 1;
        int tie_num = 1;
        for (int i = 1; i < players.size(); ++i) {
            if (players.get(i).all4rd != players.get(i - 1).all4rd || i == players.size() - 1) {
                //不和前一位tie或者到达最后一个player，则开始给前面tie的tie_num个player赋place

                int not_amateur = 0;
                for (int j = i - 1; j > i - 1 - tie_num; --j) {
                    if (!players.get(j).amateur) {
                        ++not_amateur;
                    }
                }
                if (not_amateur <= 1) {
                    //非amateur的player小于等于1个，则所有place不加T
                    for (int j = i - 1; j > i - 1 - tie_num; --j) {
                        players.get(j).place = place + "";
                    }
                } else {
                    //非amateur的player大于1个，则非amateur加T，amateur不加T
                    for (int j = i - 1; j > i - 1 - tie_num; --j) {
                        if (players.get(j).amateur)
                            players.get(j).place = place + "";
                        else
                            players.get(j).place = place + "T";
                    }
                }

                //赋完前面tie的players的place后计数place更新
                place += tie_num;
                tie_num = 1;
            } else {
                ++tie_num;
            }
        }
    }

    private static void countMoney() {
        //题目保证第一位不会tie
        int place = 1;
        int tie_num = 1;
        for (int i = 1; i < players.size(); ++i) {
            if (place + tie_num > 71)
                return;
            if (players.get(i).all4rd != players.get(i - 1).all4rd || i == players.size() - 1) {
                //不和前一位tie或者到达最后一个player，则开始给前面tie的tie_num个player赋place

                int not_amateur = 0;
                for (int j = i - 1; j > i - 1 - tie_num; --j) {
                    if (!players.get(j).amateur) {
                        ++not_amateur;
                    }
                }
                if (not_amateur == 0) {
                    //当前tie全是amateur，不分奖
                    continue;
                } else {
                    //有人要分奖
                    double pool_percentage = 0.0;//奖池比例
                    for (int j = place; j < place + not_amateur; ++j) {
                        pool_percentage += percentages.get(j - 1);
                    }
                    pool_percentage /= 100.0;
                    double money = pool_percentage * purse / not_amateur;
                    for (int j = i - 1; j > i - 1 - tie_num; --j) {
                        if (!players.get(j).amateur) {
                            players.get(j).money = money;
                        }
                    }
                }

                //赋完前面tie的players的money后计数place更新
                place += not_amateur;
                tie_num = 1;
            } else {
                ++tie_num;
            }
        }
    }

    private static void print() {
        System.out.printf("%-21s", "Player Name");
        System.out.printf("%-10s", "Place");
        System.out.printf("%-5s", "RD1");
        System.out.printf("%-5s", "RD2");
        System.out.printf("%-5s", "RD3");
        System.out.printf("%-5s", "RD4");
        System.out.printf("%-10s", "TOTAL");
        System.out.printf("%-9s\n", "Money Won");
        System.out.println("-----------------------------------------------------------------------");
        for (int i = 0; i < players.size(); ++i) {
            System.out.printf("%-21s", players.get(i).name);
            if(players.get(i).all4rd != -1)
                System.out.printf("%-10s", players.get(i).place);
            else
                System.out.printf("%-10s", "");
            System.out.printf("%-5d", players.get(i).rd1);
            System.out.printf("%-5d", players.get(i).rd2);
            if (players.get(i).rd3 != -1)
                System.out.printf("%-5d", players.get(i).rd3);
            else
                System.out.printf("%-5s", "");
            if (players.get(i).rd4 != -1)
                System.out.printf("%-5d", players.get(i).rd4);
            else
                System.out.printf("%-5s", "");

            if (players.get(i).all4rd == -1)
                System.out.printf("%-10s\n", "DQ");
            else {
                if (players.get(i).amateur || players.get(i).money == -1.0)
                    System.out.println(players.get(i).all4rd);
                else
                    System.out.printf("%-10d$%9.2f\n", players.get(i).all4rd, players.get(i).money);
            }

        }
    }

    public static void main(String[] args) {
        int kases = Integer.parseInt(scanner.next());
        int kase = 0;
        while (0 != kases--) {
            if (kase != 0)
                //The outputs of two consecutive cases will be separated by a blank line.
                System.out.println();
            ++kase;

            readPurseAndPercentages();
            readPlayers();
            players.sort(comparator_first2rd);
            makeCut();
            players.sort(comparator_all4rd);
            countPlace();
            countMoney();
            print();
        }
    }
}