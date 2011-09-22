import java.io.*;
import java.util.*;

public class DYNACON {

	static class Graph {
		Map<Integer, Map<Integer, Integer>> edges = new HashMap<Integer, Map<Integer, Integer>>();

		void add0(int u, int v) {
			if (!edges.containsKey(u))
				edges.put(u, new HashMap<Integer, Integer>());
			if (!edges.get(u).containsKey(v))
				edges.get(u).put(v, 0);
			edges.get(u).put(v, edges.get(u).get(v) + 1);
		}

		void add(int u, int v) {
			add0(u, v);
			add0(v, u);
		}

		boolean remove0(int u, int v) {
			if (!edges.containsKey(u))
				edges.put(u, new HashMap<Integer, Integer>());
			if (!edges.get(u).containsKey(v))
				return false;
			edges.get(u).put(v, edges.get(u).get(v) - 1);
			if (edges.get(u).get(v) == 0)
				edges.get(u).remove(v);
			return true;
		}

		boolean remove(int u, int v) {
			remove0(u, v);
			return remove0(v, u);
		}

		Set<Integer> getAdj(int u) {
			if (!edges.containsKey(u))
				return Collections.emptySet();
			return edges.get(u).keySet();
		}
	}

	static class DisjointSets {
		int[] p;
		int[] rank;

		public DisjointSets(int size) {
			p = new int[size];
			for (int i = 0; i < size; i++) {
				p[i] = i;
			}
			rank = new int[size];
		}

		public int root(int x) {
			while (x != p[x])
				x = p[x];
			return x;
		}

		public void unite(int a, int b) {
			a = root(a);
			b = root(b);
			if (a == b)
				return;
			if (rank[a] < rank[b]) {
				p[a] = b;
			} else {
				p[b] = a;
				if (rank[a] == rank[b])
					++rank[a];
			}
		}
	}

	static boolean connected(Graph dsGraph, Graph deltaGraph, int a, int b, boolean[] vis) {
		vis[a] = true;
		if (a == b)
			return true;
		for (int v : dsGraph.getAdj(a)) {
			if (!vis[v]) {
				if (connected(dsGraph, deltaGraph, v, b, vis))
					return true;
			}
		}
		for (int v : deltaGraph.getAdj(a)) {
			if (!vis[v]) {
				if (connected(dsGraph, deltaGraph, v, b, vis))
					return true;
			}
		}
		return false;
	}

	// Usage example
	public static void main(String[] args) throws Exception {
		PrintWriter pw = new PrintWriter(System.out);

		int n = nextInt();
		Graph g = new Graph();

		int q = nextInt();
		int[] vt = new int[q];
		int[] va = new int[q];
		int[] vb = new int[q];

		for (int i = 0; i < q; i++) {
			String type = nextToken();
			vt[i] = "add".equals(type) ? 0 : "rem".equals(type) ? 1 : 2;
			int a = nextInt() - 1;
			int b = nextInt() - 1;
			va[i] = Math.min(a, b);
			vb[i] = Math.max(a, b);
		}

		int block = (int) Math.sqrt(q);

		for (int i = 0; i < q; i += block) {
			Set<Long> removedEdges = new HashSet<Long>();

			for (int j = i; j < Math.min(i + block, q); j++) {
				if (vt[j] == 1) {
					if (g.remove(va[i], vb[i])) {
						removedEdges.add(((long) va[i] << 32) + vb[i]);
					}
				}
			}

			DisjointSets ds = new DisjointSets(n);
			for (int u = 0; u < n; u++) {
				for (int v : g.getAdj(u)) {
					ds.unite(u, v);
				}
			}

			Graph deltaGraph = new Graph();
			for (long e : removedEdges) {
				deltaGraph.add(ds.root((int) (e >>> 32)), ds.root((int) (e & 0xFFFF)));
			}

			Graph dsGraph = new Graph();
			for (int u = 0; u < n; u++) {
				for (int v : g.getAdj(u)) {
					int a = ds.root(u);
					int b = ds.root(v);
					if (a != b)
						dsGraph.add(a, b);
				}
			}

			for (int j = i; j < Math.min(i + block, q); j++) {
				if (vt[j] == 0) {
					deltaGraph.add(ds.root(va[j]), ds.root(vb[j]));
					g.add(va[j], vb[j]);
				} else if (vt[j] == 1) {
					deltaGraph.remove(ds.root(va[j]), ds.root(vb[j]));
					g.remove(va[j], vb[j]);
				} else {
					String res = connected(dsGraph, deltaGraph, ds.root(va[j]), ds.root(vb[j]), new boolean[n]) ? "YES"
							: "NO";
					pw.println(res);
				}
			}
		}
		pw.close();
	}

	static int nextInt() throws IOException {
		return Integer.parseInt(nextToken());
	}

	static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
	static StringTokenizer tokenizer;

	static String nextToken() throws IOException {
		while (tokenizer == null || !tokenizer.hasMoreTokens()) {
			tokenizer = new StringTokenizer(reader.readLine());
		}
		return tokenizer.nextToken();
	}
}
