import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    private static List<String[]> parts;//存储所有ip，每个ip都经过split
    private static List<List<Integer>> diff_ips;//存储二进制
    private static Scanner scanner = new Scanner(System.in);

    private static List<Integer> dec2bin(String decStr) {
        int dec = Integer.parseInt(decStr);
        List<Integer> bin = new ArrayList<>();
        while (dec != 0) {
            bin.add(dec % 2);
            dec /= 2;
        }
        //补全前导0
        while(bin.size()<8){
            bin.add(0);
        }
        return bin;
    }

    /**
     * 寻找4个ip段，从第几段开始不同
     *
     * @return -1表示全部相同
     */
    private static int findFirtDiffIp() {
        //4个ip段，从第几个开始不同（0为起始）
        int diff = 0;
        //4个ip段
        for (int i = 0; i < 4; ++i) {
            boolean inconsistent = false;
            //T个4段ip
            for (int j = 0; j < parts.size(); ++j) {
                //出现了不一样的ip段
                if (!parts.get(0)[i].equals(parts.get(j)[i])) {
                    diff = i;
                    inconsistent = true;//连退两层
                    break;
                }
            }
            //全部相同
            if (i == 3 && !inconsistent) diff = -1;
            if (inconsistent) break;
        }
        return diff;
    }

    /**
     * 寻找不相同的那个ip段从第几个位开始不同
     * @return
     */
    private static int findFirstDiffBit(){
        //8位
        int diff_bit = 0;
        //倒序存储的
        for (int i = 7; i >= 0; --i) {
            boolean inconsistent = false;
            for (int j = 0; j < diff_ips.size(); ++j) {
                if (diff_ips.get(0).get(i) != diff_ips.get(j).get(i)) {
                    diff_bit = i;
                    inconsistent = true;
                    break;
                }
            }
            if (inconsistent) break;
        }
        return diff_bit;
    }

    private static void print(int diff, int min_ip, int mask){
        for (int i = 0; i < diff; ++i) {
            System.out.print(parts.get(0)[i]);
            System.out.print(".");
        }
        System.out.print(min_ip);
        if (diff != 3) {
            System.out.print(".");
        }
        for (int i = diff + 1; i < 4; ++i) {
            System.out.print(0);
            if (i != 3) {
                System.out.print(".");
            }
        }
        System.out.print('\n');
        for (int i = 0; i < diff; ++i) {
            System.out.print(255);
            System.out.print(".");
        }
        System.out.print(mask);
        if (diff != 3) {
            System.out.print(".");
        }
        for (int i = diff + 1; i < 4; ++i) {
            System.out.print(0);
            if (i != 3) {
                System.out.print(".");
            }
        }
        System.out.print('\n');
    }

    public static void main(String[] args) {
        while (scanner.hasNext()) {
            //1. 读取输入
            int T = Integer.parseInt(scanner.nextLine());
            parts = new ArrayList<>();
            String ip = new String();
            while (T-- != 0) {
                ip = scanner.nextLine();
                parts.add(ip.split("\\."));
            }
            //2. 寻找哪个ip段不同
            int diff = findFirtDiffIp();
            //全部相同
            if(diff == -1){
                System.out.println(ip);
                System.out.println("255.255.255.255");
            }else{
                //3. 将不同的ip段转为二进制
                diff_ips = new ArrayList<>();
                for (int i = 0; i < parts.size(); ++i) {
                    diff_ips.add(dec2bin(parts.get(i)[diff]));
                }

                //4. 寻找不同的比特位
                int diff_bit = findFirstDiffBit();
                //5. 合成最小ip与mask
                int min_ip = 0;
                int mask = 0;
                for (int i = diff_bit + 1; i < 8; ++i) {
                    min_ip += diff_ips.get(0).get(i) * Math.pow(2, i);
                    mask += 1 * Math.pow(2, i);
                }
                //5. 打印输出
                print(diff, min_ip, mask);
            }
        }
    }
}