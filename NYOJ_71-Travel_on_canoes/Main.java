import java.util.*;
import java.util.Map.Entry;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int cases = in.nextInt();
        int c = 0;
        while (c++ != cases) {
            int res;
            int w = in.nextInt();
            int n = in.nextInt();
            ArrayList<Integer> weights = new ArrayList<>();
            for(int i=0; i<n; ++i){
                weights.add(in.nextInt());
            }
            Collections.sort(weights);
            int lo=0, hi=weights.size()-1;
            int pairs=0;
            while(lo<hi){
                if(weights.get(lo)+weights.get(hi)<=w){
                    ++pairs;
                    ++lo;
                    --hi;
                }else{
                    --hi;
                }
            }
            res = n-pairs;
            System.out.println(res);
        }
    }
}
