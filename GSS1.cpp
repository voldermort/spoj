#include <cstdio>
#include <vector>
using namespace std;

#define MAXN (1<<16)

int sum[MAXN + MAXN];
int pref[MAXN + MAXN];
int suff[MAXN + MAXN];
int maxs[MAXN + MAXN];

int main() {
	//freopen("input.txt","r",stdin);

	int n;
	scanf("%d", &n);

	for(int i=MAXN;i<MAXN+n;i++) {
		int x;
		scanf("%d", &x);
		sum[i]=x;
		pref[i]=x;
		suff[i]=x;
		maxs[i]=x;
	}

	for (int i = MAXN - 1; i > 0; i--) {
		int n0 = i + i;
		int n1 = i + i + 1;

		sum[i] = sum[n0] + sum[n1];
		maxs[i] = max( max(maxs[n0], maxs[n1]), suff[n0] + pref[n1]);
		pref[i] = max(pref[n0], sum[n0] + pref[n1]);
		suff[i] = max(suff[n1], sum[n1] + suff[n0]);
	}

	int m;
	scanf("%d", &m);

	for(int i=0;i<m;i++) {
		int a,b;
		scanf("%d%d", &a, &b);
		
		a += MAXN - 1;
		b += MAXN - 1;
		vector<int> left, right;
		while (a <= b) {
			if ((a & 1) != 0)
				left.push_back(a);
			if ((b & 1) == 0)
				right.push_back(b);
			a = (a + 1) >> 1;
			b = (b - 1) >> 1;
		}

		copy(right.rbegin(), right.rend(), back_inserter(left));

		int res = -1000000000;
		int cur = -1000000000;
		for(int i=0;i<left.size();i++){
			int x = left[i];
			res = max(res, max(maxs[x], cur + pref[x]));
			cur = max(suff[x], cur + sum[x]);
		}

		printf("%d\n", res);
	}	
}
