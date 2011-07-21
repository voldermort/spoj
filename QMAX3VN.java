import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.InputMismatchException;
import java.util.Random;

public class Main {

	static Random rnd = new Random();
	Node root;
	int[] rand;
	int cnt;

	static class Node {
		int cnt;
		int prio;
		int value;
		int max = Integer.MIN_VALUE;
		Node l;
		Node r;
	}

	int cnt(Node p) {
		return p == null ? 0 : p.cnt;
	}

	int max(Node p) {
		return p == null ? Integer.MIN_VALUE : p.max;
	}

	void update(Node p) {
		p.cnt = 1 + cnt(p.l) + cnt(p.r);
		p.max = Math.max(p.value, Math.max(max(p.l), max(p.r)));
	}

	Node merge(Node l, Node r) {
		Node res;
		if (l == null)
			res = r;
		else if (r == null)
			res = l;
		else if (l.prio < r.prio) {
			l.r = merge(l.r, r);
			res = l;
		} else {
			r.l = merge(l, r.l);
			res = r;
		}
		update(res);
		return res;
	}

	Node L, R;

	void split(Node t, int key) {
		if (t == null) {
			L = R = null;
			return;
		}

		if (key <= cnt(t.l)) {
			split(t.l, key);
			t.l = R;
			R = t;
		} else {
			split(t.r, key - cnt(t.l) - 1);
			t.r = L;
			L = t;
		}

		update(t);
	}

	Node add(Node t, Node it, int index) {
		Node res;
		if (t == null)
			res = it;
		else if (it.prio < t.prio) {
			split(t, index);
			it.l = L;
			it.r = R;
			res = it;
		} else {
			if (index <= cnt(t.l))
				t.l = add(t.l, it, index);
			else
				t.r = add(t.r, it, index - cnt(t.l) - 1);
			res = t;
		}
		update(res);
		return res;
	}

	public void add(int index, int value) {
		Node it = new Node();
		it.value = value;
		// it.prio = rnd.nextInt();
		it.prio = rand[cnt++];
		it.cnt = 1;
		root = add(root, it, index);
	}

	public int max(int a, int b) {
		split(root, b);
		Node R1 = R;
		split(L, a - 1);
		int res = max(R);
		root = merge(merge(L, R), R1);
		return res;
	}

	public static int[] getRandomPermutation(int n, Random rnd) {
		int[] res = new int[n];
		for (int i = 0; i < n; i++) {
			res[i] = i;
		}
		for (int i = res.length; i > 1; i--) {
			int j = rnd.nextInt(i);
			int t = res[i - 1];
			res[i - 1] = res[j];
			res[j] = t;
		}
		return res;
	}

	public static void main(String[] args) throws Exception {
//		long time = System.currentTimeMillis();
		Main treap = new Main();

		InputReader sc = new InputReader(System.in);
//		 InputReader sc = new InputReader(new FileInputStream("D:/projects/cpp/spoj/input_ref.txt"));
//		 PrintWriter pw = new PrintWriter("D:/projects/cpp/spoj/output2.txt");
		int n = sc.nextInt();
		treap.rand = getRandomPermutation(n, rnd);
		for (int i = 0; i < n; i++) {
			char t = sc.nextChar();
			int x = sc.nextInt();
			int y = sc.nextInt();

			if (t == 'A') {
				--y;
				treap.add(y, x);
			} else {
				// --x;
				// --y;
				int res = treap.max(x, y);
//				 pw.println(res);
				System.out.println(res);
			}
		}
//		 pw.close();
//		 System.err.println(System.currentTimeMillis() - time);
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
			while (isSpaceChar(c))
				c = read();
			int sgn = 1;
			if (c == '-') {
				sgn = -1;
				c = read();
			}
			int res = 0;
			do {
				if (c < '0' || c > '9')
					throw new InputMismatchException();
				res *= 10;
				res += c - '0';
				c = read();
			} while (!isSpaceChar(c));
			return res * sgn;
		}

		public char nextChar() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			return (char) c;
		}

		private boolean isSpaceChar(int c) {
			return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
		}
	}

}
