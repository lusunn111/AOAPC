import java.util.*;

public class Main {
    private static Scanner scanner = new Scanner(System.in);
    private static Map<String, List<String>> dictionary;

    private static void readDict() {
        dictionary = new HashMap<>();
        while (scanner.hasNext()) {
            String word = scanner.next();
            if ("#".equals(word)) {
                return;
            }
            String word_sorted = word.toLowerCase();
            char[] word_ch = word_sorted.toCharArray();
            Arrays.sort(word_ch);
            word_sorted = new String(word_ch);
            if (!dictionary.containsKey(word_sorted)) {
                List<String> value = new ArrayList<>();
                value.add(word);
                dictionary.put(word_sorted, value);
            } else {
                dictionary.get(word_sorted).add(word);
            }
        }
    }

    public static void main(String[] args) {
        readDict();
        List<String> res = new ArrayList<>();
        for (Map.Entry<String, List<String>> dict : dictionary.entrySet()) {
            if (dict.getValue().size() == 1) {
                res.add(dict.getValue().get(0));
            }
        }
        res.sort(String::compareTo);
        for (String r : res) {
            System.out.println(r);
        }
    }
}