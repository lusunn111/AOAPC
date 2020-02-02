import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    private static Scanner scanner = new Scanner(System.in);
    private static int n;
    private static List<List<Integer>> blocks;

    private static void init() {
        blocks = new ArrayList<>();
        for (int i = 0; i < n; ++i) {
            List<Integer> block = new ArrayList<>();
            block.add(i);
            blocks.add(block);
        }
    }

    /**
     * @param ind index of blocks
     * @param pos index of blocks.get(ind)
     */
    private static void ret2InitPos(int ind, int pos) {
        for (int i = pos + 1; i < blocks.get(ind).size(); ) {
            blocks.get(blocks.get(ind).get(i)).add(blocks.get(ind).get(i));
            blocks.get(ind).remove(i);
        }
    }

    private static void process(String command) {
        String[] cmds = command.split("\\s+");
        int a = Integer.parseInt(cmds[1]);
        int b = Integer.parseInt(cmds[3]);
        int a_ind = -1;//a在哪一个block
        int b_ind = -1;
        int a_pos = 0;//a在block中的索引
        int b_pos = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < blocks.get(i).size(); ++j) {
                if (blocks.get(i).get(j) == a) {
                    a_ind = i;
                    a_pos = j;
                }
                if (blocks.get(i).get(j) == b) {
                    b_ind = i;
                    b_pos = j;
                }
            }
            if (a_ind != -1 && b_ind != -1)
                break;
        }
        if (a_ind == b_ind)
            //忽略此命令
            return;
        if ("move".equals(cmds[0])) {
            if ("onto".equals(cmds[2])) {
                //puts block a onto block b
                //after returning any blocks that are stacked on top of blocks a and b to their initial positions.
                ret2InitPos(a_ind, a_pos);
                ret2InitPos(b_ind, b_pos);
                blocks.get(b_ind).add(a);
                blocks.get(a_ind).remove(a_pos);
            } else if ("over".equals(cmds[2])) {
                //puts block a onto the top of the stack containing block b,
                //after returning any blocks that are stacked on top of block a to their initial positions.
                ret2InitPos(a_ind, a_pos);
                blocks.get(b_ind).add(a);
                blocks.get(a_ind).remove(a_pos);
            }
        } else if ("pile".equals(cmds[0])) {
            if ("onto".equals(cmds[2])) {
                //moves the pile of blocks consisting of block a, and any blocks that are stacked above block a, onto block b.
                //All blocks on top of block b are moved to their initial positions prior to the pile taking place.
                //The blocks stacked above block a retain their order when moved.
                ret2InitPos(b_ind, b_pos);
                for (int i = a_pos; i < blocks.get(a_ind).size(); ) {
                    blocks.get(b_ind).add(blocks.get(a_ind).get(i));
                    blocks.get(a_ind).remove(i);
                }
            } else if ("over".equals(cmds[2])) {
                //puts the pile of blocks consisting of block a, and any blocks that are stacked above block a, onto the top of the stack containing block b.
                //The blocks stacked above block a retain their original order when moved
                for (int i = a_pos; i < blocks.get(a_ind).size(); ) {
                    blocks.get(b_ind).add(blocks.get(a_ind).get(i));
                    blocks.get(a_ind).remove(i);
                }
            }
        }
    }

    private static void print() {
        for (int i = 0; i < n; ++i) {
            System.out.print(i + ":");
            for (int j = 0; j < blocks.get(i).size(); ++j) {
                System.out.print(" " + blocks.get(i).get(j));
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        n = Integer.parseInt(scanner.next());
        scanner.nextLine();//回车符
        init();
        while (scanner.hasNext()) {
            String command = scanner.nextLine();
            if ("quit".equals(command))
                print();
            else {
                process(command);
            }
        }
    }
}