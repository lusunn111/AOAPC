import java.util.*;
import java.util.Map.Entry;

public class Main {
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int C = in.nextInt();
        int i = 0;
        ArrayList<Entry<Integer, Integer> > weights = new ArrayList<>();
        while(i++ != n){
            int weight = in.nextInt();
            weights.add(new AbstractMap.SimpleImmutableEntry<Integer, Integer>(i, weight));
        }
        Collections.sort(weights, (w1, w2) -> w1.getValue().compareTo(w2.getValue()));
        int sum = 0;
        ArrayList<Integer> res = new ArrayList<>();
        for(int k=0; k<weights.size(); ++k){
            if(sum+weights.get(k).getValue() <= C){
                res.add(weights.get(k).getKey());
                sum += weights.get(k).getValue();
            }else{
                break;
            }
        }
        for (int r: res) {
            System.out.print(r+" ");
        }
    }
}
