import java.util.Scanner;

public class Main{
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        int R = in.nextInt();
        int[][] traingle = new int[R][R];
        int i=0;
        while(i<R){
            for(int k=0; k<=i; ++k){
                traingle[i][k] = in.nextInt();
            }
            ++i;
        }

        int[][] max_sum = new int[R][R];
        for(int k=0; k<R; ++k){
            max_sum[R-1][k] = traingle[R-1][k];
        }
        for(int k=R-2; k>=0; --k){
            for(int j=0; j<=k; ++j){
                max_sum[k][j] = traingle[k][j] + (max_sum[k+1][j]>max_sum[k+1][j+1] ? max_sum[k+1][j] : max_sum[k+1][j+1]);
            }
        }
        System.out.println(max_sum[0][0]);
    }
}
