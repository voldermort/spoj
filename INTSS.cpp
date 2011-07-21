#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
#include <memory.h>
using namespace std;

typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<int> vi;
typedef long long ll;
#define N 256

int w[N];
bool g[N][N];
ll res;

void maximumIndependentSet(vi& oldSet, vi &a, int ne, int ce, ll curSum) {
	int nod = 0;
	int minnod = ce;
	int fixp = -1;
	int s = -1;

	for (int i = 0; i < ce && minnod != 0; i++) {
		int p = oldSet[i];
		int cnt = 0;
		int pos = -1;

		for (int j = ne; j < ce; j++)
			if (g[a[p]][a[oldSet[j]]]) {
				if (++cnt == minnod)
					break;
				pos = j;
			}

			if (minnod > cnt) {
				minnod = cnt;
				fixp = p;
				if (i < ne)
					s = pos;
				else {
					s = i;
					nod = 1;
				}
			}
	}

	vi newSet(ce);

	for (int k = minnod + nod; k >= 1; k--) {
		int sel = oldSet[s];
		oldSet[s] = oldSet[ne];
		oldSet[ne] = sel;

		int newne = 0;
		for (int i = 0; i < ne; i++)
			if (!g[a[sel]][a[oldSet[i]]])
				newSet[newne++] = oldSet[i];

		int newce = newne;
		ll remain = 0;
		for (int i = ne + 1; i < ce; i++)
			if (!g[a[sel]][a[oldSet[i]]]) {
				newSet[newce++] = oldSet[i];
				remain += w[a[oldSet[i]]];
			}

			curSum += w[a[sel]];

			if (newce == 0) {
				res = max(res, curSum);
			} else if (newne < newce) {
				if (curSum + remain > res)
					maximumIndependentSet(newSet, a, newne, newce, curSum);
			}

			curSum -= w[a[sel]];

			if (k > 1)
				for (s = ++ne; !g[a[fixp]][a[oldSet[s]]]; s++)
					;
	}
}

void dfs(vector<vi> &graph, int u, vector<bool> &vis, vi &comp){
	vis[u]=true;
	comp.push_back(u);
	for(int j=0; j<graph[u].size(); j++){
		int v=graph[u][j];
		if(!vis[v])dfs(graph, v, vis, comp);
	}
}

int main() {
	//freopen("input.txt","r",stdin);

	int t;
	scanf("%d", &t);

	while (t-- > 0) {
		int n;
		scanf("%d", &n);

		int k;
		scanf("%d", &k);

		for (int i = 0; i < n; i++) {
			scanf("%d", &w[i]);
		}

		vector<vi> graph(n);

		memset(g, 0, sizeof(g));
		for (int i = 0; i < k; i++) {
			int v1,v2;
			scanf("%d%d", &v1, &v2);
			--v1;
			--v2;
			g[v1][v2] = g[v2][v1] = true;
			graph[v1].push_back(v2);
			graph[v2].push_back(v1);
		}

		ll total = 0;
		vector<bool> vis(n);

		for(int i=0; i<n; i++){
			if(!vis[i]){
				vi comp;
				dfs(graph, i, vis, comp);
				int m=comp.size();
				vi all(m);
				for(int j=0; j<m; j++) all[j] = j;
				res = 0;
				maximumIndependentSet(all, comp, 0, m, 0);
				total += res;
			}
		}

		printf("%ld\n", total);
	}
}
