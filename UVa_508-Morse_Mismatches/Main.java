import java.lang.reflect.GenericDeclaration;
import java.util.*;

public class Main {
    private static Scanner scanner = new Scanner(System.in);
    private static Map<String, String> code_table = new HashMap<>();
    private static Map<String, String> context = new HashMap<>();

    private static Comparator<String> comparator1 = new Comparator<String>() {
        @Override
        public int compare(String s1, String s2) {
            char[] chars1 = s1.toCharArray();
            char[] chars2 = s2.toCharArray();
            for (int i = 0; i < chars1.length; ++i) {
                if (chars1[i] < chars2[i])
                    return -1;
                else if (chars1[i] > chars2[i])
                    return 1;
            }
            return 0;
        }
    };

    private static void readCodeTable() {
        String key = scanner.next();
        while (!"*".equals(key)) {
            String value = scanner.next();
            code_table.put(key, value);
            key = scanner.next();
        }
        return;
    }

    private static void generateContext() {
        String key = scanner.next();
        while (!"*".equals(key)) {
            String value = "";
            for (int i = 0; i < key.length(); ++i) {
                value += code_table.get(key.charAt(i) + "");
            }
            context.put(key, value);
            key = scanner.next();
        }
        return;
    }

    private static void solve(String code) {
        int match_count = 0;
        List<String> match_context = new ArrayList<>();
        for (Map.Entry<String, String> entry : context.entrySet()) {
            if (entry.getValue().equals(code)) {
                ++match_count;
                match_context.add(entry.getKey());
            }
        }
        if (match_count == 1) {
            //只有一个精确匹配，直接输出
            System.out.println(match_context.get(0));
        } else if (match_count > 1) {
            //有多个精确匹配，输出字典序最小的
            match_context.sort(comparator1);
            System.out.println(match_context.get(0) + "!");
        } else if (match_count == 0) {
            //没有精确匹配，寻找模糊匹配
            //模糊匹配规则，context的morse码作为前缀或code作为前缀，寻找相差长度最小，且字典序最小的
            int count = 10000000;//作为前缀或后缀时不匹配的字符数
            List<String> fuzzy_match = new ArrayList<>();
            for (Map.Entry<String, String> entry : context.entrySet()) {
                if (entry.getValue().startsWith(code)) {
                    if (entry.getValue().length() - code.length() < count) {
                        fuzzy_match.clear();
                        count = entry.getValue().length() - code.length();
                        fuzzy_match.add(entry.getKey());
                    } else if (entry.getValue().length() - code.length() == count) {
                        fuzzy_match.add(entry.getKey());
                    }
                } else if (code.startsWith(entry.getValue())) {
                    if (code.length() - entry.getValue().length() < count) {
                        fuzzy_match.clear();
                        count = code.length() - entry.getValue().length();
                        fuzzy_match.add(entry.getKey());
                    } else if (code.length() - entry.getValue().length() == count) {
                        fuzzy_match.add(entry.getKey());
                    }
                }
            }
            fuzzy_match.sort(comparator1);
            if (fuzzy_match.size() == 0) {
                //没有模糊匹配，输出context中字典序最小的
                for (String value : context.values()) {
                    fuzzy_match.add(value);
                }
                fuzzy_match.sort(comparator1);
                System.out.println(fuzzy_match.get(0) + "?");
            } else
                System.out.println(fuzzy_match.get(0) + "?");
        }
    }

    public static void main(String[] args) {
        readCodeTable();
        generateContext();
        /*System.out.println(code_table);
        System.out.println(context);*/
        String code = scanner.next();
        while (!"*".equals(code)) {
            solve(code);
            code = scanner.next();
        }
    }
}