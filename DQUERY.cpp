#include <cstdio>
#include <algorithm>
using namespace std;

struct item {
	int v;
	int type;
	int pos;
	int i, j;

	bool operator<(const item &o) const {
		if(j!=o.j)return j<o.j;
		return type<o.type;
	}
};

#define MAXN 30001
#define MAXQ 200000

item items[MAXN+MAXQ];
int res[MAXQ];
int t[MAXN];
int position[1000001];
int n;

void inc(int i) {
	for (; i <= n; i += i & -i)
		++t[i];
}

void dec(int i) {
	for (; i <= n; i += i & -i)
		--t[i];
}

int sum(int a, int b) {
	int res = 0;
	for (; b > 0; b -= b & -b) res += t[b];
	for (--a; a > 0; a -= a & -a) res -= t[a];
	return res;
}


int main() {
	//freopen("input.txt","r",stdin);

	scanf("%d", &n);

	for(int i=0;i<n;i++) {
		scanf("%d", &items[i].v);
		items[i].j = i + 1;
	}

	int q;
	scanf("%d", &q);

	for(int i=n;i<n+q;i++) {
		scanf("%d%d", &items[i].i, &items[i].j);
		items[i].pos = i - n;
		items[i].type = 1;
	}

	int m = n + q;
	sort(items, items+m);

	for(int i=0;i<m;i++){
		if(items[i].type == 0){
			int v = items[i].v;
			if(position[v] != 0) dec(position[v]);

			position[v] = items[i].j;
			inc(position[v]);
		}
		else
			res[items[i].pos] = sum(items[i].i, items[i].j);
	}

	for(int i=0;i<q;i++) printf("%d\n", res[i]);
}
