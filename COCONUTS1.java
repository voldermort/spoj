import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Scanner;

public class COCONUTS1 {

	public static long maxFlow(Graph g, int s, int t) {
		long flow = 0;
		while (true) {
			Queue<Integer> q = new LinkedList<Integer>();
			q.add(s);
			Edge[] p = new Edge[g.n];
			while (!q.isEmpty() && p[t] == null) {
				int cur = q.poll();
				for (Edge e : g.edges[cur]) {
					if (p[e.t] == null && e.cap > e.f) {
						p[e.t] = e;
						q.add(e.t);
					}
				}
			}
			if (p[t] == null) {
				break;
			}
			Path path = getPath(p, s, t);
			for (Edge e : path.edges) {
				e.f += path.f;
				g.edges[e.t].get(e.rev).f -= path.f;
			}
			flow += path.f;
		}
		return flow;
	}

	public static class Graph {
		public final int n;
		public List<Edge>[] edges;

		public Graph(int n) {
			this.n = n;
			edges = new List[n];
			for (int i = 0; i < n; i++) {
				edges[i] = new ArrayList<Edge>();
			}
		}

		void addEdge(int s, int t, int cap) {
			edges[s].add(new Edge(s, t, edges[t].size(), cap));
			edges[t].add(new Edge(t, s, edges[s].size() - 1, 0));
		}
	}

	public static class Edge {
		public int s, t, rev, cap, f;

		public Edge(int s, int t, int rev, int cap) {
			this.s = s;
			this.t = t;
			this.rev = rev;
			this.cap = cap;
		}
	}

	public static class Path {
		public List<Edge> edges = new ArrayList<Edge>();
		public int f;
	}

	public static Path getPath(Edge[] p, int s, int t) {
		Path path = new Path();
		path.f = Integer.MAX_VALUE;
		for (; t != s; t = p[t].s) {
			path.edges.add(p[t]);
			path.f = Math.min(path.f, p[t].cap - p[t].f);
		}
		return path;
	}

	public static void main(String[] args) {
		InputReader sc = new InputReader(System.in);
		while (true) {
			int n = sc.nextInt();
			int m = sc.nextInt();
			if (n == 0 && m == 0)
				return;

			int s = n;
			int t = n + 1;
			Graph g = new Graph(n + 2);

			boolean[] b = new boolean[n];
			for (int i = 0; i < n; i++) {
				b[i] = sc.nextInt() == 1;
				if (b[i])
					g.addEdge(s, i, 1);
				else
					g.addEdge(i, t, 1);
			}

			for (int k = 0; k < m; k++) {
				int u = sc.nextInt();
				int v = sc.nextInt();
				--u;
				--v;
				g.addEdge(u, v, 1);
				g.addEdge(v, u, 1);
			}

			System.out.println(maxFlow(g, s, t));
		}
	}

	private static class InputReader {
		private InputStream stream;
		private byte[] buf = new byte[1000];
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

		private boolean isSpaceChar(int c) {
			return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
		}
	}
}
