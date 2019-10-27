import java.util.*;

public class Main{
    public static void main(String[] args){
        class interval implements Comparable<interval> {
            int left;
            int right;
            interval(int left, int right){
                this.left = left;
                this.right = right;
            }
            @Override
            public int compareTo(interval o){
                if(this.right<o.right) return -1;
                else if (this.right==right) return 0;
                else return 1;
            }
        }
        Scanner in = new Scanner(System.in);
        ArrayList<interval> intervals = new ArrayList<>();
        int n = in.nextInt();
        while(n--!=0){
            int l = in.nextInt();
            int r = in.nextInt();
            if(l>r){
                interval inte = new interval(r, l);
                intervals.add(inte);
            }else{
                interval inte = new interval(l, r);
                intervals.add(inte);
            }

        }
//        Comparator<interval> cmp = new Comparator<interval>() {
//            @Override
//            public int compare(interval o1, interval o2) {
//                if(o1.right<o2.right) return -1;
//                else if(o1.right==o2.right) return 0;
//                else return 1;
//            }
//        };
//        Collections.sort(intervals, cmp);
        Collections.sort(intervals);
        int i=0, j=0, count=0;
        while(i<intervals.size()){
            ++count;
            while (j<intervals.size() && intervals.get(i).right >= intervals.get(j).left){
                ++j;
            }
            i = j;
        }
        System.out.println(intervals.size()-count);
    }
}
