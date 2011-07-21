#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;

#define MAXN (1<<17)

int max1[MAXN + MAXN];
int max2[MAXN + MAXN];

void check(int *res1, int *res2, int x) {
	if(*res1 <= x) {
		*res2 = *res1;
		*res1 = x;
	} else if(*res2 <= x) {
		*res2 = x;
	}
}

int main() {
	//freopen("input.txt","r",stdin);

	int n;
	scanf("%d", &n);
	fill(max1, max1 + MAXN*2, INT_MIN);
	fill(max2, max2 + MAXN*2, INT_MIN);

	for(int i=MAXN;i<MAXN+n;i++) {
		scanf("%d", &max1[i]);
	}

	for (int i = MAXN - 1; i > 0; i--) {
		int n0 = i + i;
		int n1 = i + i + 1;

		max1[i] = max1[n0];
		max2[i] = max2[n0];

		check(&max1[i], &max2[i], max1[n1]);
		check(&max1[i], &max2[i], max2[n1]);
	}

	int m;
	scanf("%d", &m);

	for(int i=0;i<m;i++) {
		char s[20];
		scanf("%s", s);

		if(s[0] == 'U') {
			int a,x;
			scanf("%d%d", &a, &x);

			a += MAXN - 1;
			max1[a]=x;
			max2[a]=INT_MIN;
			for (a >>= 1; a > 0; a >>= 1) {
				int n0 = a + a;
				int n1 = a + a + 1;

				max1[a] = max1[n0];
				max2[a] = max2[n0];

				check(&max1[a], &max2[a], max1[n1]);
				check(&max1[a], &max2[a], max2[n1]);
			}
		} else {
			int a,b;
			scanf("%d%d", &a, &b);
		
			a += MAXN - 1;
			b += MAXN - 1;
			int res1 = INT_MIN;
			int res2 = INT_MIN;
			while (a <= b) {
				if ((a & 1) != 0) {
					check(&res1, &res2, max1[a]);
					check(&res1, &res2, max2[a]);
				}
				if ((b & 1) == 0) {
					check(&res1, &res2, max1[b]);
					check(&res1, &res2, max2[b]);
				}
				a = (a + 1) >> 1;
				b = (b - 1) >> 1;
			}

			printf("%d\n", res1 + res2);
		}
	}	
}
