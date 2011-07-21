import java.io.IOException;
import java.io.InputStream;
import java.util.Arrays;
import java.util.InputMismatchException;

public class IM {

	static final int INF = 1000000000;
	int maxnodes, maxedges, src, dest, edges;
	int[] top, work, Q;
	int[] head, prev, flow, cap, dist;

	public void init(int maxnodes, int maxedges) {
		this.maxnodes = maxnodes;
		this.maxedges = maxedges;
		top = new int[maxnodes];
		work = new int[maxnodes];
		Q = new int[maxnodes];
		head = new int[maxedges];
		prev = new int[maxedges];
		flow = new int[maxedges];
		cap = new int[maxedges];
		dist = new int[maxnodes];
		clear();
	}

	public void clear() {
		Arrays.fill(top, -1);
		edges = 0;
	}

	public void addEdge(int u, int v, int capacity) {
		head[edges] = v;
		cap[edges] = capacity;
		flow[edges] = 0;
		prev[edges] = top[u];
		top[u] = edges++;
		head[edges] = u;
		cap[edges] = 0;
		flow[edges] = 0;
		prev[edges] = top[v];
		top[v] = edges++;
	}

	boolean dinic_bfs() {
		Arrays.fill(dist, -1);
		dist[src] = 0;
		int sizeQ = 0;
		Q[sizeQ++] = src;
		for (int i = 0; i < sizeQ; i++) {
			int u = Q[i];
			for (int e = top[u]; e >= 0; e = prev[e]) {
				int v = head[e];
				if (flow[e] < cap[e] && dist[v] < 0) {
					dist[v] = dist[u] + 1;
					Q[sizeQ++] = v;
				}
			}
		}
		return dist[dest] >= 0;
	}

	int dinic_dfs(int u, int f) {
		if (u == dest)
			return f;

		for (int e = work[u]; e >= 0; work[u] = e = prev[e]) {
			int v = head[e];
			if (flow[e] < cap[e] && dist[v] == dist[u] + 1) {
				int df = dinic_dfs(v, Math.min(f, cap[e] - flow[e]));
				if (df > 0) {
					flow[e] += df;
					flow[e ^ 1] -= df;
					return df;
				}
			}
		}
		return 0;
	}

	public int maxFlow(int src, int dest) {
		this.src = src;
		this.dest = dest;
		int flow = 0;
		while (dinic_bfs()) {
			System.arraycopy(top, 0, work, 0, maxnodes);
			while (true) {
				int df = dinic_dfs(src, INF);
				if (df == 0)
					break;
				flow += df;
			}
		}
		return flow;
	}

	public static void main(String[] args) {
		InputReader sc = new InputReader(System.in);
		IM task = new IM();
		task.init(31000, 1000000);
		int tc = sc.nextInt();
		while (tc-- > 0) {
			task.clear();
			int n = sc.nextInt();
			int m = sc.nextInt();

			int s = n;
			int t = n + 1;

			task.addEdge(s, 1, 2);
			task.addEdge(0, t, 1);
			task.addEdge(2, t, 1);

			for (int k = 0; k < m; k++) {
				int u = sc.nextInt();
				int v = sc.nextInt();
				--u;
				--v;
				task.addEdge(u, v, 1);
				task.addEdge(v, u, 1);
			}

			int flow = task.maxFlow(s, t);
			System.out.println(flow == 2 ? "YES" : "NO");
		}
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

		private boolean isSpaceChar(int c) {
			return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
		}
	}
}
