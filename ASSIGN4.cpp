#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <climits>
#include <numeric>
#include <memory.h>
//#include <ctime>
//clock_t start=clock();
//fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<string> vs;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef pair<double, double> pdd;
typedef vector<pdd> vpdd;
typedef vector<vpii> Graph;

#define fr(i,a,b) for(int i(a),_b(b);i<=_b;++i)
#define frd(i,a,b) for(int i(a),_b(b);i>=_b;--i)
#define rep(i,n) for(int i(0),_n(n);i<_n;++i)
#define reps(i,a) fr(i,0,sz(a)-1)
#define all(a) a.begin(),a.end()
#define pb push_back
#define mp make_pair
#define clr(x,a) memset(x,a,sizeof(x))
#define findx(a,x) (find(all(a),x)-a.begin())
#define two(X) (1LL<<(X))
#define contain(S,X) (((S)&two(X))!=0)

const int dr[]={0,-1,0,1,-1,1, 1,-1};
const int dc[]={1,0,-1,0, 1,1,-1,-1};
const double eps=1e-9;

template<class T> void print(vector<T> const &v) {ostringstream os; for(int i=0; i<(int)v.size(); ++i){if(i)os<<' ';os<<v[i];} cout<<os.str()<<endl;}
template<class T> int sz(const T&c){return (int)c.size();}
template<class T> void srt(T&c){std::sort(c.begin(),c.end());}
template<class T> void checkmin(T &a,T b){if(b<a) a=b;}
template<class T> void checkmax(T &a,T b){if(b>a) a=b;}
template<class T> T sqr(T x){return x*x;}
template<class T, class U> T cast (U x) { ostringstream os; os<<x; T res; istringstream is(os.str()); is>>res; return res; }
template<class T> vector<T> split(string s, string x=" ") {vector<T> res; for(int i=0;i<s.size();i++){string a; while(i<(int)s.size()&&x.find(s[i])==string::npos)a+=s[i++]; if(!a.empty())res.push_back(cast<T>(a));} return res;}
template<class T> bool inside(T r,T c,T R, T C){return r>=0 && r<R && c>=0 && c<C;}

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

const int maxnodes = 200000;
const int maxedges = 1000000;

int edges, nodes;
int last[maxnodes], head[maxedges], previous[maxedges];
int flow[maxedges], cap[maxedges], cost[maxedges];
int prio[maxnodes], curflow[maxnodes], edge[maxnodes], vstate[maxnodes], q[maxnodes];

void graphClear(int _nodes) {
	fill(last, last + maxnodes, -1);
	edges = 0;
	nodes = _nodes;
}

void addEdge1(int u, int v, int _cap, int _cost) {
	head[edges] = v;
	cap[edges] = _cap;
	cost[edges] = _cost;
	flow[edges] = 0;
	previous[edges] = last[u];
	last[u] = edges++;
}

void addEdge(int u, int v, int cap, int cost) {
	addEdge1(u, v, cap, cost);
	addEdge1(v, u, 0, -cost);
}

pii maxFlowOfMinCost(int s, int t) {
	int f = 0;
	int flowCost = 0;
	while (true) {
		curflow[s] = INT_MAX;
		fill(vstate, vstate + nodes, 2);
		fill(prio, prio + nodes, INT_MAX);
		prio[s] = 0;
		int qh = 0;
		int qt = 0;
		q[qt++] = s;
		if (qt == nodes)
			qt = 0;
		while (qh != qt) {
			int u = q[qh++];
			if (qh == nodes)
				qh = 0;
			vstate[u] = 0;
			for (int e = last[u]; e >= 0; e = previous[e]) {
				int v = head[e];
				int nprio = prio[u] + cost[e];
				if (cap[e] > flow[e] && prio[v] > nprio) {
					prio[v] = nprio;
					edge[v] = e;
					curflow[v] = min(curflow[u], cap[e] - flow[e]);

					if (vstate[v] == 2) {
						q[qt++] = v;
						if (qt == nodes)
							qt = 0;
					} else if (vstate[v] == 0) {
						if (--qh == -1)
							qh = nodes - 1;
						q[qh] = v;
					}
					vstate[v] = 1;
				}
			}
		}
		if (prio[t] == INT_MAX)
			break;
		int df = curflow[t];
		f += df;
		flowCost += df * prio[t];
		for (int v = t; v != s; v = head[edge[v] ^ 1]) {
			flow[edge[v]] += df;
			flow[edge[v] ^ 1] -= df;
		}
	}
	return make_pair(f, flowCost);
}


int main( int argc, char* argv[] ) {
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	#endif	

	Scanner sc;
		
	int tc = sc.nextInt();
	while(tc--){
		int m = sc.nextInt();
		int n = sc.nextInt();
		int s=n+m;
		int t=n+m+1;
		graphClear(n+m+2);
		rep(i,m) {
			int a=sc.nextInt();
			addEdge(s, i, a, 0);
		}
		rep(j,n) {
			int b=sc.nextInt();
			addEdge(m+j, t, b, 0);
		}
		rep(i,m){
			rep(j,n){
				int c=sc.nextInt();
				addEdge(i, m+j, 60000, c);
			}
		}

		pii res=maxFlowOfMinCost(s,t);

		printf("%d\n", res.second);
	}

	return 0;
}
