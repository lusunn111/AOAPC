import java.util.*;
import java.util.Map.Entry;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int cases = in.nextInt();
        int c = 0;
        while (c++ != cases) {
            int N = in.nextInt();
            int V = in.nextInt();
            ArrayList<Integer> values = new ArrayList<>();
            ArrayList<Integer> volumes = new ArrayList<>();
            for (int i = 0; i < N; ++i) {
                values.add(in.nextInt());
            }
            for (int i = 0; i < N; ++i) {
                volumes.add(in.nextInt());
            }
            ArrayList<Entry<Integer, Integer>> va_and_vo = new ArrayList<>();
            for (int i = 0; i < N; ++i) {
                va_and_vo.add(new AbstractMap.SimpleEntry<>(values.get(i), volumes.get(i)));
            }
            Comparator<Entry<Integer, Integer>> cmp = new Comparator<Entry<Integer, Integer>>() {
                @Override
                public int compare(Entry<Integer, Integer> o1, Entry<Integer, Integer> o2) {
                    double density1 = (double)(o1.getKey())/o1.getValue();
                    double density2 = (double)(o2.getKey())/o2.getValue();
                    if(density1<density2){
                        return 1;
                    }else if(density1 == density2){
                        return 0;
                    }else {
                        return -1;
                    }
                }
            };
            Collections.sort(va_and_vo, cmp);
            int sum = 0;
            int res = 0;
            for (int i = 0; i < N; ++i) {
                if (sum + va_and_vo.get(i).getValue() < V) {
                    sum += va_and_vo.get(i).getValue();
                    res += va_and_vo.get(i).getKey();
                } else if (sum + volumes.get(i) == V) {
                    res += va_and_vo.get(i).getKey();
                    break;
                } else {
                    res += (double)(V - sum) / va_and_vo.get(i).getValue() * va_and_vo.get(i).getKey();
                    break;
                }
            }
            System.out.println(res);
        }
    }
}
