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


const int maxnodes = 200000;
const int maxedges = 1000000;

int edges, n;
int last[maxnodes], head[maxedges], previous[maxedges], len[maxedges];
int prio[maxnodes], pred[maxnodes], id[maxnodes], q[maxnodes];

void graphClear() {
	fill(last, last + maxnodes, -1);
	edges = 0;
}

void addEdge(int u, int v, int length) {
	head[edges] = v;
	len[edges] = length;
	previous[edges] = last[u];
	last[u] = edges++;
}



void dijkstra(Graph &g, int s, vector<int> &prio, vector<int> &pred) {
	int n = g.size();
	prio.assign(n, INT_MAX);
	prio[s] = 0;
	pred.assign(n, -1);
	priority_queue<pii, vector<pii> , greater<pii> > q;
	q.push(make_pair(prio[s], s));

	while (!q.empty()) {
		int d = q.top().first;
		int u = q.top().second;
		q.pop();
		if (d != prio[u])
			continue;
		for (int i = 0; i < (int) g[u].size(); i++) {
			int v = g[u][i].first;
			int nprio = prio[u] + g[u][i].second;
			if (prio[v] > nprio) {
				prio[v] = nprio;
				pred[v] = u;
				q.push(make_pair(nprio, v));
			}
		}
	}
}

void dijkstra2(Graph &g, int s, vector<int> &prio, vector<int> &pred) {
	int n = g.size();
	prio.assign(n, INT_MAX);
	prio[s] = 0;
	pred.assign(n, -1);
	set<pii> q;
	q.insert(make_pair(prio[s], s));

	while (!q.empty()) {
		int u = q.begin()->second;
		q.erase(q.begin());
		for (int i = 0; i < (int) g[u].size(); ++i) {
			int v = g[u][i].first;
			int nprio = prio[u] + g[u][i].second;
			if (prio[v] > nprio) {
				q.erase(make_pair(prio[v], v));
				prio[v] = nprio;
				pred[v] = u;
				q.insert(make_pair(prio[v], v));
			}
		}
	}
}

int main() {
	srand(2);
	int n=1000;
	Graph g(n);
	set<pii> edges;

	int m=100000;

	while(sz(edges)<m){
		int	a=rand()%n;
		int	b=rand()%n;
		pii p(a,b);
		if(edges.count(p))continue;
		edges.insert(p);
		int cost = rand();
		g[a].pb(mp(b,cost));
	}

	vector<int> prio;
	vector<int> pred;

	fprintf(stderr, "starting...\n");

	clock_t start=clock();
	rep(i,n)
	dijkstra(g, i, prio, pred);
	fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));

}
