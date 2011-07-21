#include <algorithm>
#include <cstdio>
#include <memory.h>
#include <ctime>

char buf1[1<<20];
int pos1;

int nextInt() {
	while (buf1[pos1] <= ' ') ++pos1;
	int res = 0;
	while (buf1[pos1] > ' ') 
		res = res*10+(buf1[pos1++]&15);
	return res;
}

const int maxnodes = 5000;
const int maxedges = 60000;
const int inf = 2000000000;

short src, dest;
int edges;
short head[maxedges], dist[maxnodes], Q[maxnodes];
unsigned short last[maxnodes], prev[maxedges], work[maxnodes];
int flow[maxedges], cap[maxedges];

void dinic_init() {
	memset(last, 255, sizeof(last));
	edges = 0;
}

void addedge(int u, int v, int cap1, int cap2) {
	head[edges] = v;
	cap[edges] = cap1;
	flow[edges] = 0;
	prev[edges] = last[u];
	last[u] = edges++;
	head[edges] = u;
	cap[edges] = cap2;
	flow[edges] = 0;
	prev[edges] = last[v];
	last[v] = edges++;
}

bool dinic_bfs(int nodes) {
	memset(dist, 255, nodes * sizeof(short));
	dist[src] = 0;
	int sizeQ = 0;
	Q[sizeQ++] = src;
	for (int i = 0; i < sizeQ; i++) {
		short u = Q[i];
		for (unsigned short e = last[u]; e != 65535; e = prev[e]){
			short v = head[e];
			if (dist[v] < 0 && flow[e] < cap[e]) {
				dist[v] = dist[u] + 1;
				Q[sizeQ++] = v;
			}
		}
	}
	return dist[dest] >= 0;
}

int dinic_dfs(short u, int f) {
	if (u == dest)
		return f;
	for (unsigned short &e = work[u]; e != 65535; e = prev[e]) {
		short v = head[e];
		if (dist[v] == dist[u] + 1) {
			int nf = cap[e] - flow[e];
			if(nf){
				if(nf>f)nf=f;
				int df = dinic_dfs(v, nf);
				if (df > 0) {
					flow[e] += df;
					flow[e ^ 1] -= df;
					return df;
				}
			}
		}
	}
	return 0;
}

long long maxFlow(int src, int dest, int nodes) {
	::src = src;
	::dest = dest;
	long long result = 0;
	while (dinic_bfs(nodes)) {
		memcpy(work, last, nodes * sizeof(unsigned short));
		while (int delta = dinic_dfs(src, inf))
			result += delta;
	}
	return result;
}

int main( int argc, char* argv[] ) {
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	#endif	

	fread(buf1, 1, sizeof(buf1), stdin);
	
	int n = nextInt();
	int m = nextInt();

	dinic_init();

	for(int i=0; i<m; i++){
		int a = nextInt();
		int b = nextInt();
		int c = nextInt();
		if(a!=b) addedge(a-1, b-1, c, c);
	}

	//clock_t start=clock();
	long long res = maxFlow(0, n-1, n);
	//fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));

	printf("%lld\n", res);

	return 0;
}
