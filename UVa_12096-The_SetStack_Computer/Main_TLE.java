import java.util.*;

public class Main {
    private static Scanner scanner = new Scanner(System.in);
    private static Stack<Set<String>> stack;

    /**
     * PUSH will push the empty set {} on the stack
     */
    private static void push() {
        Set<String> sets = new HashSet<>();
        //sets.add("");
        stack.push(sets);
    }

    /**
     * DUP will duplicate the topmost set (pop the stack, and then push that set on the stack twice).
     */
    private static void dup() {
        //一定要new，否则两个地址都一样
        Set<String> set = new HashSet<>(stack.peek());
        stack.push(set);
    }

    /**
     * ADD will pop the stack twice, add the first set to the second one, and then push the resulting set
     * on the stack.
     */
    private static void add() {
        Set<String> set1 = stack.pop();
        Set<String> set2 = stack.pop();
        String set1_str = "{";
        int i=0;
        for(String s : set1){
            if (i != 0)
                set1_str += ",";
            set1_str += s;
            ++i;
        }
        set1_str += "}";
        set2.add(set1_str);
        stack.push(set2);
    }

    /**
     * UNION will pop the stack twice and then push the union of the two sets on the stack.
     */
    private static void union() {
        Set<String> set1 = stack.pop();
        Set<String> set2 = stack.pop();
        for (String s : set1) {
            if (!set2.contains(s)) {
                set2.add(s);
            }
        }
        stack.push(set2);
    }

    /**
     * INTERSECT will pop the stack twice and then push the intersection of the two sets on the stack
     */
    private static void intersect() {
        Set<String> set1 = stack.pop();
        Set<String> set2 = stack.pop();
        Set<String> set3 = new HashSet<>();
        for (String s : set1) {
            if (set2.contains(s)) {
                set3.add(s);
            }
        }
        stack.push(set3);
    }

    public static void main(String[] args) {
        int kases = Integer.parseInt(scanner.next());
        int line = 1;
        for (int i = 0; i < kases; ++i) {
            stack = new Stack<>();
            int cmd_num = Integer.parseInt(scanner.next());
            for (int j = 0; j < cmd_num; ++j) {
                String command = scanner.next();
                if ("PUSH".equals(command)) {
                    push();
                } else if ("DUP".equals(command)) {
                    dup();
                } else if ("ADD".equals(command)) {
                    add();
                } else if ("UNION".equals(command)) {
                    union();
                } else if ("INTERSECT".equals(command)) {
                    intersect();
                }
                System.out.println(stack.peek().size());
                ++line;
            }
            System.out.println("***");
            ++line;
        }
    }
}