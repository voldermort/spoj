#include <cstdio>
#include <vector>
#include <algorithm>
#include <memory.h>
using namespace std;

typedef vector<int> vi;
#define N 50

int w[N];
bool g[N][N], g1[N][N];
int res;

void maximumIndependentSet(vi& oldSet, int ne, int ce, int curSum) {
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
		long remain = 0;
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

			++ne;
			if (k > 1)
				for (s = ne; !g[fixp][oldSet[s]]; s++)
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

		vi w1(n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &w1[i]);
		}

		memset(g1, 0, sizeof(g1));
		for (int i = 0; i < k; i++) {
			int v1,v2;
			scanf("%d%d", &v1, &v2);
			g1[v1][v2] = g1[v2][v1] = true;
		}

		int q;
		scanf("%d", &q);

		for (int i = 0; i < q; i++) {
			int qn;
			scanf("%d", &qn);

			vi a(qn);
			for (int j = 0; j < qn; j++) scanf("%d", &a[j]);

			for (int j = 0; j < qn; j++){
				w[j] = w1[a[j]];
				for (int k = 0; k < qn; k++) g[j][k]=g1[a[j]][a[k]];
			}

			vi all(qn);
			for (int i = 0; i < qn; i++) all[i] = i;

			res = 0;
			maximumIndependentSet(all, 0, qn, 0);

			printf("%d\n", res);
		}

		printf("\n");
	}
}
