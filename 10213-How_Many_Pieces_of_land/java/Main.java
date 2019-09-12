import java.util.*;
import java.math.*;

public class Main {
    public static void main(String[] args) {
        Scanner input=new Scanner(System.in);
        int T=input.nextInt();
        for(int kase=1;kase<=T;++kase) {
            BigInteger n=input.nextBigInteger();
            BigInteger ans=n.pow(3);
            ans=ans.subtract(n.pow(2).multiply(BigInteger.valueOf(6)));
            ans=ans.add(n.multiply(BigInteger.valueOf(23)));
            ans=ans.subtract(BigInteger.valueOf(18));
            ans=ans.multiply(n);
            ans=ans.divide(BigInteger.valueOf(24));
            ans=ans.add(BigInteger.ONE);
            System.out.println(ans);
        }
        input.close();
    }
}
