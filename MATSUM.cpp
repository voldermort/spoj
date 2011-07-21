#include <cstdio>
#include <algorithm>
#include <memory.h>
using namespace std;

#define MAXN 1025

int t[MAXN][MAXN];
int t2[MAXN][MAXN];
int R, C;

void add(int r, int c, int value) {
	for (int i = r; i <= R; i += i & -i)
		for (int j = c; j <= C; j += j & -j)
			t[i][j] += value;
}

int sum(int r, int c) {
	int res = 0;
	for (int i = r; i > 0; i &= i - 1)
		for (int j = c; j > 0; j &= j - 1)
			res += t[i][j];
	return res;
}

int sum(int r1, int c1, int r2, int c2) {
	return sum(r2, c2) - sum(r1 - 1, c2) - sum(r2, c1 - 1) + sum(r1 - 1, c1 - 1);
}

void set(int r, int c, int value) {
	add(r, c, -t2[r][c] + value);
}

int main() {
	//freopen("input.txt","r",stdin);
	int tc; scanf("%d",&tc);
	while(tc--){
		int n;
		scanf("%d",&n);
		R = C = n;
		memset(t, 0, sizeof(t));
		memset(t2, 0, sizeof(t2));

		while(true){
			char s[20];
			scanf("%s",s);

			if(!strcmp(s,"SET")){
				int r;
				int c;
				int v;
				scanf("%d %d %d",&r,&c,&v);
				++r;
				++c;
				set(r, c, v);
				t2[r][c] = v;
			} else if(!strcmp(s,"SUM")) {
				int r1;
				int c1;
				int r2;
				int c2;
				scanf("%d %d %d %d",&r1,&c1,&r2,&c2);
				r1=min(r1,R);
				c1=min(c1,C);
				r2=min(r2,R);
				c2=min(c2,C);
				++r1;
				++c1;
				++r2;
				++c2;
				printf("%d\n", sum(r1,c1,r2,c2));
			} else
				break;
		}
		printf("\n");
	}
}
