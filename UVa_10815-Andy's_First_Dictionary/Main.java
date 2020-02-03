import java.util.*;

public class Main {
    private static Scanner scanner = new Scanner(System.in);
    private static Set<String> dictionary = new HashSet<>();

    public static void main(String[] args) {
        while (scanner.hasNext()) {
            String word = scanner.next().toLowerCase();
            for (int i = 0; i < word.length(); ++i) {
                if (!Character.isLetter(word.charAt(i))) {
                    word = word.substring(0, i) + ' ' + word.substring(i + 1, word.length());
                }
            }
            String[] ws = word.split(" ");
            for (String w : ws) {
                if (!"".equals(w))
                    dictionary.add(w);
            }
        }
        List<String> dict_list = new ArrayList<>(dictionary);
        dict_list.sort(String::compareTo);
        for (String dict : dict_list) {
            System.out.println(dict);
        }
    }
}