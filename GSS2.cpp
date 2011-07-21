#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef vector<ll> vl;
#define rep(i,n) for(int i(0),_n(n);i<_n;++i)
template<class T> void checkmax(T &a,T b){if(b>a) a=b;}

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

const int MAXT = 1<<17;
ll mx[2*MAXT], add[2*MAXT];
int len;

const int MAXN = 100000;
const int MAXQ = 100000;
item items[MAXN + MAXQ];
int last[200001];

void buildTree(int node, int left, int right) {
	if (left == right) return;
	int mid = (left + right) >> 1;
	buildTree(node * 2, left, mid);
	buildTree(node * 2 + 1, mid + 1, right);
	mx[node] = max(mx[node * 2], mx[node * 2 + 1]);
}

int getMax(int node, int left, int right, int a, int b, ll sumAdd) {
	sumAdd += add[node];
	if (a == left && b == right) {
		return mx[node] + sumAdd;
	}
	ll res = LLONG_MIN;
	int mid = (left + right) >> 1;
	if (a <= mid) {
		checkmax(res,  getMax(node * 2, left, mid, a, min(b, mid), sumAdd));
	}
	if (mid + 1 <= b) {
		checkmax(res,  getMax(node * 2 + 1, mid + 1, right, max(a, mid + 1), b, sumAdd));
	}
	return res;
}

int getMax(int a, int b) {
	return getMax(1, 0, len - 1, a, b, 0);
}

void add(int node, int left, int right, int a, int b, int value) {
	if (a == left && b == right) {
		add[node] += value;
	} else {
		int mid = (left + right) >> 1;
		int n0 = node * 2;
		int n1 = node * 2 + 1;
		if (a <= mid) {
			add(n0, left, mid, a, min(b, mid));
		}
		if (mid + 1 <= b) {
			add(n1, mid + 1, right, max(a, mid + 1), b);
		}
		mx[node] = max(mx[n0] + add[n0], mx[n1] + add[n1]);
	}
}

void add(int a, int b, int value) {
	add(1, 0, len - 1, a, b, value);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	#endif	

	int n;
	scanf("%d", &n);

	len = 1;
	while (len < n) len += len;
	buildTree(1, 0, len - 1);

	for(int i=0;i<n;i++) {
		scanf("%d", &items[i].v);
		items[i].j = i + 1;
	}

	int q;
	scanf("%d", &q);

	for(int i=n;i<n+q;i++) {
		scanf("%d%d", &items[i].i, &items[i].j);
		items[i].pos = i-n;
		items[i].type = 1;
	}

	int m=n+q;
	sort(items, items+m);

	vl res(q);
	fill(last, last+200001, -1);

	for(int i=0;i<m;i++){
		if(items[i].type == 0) {
			int v = items[i].v;
			add(last[v] + 1, items[i].j, v);
			last[v] = i;
		} else
			res[items[i].pos] = max(0, mx(items[i].i, items[i].j));
	}

	rep(i,q)printf("%ld\n", res[i]);
}
