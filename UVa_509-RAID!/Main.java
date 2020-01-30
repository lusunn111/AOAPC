import java.util.*;

//测试样例和udebug都过了，但是runtime error
public class Main {
    private static Scanner scanner = new Scanner(System.in);
    private static List<List<List<Integer>>> raid;
    private static int d;//num of disks/cols
    private static int s;//num of bits of each block
    private static int b;//rows
    private static String parity;
    private static List<PosX> Xs;

    private static class PosX {
        //这边的行列与题意中的行列是相反的，是读入数据时的行列，与input的顺序相同，input是一列一列的输入的
        int row;
        int col;
        int bit;

        PosX(int r, int c, int b) {
            this.row = r;
            this.col = c;
            this.bit = b;
        }
    }

    private static boolean readRaid() {
        raid = new ArrayList<>();
        Xs = new ArrayList<>();
        d = Integer.parseInt(scanner.next());
        if (d == 0) {
            return false;
        }
        s = Integer.parseInt(scanner.next());
        b = Integer.parseInt(scanner.next());
        parity = scanner.next();
        //读取raid
        for (int i = 0; i < d; ++i) {
            String diskStr = scanner.next();
            List<List<Integer>> disk = new ArrayList<>();
            //读取一个disk
            for (int j = 0; j < diskStr.length(); j += s) {
                List<Integer> block = new ArrayList<>();
                //读取一个block
                String blockStr = diskStr.substring(j, j + s);
                for (int k = 0; k < s; ++k) {
                    int c = blockStr.charAt(k) - '0';
                    if (c == 'x' - '0') {
                        Xs.add(new PosX(i, j / s, k));
                    }
                    block.add(c);
                }
                disk.add(block);
            }
            raid.add(disk);
        }
        return true;
    }

    private static boolean removeX() {
        int target;
        if ("E".equals(parity)) {
            target = 0;
        } else {
            target = 1;
        }

        for (PosX posX : Xs) {
            int r = posX.row;
            int c = posX.col;
            int b = posX.bit;
            //对列遍历
            int res = -1;
            for (int i = 0; i < d; ++i) {
                //跳过需要remove的X
                if (i == r) {
                    continue;
                }

                if (res == -1) {
                    //起始
                    res = raid.get(i).get(c).get(b);
                } else {
                    if (raid.get(i).get(c).get(b) == 'x' - '0') {
                        //出现另外一个x
                        return false;
                    } else {
                        res ^= raid.get(i).get(c).get(b);
                    }
                }
            }
            raid.get(r).get(c).set(b, res ^ target);
        }
        return true;
    }

    private static boolean isValid() {
        int target;
        if ("E".equals(parity)) {
            target = 0;
        } else {
            target = 1;
        }

        for (int i = 0; i < b; ++i) {
            for (int k = 0; k < s; ++k) {
                int res = raid.get(0).get(i).get(k);
                for (int j = 1; j < d; ++j) {
                    res ^= raid.get(j).get(i).get(k);
                }
                if (res != target) {
                    return false;
                }
            }
        }
        return true;
    }

    private static String bin2Hex(String resBinStr) {
        int zero_padding = resBinStr.length() % 4;
        String zeros = new String();
        for (int i = 0; i < zero_padding; ++i) {
            zeros += "0";
        }
        resBinStr += zeros;
        String resHexStr = new String();
        for (int i = 0; i < resBinStr.length(); i += 4) {
            resHexStr += Integer.toHexString(Integer.valueOf(resBinStr.substring(i, i + 4), 2)).toUpperCase();
        }
        return resHexStr;
    }

    private static String print() {
        String resBinStr = new String();
        for (int i = 0; i < b; ++i) {
            for (int j = 0; j < d; ++j) {
                if (i % d == j) {
                    continue;
                }
                for (int k = 0; k < s; ++k) {
                    resBinStr += raid.get(j).get(i).get(k);
                }
            }
        }
        return bin2Hex(resBinStr);
    }

    public static void main(String[] args) {
        int kase = 0;
        while (scanner.hasNext()) {
            ++kase;
            if (!readRaid())
                break;
            //System.out.println(raid);
            if (!removeX()) {
                System.out.print("Disk set " + kase + " is invalid.\n");
                continue;
            }
            if (!isValid()) {
                System.out.print("Disk set " + kase + " is invalid.\n");
                continue;
            }
            System.out.println("Disk set " + kase + " is valid, contents are: " + print());
        }
    }
}