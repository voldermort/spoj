#include <cstdio>
#include <vector>
using namespace std;

#define maxn 10000
vector<int> g[maxn];
int bd, bu;

void dfs(int u, int p, int d) {
	if (bd < d) {
		bd = d;
		bu = u;
	}
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v!=p)dfs(v,u,d+1);
	}
}

char buf[1<<18];
int pos;

int nextInt() {
	while (buf[pos] <= ' ') ++pos;
	int res = 0;
	while (buf[pos] > ' ') 
		res = res*10+(buf[pos++]&15);
	return res;
}

int main() {
	//freopen("input.txt", "r", stdin);
	fread(buf, 1, sizeof(buf), stdin);
	int n = nextInt();
	for (int i=0;i<n-1;i++) {
		int u = nextInt();
		int v = nextInt();
		--u; --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	bd = -1;
	dfs(0, -1, 0);
	dfs(bu, -1, 0);
	printf("%d\n", bd);	
}