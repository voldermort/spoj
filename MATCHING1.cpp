#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int BUF_SIZE = 65536;
char input[BUF_SIZE];

struct Scanner {
	char* curPos;

	Scanner() {
		fread(input, 1, sizeof(input), stdin);
		curPos = input;
	}

	void ensureCapacity(){
		int size = input + BUF_SIZE - curPos;
		if (size < 100) {
			memcpy(input, curPos, size);
			fread(input + size, 1, BUF_SIZE - size, stdin);
			curPos = input;
		}
	}

	int nextInt() {
		ensureCapacity();
		while (*curPos <= ' ') ++curPos;
		int res = 0;
		while (*curPos > ' ') 
			res = res * 10 + (*(curPos++) & 15);
		return res;
	}
};

#define MAX_V1 50000
#define MAX_V2 50000
#define MAX_E 150000

int V1,V2,l[MAX_V1],r[MAX_V2];
int E,to[MAX_E],next[MAX_E],last[MAX_V1];
bool visited[MAX_V1];

void init(){
	memset(last,-1,sizeof(int)*V1);
	E = 0;
}

void add_edge(int u, int v){
	to[E] = v, next[E] = last[u]; last[u] = E; ++E;
}

bool pairup(int u){
	if (visited[u])  return false;
	visited[u] = true;

	for(int e = last[u];e!=-1;e = next[e]){
		int v = to[e];

		if(r[v]==-1 || pairup(r[v])){
			l[u] = v;
			r[v] = u;
			return true;
		}
	}

	return false;
}

int hopcroft_karp(){
	bool change = true;
	memset(l,-1,sizeof(int)*V1);
	memset(r,-1,sizeof(int)*V2);

	while(change){
		change = false;
		memset(visited,false,sizeof(bool)*V1);

		for(int i = 0;i<V1;++i)
			if(l[i]==-1) change |= pairup(i);
	}

	int ret = 0;

	for(int i = 0;i<V1;++i)
		if(l[i]!=-1) ++ret;

	return ret;
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	#endif	

	Scanner sc;

	V1 = sc.nextInt();
	V2 = sc.nextInt();
	int e = sc.nextInt(),u,v;

	init();

	while(e--){
		u = sc.nextInt();
		v = sc.nextInt();
		--u; --v;
		add_edge(u,v);
	}

	printf("%d\n",hopcroft_karp());

	return 0;
}