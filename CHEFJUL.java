import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class Main {

	public static BigInteger detKraut(BigDecimal a[][], int n) {
		try {
			for (int i = 0; i < n; i++) {
				boolean nonzero = false;
				for (int j = 0; j < n; j++)
					if (a[i][j].compareTo(new BigDecimal(BigInteger.ZERO)) > 0)
						nonzero = true;
				if (!nonzero)
					return BigInteger.ZERO;
			}

			BigDecimal scaling[] = new BigDecimal[n];
			for (int i = 0; i < n; i++) {
				BigDecimal big = new BigDecimal(BigInteger.ZERO);
				for (int j = 0; j < n; j++)
					if (a[i][j].abs().compareTo(big) > 0)
						big = a[i][j].abs();
				scaling[i] = (new BigDecimal(BigInteger.ONE)).divide(big, 45, BigDecimal.ROUND_HALF_EVEN);
			}

			int sign = 1;

			for (int j = 0; j < n; j++) {

				for (int i = 0; i < j; i++) {
					BigDecimal sum = a[i][j];
					for (int k = 0; k < i; k++)
						sum = sum.subtract(a[i][k].multiply(a[k][j]));
					a[i][j] = sum;
				}

				BigDecimal big = new BigDecimal(BigInteger.ZERO);
				int imax = -1;
				for (int i = j; i < n; i++) {
					BigDecimal sum = a[i][j];
					for (int k = 0; k < j; k++)
						sum = sum.subtract(a[i][k].multiply(a[k][j]));
					a[i][j] = sum;
					BigDecimal cur = sum.abs();
					cur = cur.multiply(scaling[i]);
					if (cur.compareTo(big) >= 0) {
						big = cur;
						imax = i;
					}
				}

				if (j != imax) {

					for (int k = 0; k < n; k++) {
						BigDecimal t = a[j][k];
						a[j][k] = a[imax][k];
						a[imax][k] = t;
					}

					BigDecimal t = scaling[imax];
					scaling[imax] = scaling[j];
					scaling[j] = t;

					sign = -sign;
				}

				if (j != n - 1)
					for (int i = j + 1; i < n; i++)
						a[i][j] = a[i][j].divide(a[j][j], 45, BigDecimal.ROUND_HALF_EVEN);

			}

			BigDecimal result = new BigDecimal(1);
			if (sign == -1)
				result = result.negate();
			for (int i = 0; i < n; i++)
				result = result.multiply(a[i][i]);

			return result.divide(BigDecimal.valueOf(1), 0, BigDecimal.ROUND_HALF_EVEN).toBigInteger();

		} catch (Exception e) {
			return BigInteger.ZERO;
		}
	}

	static boolean findCycle(List<Integer>[] g, int[] color, int i, int p, int colors) {
		color[i] = colors;
		for (int j : g[i]) {
			if (j != p) {
				if (color[j] != -1)
					return true;
				if (findCycle(g, color, j, i, colors))
					return true;
			}
		}
		return false;
	}

	public static void main(String[] args) throws Exception {
		Scanner sc = new Scanner(System.in);

		int t = sc.nextInt();
		m1: while (t-- > 0) {
			int n = sc.nextInt();
			String[] s = new String[n];
			for (int i = 0; i < s.length; i++) {
				s[i] = sc.next();
			}

			List<Integer>[] g = new List[n];
			for (int i = 0; i < n; i++) {
				g[i] = new ArrayList<Integer>();
			}
			int p = sc.nextInt();
			for (int i = 0; i < p; i++) {
				int x = sc.nextInt();
				int y = sc.nextInt();
				--x;
				--y;
				g[x].add(y);
				g[y].add(x);
			}

			int colors = 0;
			int[] color = new int[n];
			Arrays.fill(color, -1);
			for (int i = 0; i < n; i++) {
				if (color[i] == -1) {
					if (findCycle(g, color, i, -1, colors++)) {
						System.out.println(0);
						continue m1;
					}
				}
			}

			int[][] a = new int[colors][colors];

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					char ch = s[i].charAt(j);
					if (ch == '0')
						continue;
					if (color[i] != color[j]) {
						--a[color[i]][color[j]];
						++a[color[i]][color[i]];
					}
				}
			}

			BigDecimal[][] b = new BigDecimal[n][n];
			for (int i = 0; i < colors; i++) {
				for (int j = 0; j < colors; j++) {
					b[i][j] = BigDecimal.valueOf(a[i][j]);
				}
			}

			BigInteger res = detKraut(b, colors - 1);
			System.out.println(res);
		}
	}
}
