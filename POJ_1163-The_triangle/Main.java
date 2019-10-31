import java.util.Scanner;

public class Main{
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        int R = in.nextInt();
        int[][] max_sum = new int[R][R];
        int i=0;
        while(i<R){
            for(int k=0; k<=i; ++k){
                max_sum[i][k] = in.nextInt();
            }
            ++i;
        }

        for(int k=R-2; k>=0; --k){
            for(int j=0; j<=k; ++j){
                max_sum[k][j] += Math.max(max_sum[k+1][j], max_sum[k+1][j+1]);
            }
        }

        System.out.println(max_sum[0][0]);
    }
}
