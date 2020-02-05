import java.util.*;

public class Main {
    private static Scanner scanner = new Scanner(System.in);
    private static Stack<Integer> stack;
    private static Map<Set<Integer>, Integer> IDCache;//set与set在setCache中的index的键值对
    private static List<Set<Integer>> setCache;

    private static int getID(Set<Integer> s) {
        if (IDCache.containsKey(s)) {
            return IDCache.get(s);
        } else {
            setCache.add(s);
            IDCache.put(s, setCache.size() - 1);
            return setCache.size() - 1;
        }
    }

    public static void main(String[] args) {
        int kases = Integer.parseInt(scanner.next());
        for (int i = 0; i < kases; ++i) {
            stack = new Stack<>();
            IDCache = new HashMap<>();
            setCache = new ArrayList<>();
            int cmd_num = Integer.parseInt(scanner.next());
            for (int j = 0; j < cmd_num; ++j) {
                String command = scanner.next();
                if ("PUSH".equals(command)) {
                    stack.push(getID(new HashSet<>()));
                } else if ("DUP".equals(command)) {
                    stack.push(stack.peek());
                } else {
                    Set<Integer> set1 = setCache.get(stack.pop());
                    Set<Integer> set2 = setCache.get(stack.pop());
                    if ("ADD".equals(command)) {
                        //一定要new，否则会引起set2的改变
                        Set<Integer> set3 = new HashSet<>(set2);
                        set3.add(getID(set1));
                        stack.push(getID(set3));
                    } else if ("UNION".equals(command)) {
                        Set<Integer> set3 = new HashSet<>(set2);
                        set3.addAll(set1);
                        stack.push(getID(set3));
                    } else if ("INTERSECT".equals(command)) {
                        Set<Integer> set3 = new HashSet<>(set2);
                        set3.retainAll(set1);
                        stack.push(getID(set3));
                    }
                }
                System.out.println(setCache.get(stack.peek()).size());
            }
            System.out.println("***");
        }
    }
}