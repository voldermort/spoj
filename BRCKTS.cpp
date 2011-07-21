#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;

#define rep(i,n) for(int i(0),_n(n);i<_n;++i)

#define MAXN (1<<15)

int pl[MAXN + MAXN];
int pr[MAXN + MAXN];

char s[MAXN];

int main() {
	//freopen("input.txt","r",stdin);

	rep(tc,10){
		int n;
		scanf("%d", &n);

		int cnt=1;
		while(cnt<n)cnt<<=1;

		fill(pl, pl + cnt*2, 0);
		fill(pr, pr + cnt*2, 0);

		scanf("%s", s);

		for(int i=0; s[i]; i++){
			pl[i + cnt] = s[i]==')';
			pr[i + cnt] = s[i]=='(';
		}

		for (int i = cnt - 1; i > 0; i--) {
			int n0 = i + i;
			int n1 = i + i + 1;

			pl[i] = pl[n0] + pl[n1] - min(pr[n0], pl[n1]);
			pr[i] = pr[n0] + pr[n1] - min(pr[n0], pl[n1]);
		}

		printf("Test %d:\n", tc+1);

		int m;
		scanf("%d", &m);
		rep(i,m){
			int a;
			scanf("%d", &a);
			if(a==0) printf(pl[1]==0&&pr[1]==0?"YES\n":"NO\n");
			else {
				a += cnt - 1;
				swap(pl[a], pr[a]);
				for (a >>= 1; a > 0; a >>= 1) {
					int n0 = a + a;
					int n1 = a + a + 1;

					pl[a] = pl[n0] + pl[n1] - min(pr[n0], pl[n1]);
					pr[a] = pr[n0] + pr[n1] - min(pr[n0], pl[n1]);
				}
			}
		}
	}	
}
