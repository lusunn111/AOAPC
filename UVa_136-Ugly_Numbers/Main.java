import java.util.*;

public class Main {
    public static void main(String[] args) {
        Queue<Long> ugly = new PriorityQueue<>();
        Set<Long> visited = new HashSet<>();
        int i = 1;
        ugly.add((long) 1);
        while (i != 1500) {
            long num = ugly.poll();
            if (!visited.contains(2 * num)) {
                ugly.add(2 * num);
                visited.add(2 * num);
            }
            if (!visited.contains(3 * num)) {
                ugly.add(3 * num);
                visited.add(3 * num);
            }
            if (!visited.contains(5 * num)) {
                ugly.add(5 * num);
                visited.add(5 * num);
            }
            ++i;
        }
        System.out.println("The 1500'th ugly number is " + ugly.peek() + ".");
    }
}