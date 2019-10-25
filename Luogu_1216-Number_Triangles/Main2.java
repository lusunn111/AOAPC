import java.util.ArrayList;
import java.util.Scanner;

//TLE，能不递归尽量不要用递归吧，虽然没有重复计算节点但是不知道为什么TLE了
public class Main{
    private static ArrayList<ArrayList<Integer>> max_sum = new ArrayList<>();
    private static ArrayList<ArrayList<Integer>> traingle = new ArrayList<>();
    private static int R;
    static int maxSum(int row, int col){
        if(row==R-1) return traingle.get(R-1).get(col);
        else if(max_sum.get(row).get(col)>=0) return max_sum.get(row).get(col);
        else{
            if(maxSum(row+1, col) > maxSum(row+1, col+1))
                return traingle.get(row).get(col) + maxSum(row+1, col);
            else
                return traingle.get(row).get(col) + maxSum(row+1, col+1);
        }
    }
    static void initMaxSum(){
        for(int i=0; i<R; i++){
            ArrayList<Integer> temp = new ArrayList<>();
            for(int j=0; j<R; ++j){
                temp.add(-1);
            }
            max_sum.add(temp);
        }
    }
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        R = in.nextInt();
        int i=0;
        while(i<R){
            ArrayList<Integer> temp = new ArrayList<>();
            for(int k=0; k<=i; ++k){
                temp.add(in.nextInt());
            }
            traingle.add(temp);
            ++i;
        }

        initMaxSum();
        System.out.println(maxSum(0, 0));
    }
}
