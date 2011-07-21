import java.io.*;

public class Main {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintStream ps = new PrintStream(new BufferedOutputStream(System.out));
		char[] st1 = br.readLine().toCharArray();
		char[] st2 = br.readLine().toCharArray();
		int K = Integer.parseInt(br.readLine());
		int m = st2.length;
		int n = st1.length;
		int[][] dp = new int[m + 1][n + 1];
		for (int i = 1; i <= m; i++) {
			dp[i][0] = K * i;
		}
		for (int j = 1; j <= n; j++) {
			dp[0][j] = K * j;
		}
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				dp[i][j] = Math.min(Math.min(K + dp[i - 1][j], K + dp[i][j - 1]), dp[i - 1][j - 1]
						+ Math.abs(st1[j - 1] - st2[i - 1]));
			}
		}
		ps.print(dp[m][n]);
		ps.close();
	}
}
