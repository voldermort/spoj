import java.io.*;
import java.util.*;
import java.math.*;
import static java.util.Arrays.*;
import static java.util.Collections.*;
import static java.lang.Math.*;
import static java.lang.Double.parseDouble;
import static java.lang.Long.parseLong;
import static java.lang.Integer.parseInt;

public class Main {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);
        int N = sc.nextInt();
        sc.nextLine();
        for (int testCase = 1; testCase <= N; testCase++) {
            sc.nextLine();
            String s = sc.nextLine();
            s = s.replaceAll("=", "");
            String[] x = s.split("\\s+");
            BigInteger res = BigInteger.valueOf(0);
            char op = '+';
            for (String a : x) {
                if (a.length() == 0) {
                    continue;
                }
                if ("+".equals(a)) {
                    op = '+';
                } else if ("-".equals(a)) {
                    op = '-';
                } else if ("*".equals(a)) {
                    op = '*';
                } else if ("/".equals(a)) {
                    op = '/';
                } else {
                    BigInteger v = new BigInteger(a);
                    switch (op) {
                        case '+':
                            res = res.add(v);
                            break;
                        case '-':
                            res = res.subtract(v);                            
                            break;
                        case '*':
                            res = res.multiply(v);
                            break;
                        case '/':
                            res = res.divide(v);                            
                            break;
                    }
                }
            }
            pw.println(res);
            pw.flush();
        }
        pw.close();
    }
}
