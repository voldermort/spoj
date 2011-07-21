import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.math.BigInteger;
import java.util.InputMismatchException;
import java.util.Scanner;

public class Main {
	public static void main(String[] args) throws Exception {
		BigInteger[] a = new BigInteger[999 + 1];
		String[] b = new String[a.length];
		long time = System.currentTimeMillis();
		a[1] = BigInteger.ZERO;
		for (int i = 2; i < a.length; i++) {
			if (i % 2 == 0)
				a[i] = a[i - 1].multiply(BigInteger.valueOf(2)).add(BigInteger.ONE);
			else
				a[i] = a[i - 1].multiply(BigInteger.valueOf(2)).subtract(BigInteger.ONE);
		}
		for (int i = 1; i < a.length; i++) {
			b[i] = a[i].toString();
		}
		System.err.println(System.currentTimeMillis() - time);

		Scanner sc=new Scanner(System.in); 
		
		long time1 = System.currentTimeMillis();
//		InputReader ir = new InputReader(System.in);
		while (sc.hasNext()) {
//			int x = ir.nextInt();
			int x=sc.nextInt();
//			if (x == -1)
//				break;
			System.out.println(b[x]);
		}
		System.err.println(System.currentTimeMillis() - time1);
	}

	private static class InputReader {
		private InputStream stream;
		private byte[] buf = new byte[1024];
		private int curChar, numChars;

		public InputReader(InputStream stream) {
			this.stream = stream;
		}

		private int read() {
			if (numChars == -1)
				throw new InputMismatchException();
			if (curChar >= numChars) {
				curChar = 0;
				try {
					numChars = stream.read(buf);
				} catch (IOException e) {
					throw new InputMismatchException();
				}
				if (numChars <= 0)
					return -1;
			}
			return buf[curChar++];
		}

		public int nextInt() {
			int c = read();
			while (isSpaceChar(c)) {
				if (c == -1)
					return -1;
				c = read();
			}
			int res = 0;
			do {
				if (c < '0' || c > '9')
					return -1;
				res *= 10;
				res += c - '0';
				c = read();
			} while (!isSpaceChar(c));
			return res;
		}

		private boolean isSpaceChar(int c) {
			return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
		}
	}
}
