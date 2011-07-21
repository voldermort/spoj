#include <cstdio>
#include <algorithm>
using namespace std;

struct item {
	int v;
	int type;
	int pos;
	int i, j;

	bool operator<(const item &o) const {
		if(v!=o.v)return v>o.v;
		return type>o.type;
	}
};

#define MAXN 30000
#define MAXQ 200000

item items[MAXN+MAXQ];
int res[MAXQ];
int t[MAXN];
int n;

void inc(int i) {
	for (; i < n; i += (i + 1) & -(i + 1))
		++t[i];
}

int sum(int i) {
	int res = 0;
	for (; i >= 0; i -= (i + 1) & -(i + 1))
		res += t[i];
	return res;
}

int sum(int a, int b) {
	return sum(b) - sum(a - 1);
}


int main() {
	//freopen("input.txt","r",stdin);

	scanf("%d", &n);

	for(int i=0;i<n;i++) {
		scanf("%d", &items[i].v);
		items[i].pos = i;
	}

	int q;
	scanf("%d", &q);

	for(int i=n;i<n+q;i++) {
		scanf("%d%d%d", &items[i].i, &items[i].j, &items[i].v);
		items[i].pos = i-n;
		items[i].type = 1;
	}

	int m=n+q;
	sort(items, items+m);

	for(int i=0;i<m;i++){
		if(items[i].type == 0){
			inc(items[i].pos);
		} else {
			res[items[i].pos] = sum(items[i].i - 1, items[i].j - 1);
		}
	}

	for(int i=0;i<q;i++) printf("%d\n", res[i]);
}
