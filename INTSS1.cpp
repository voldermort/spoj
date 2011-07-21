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

void maximumIndependentSet(vi& oldSet, int ne, int ce, ll curSum) {
	int nod = 0;
	int minnod = ce;
	int fixp = -1;
	int s = -1;

	for (int i = 0; i < ce && minnod != 0; i++) {
		int p = oldSet[i];
		int cnt = 0;
		int pos = -1;

		for (int j = ne; j < ce; j++)
			if (g[p][oldSet[j]]) {
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
			if (!g[sel][oldSet[i]])
				newSet[newne++] = oldSet[i];

		int newce = newne;
		ll remain = 0;
		for (int i = ne + 1; i < ce; i++)
			if (!g[sel][oldSet[i]]) {
				newSet[newce++] = oldSet[i];
				remain += w[oldSet[i]];
			}

			curSum += w[sel];

			if (newce == 0) {
				res = max(res, curSum);
			} else if (newne < newce) {
				if (curSum + remain > res)
					maximumIndependentSet(newSet, newne, newce, curSum);
			}

			curSum -= w[sel];

			if (k > 1)
				for (s = ++ne; !g[fixp][oldSet[s]]; s++)
					;
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

		vi all(n);
		vpii a;
		for (int i = 0; i < n; i++) {
			scanf("%d", &w[i]);
			a.push_back(pii(w[i],i));
			all[i] = i;
		}
		sort(a.begin(), a.end(), greater<pii>());
		vi p(n);
		for(int i=0; i<n; i++)p[a[i].second]=i,w[i]=a[i].first;

		memset(g, 0, sizeof(g));
		for (int i = 0; i < k; i++) {
			int v1,v2;
			scanf("%d%d", &v1, &v2);
			--v1;
			--v2;
			g[p[v1]][p[v2]] = g[p[v2]][p[v1]] = true;
		}

		res = 0;
		maximumIndependentSet(all, 0, n, 0);

		printf("%ld\n", res);
	}
}
