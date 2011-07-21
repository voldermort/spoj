#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
using namespace std;

#define rep(i,n) for(int i(0),_n(n);i<_n;++i)
template<class T> void checkmin(T &a,T b){if(b<a) a=b;}
template<class T> void checkmax(T &a,T b){if(b>a) a=b;}

const int MAXN = 1<<17;

int a[MAXN];
int f[2*MAXN];
int p[MAXN];
int len;

int fmax(int a, int b) {
	int res = 0;
	a += len;
	b += len;
	while (a <= b) {
		checkmax(res, f[a]);
		checkmax(res, f[b]);
		a = (a + 1) >> 1;
		b = (b - 1) >> 1;
	}
	return res;
}

int main() {
	//freopen("input.txt","r",stdin);

	while(1){
		int n;
		scanf("%d", &n);
		if(n==0)break;

		int q;
		scanf("%d", &q);

		rep(i,n)scanf("%d", &a[i]);

		int cnt=0;
		int m=0;
		p[0]=0;

		len = 1;
		while (len < n) len += len;
		fill(f, f+2*len, 0);

		rep(i,n){
			++cnt;
			if(i==n-1 || a[i]!=a[i+1]){
				f[len + m]=cnt;
				p[m + 1]=i+1;
				++m;
				cnt=0;
			}
		}

		for (int i = len - 1; i > 0; i--) 
			f[i] = max(f[i + i], f[i + i + 1]);

		rep(k,q){
			int a,b;
			scanf("%d%d", &a, &b);
			--a;
			--b;

			int i = upper_bound(p, p+m+1, a) - p;
			int j = upper_bound(p, p+m+1, b) - p - 1;

			int res = p[i] - a;
			checkmax(res, b - p[j] + 1);
			checkmin(res, b - a + 1);
			if(j>i)checkmax(res, fmax(i, j - 1));

			printf("%d\n", res);
		}
	}
}
