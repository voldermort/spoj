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
#include <cassert>
#include <ctime>
#include <numeric>
#include <valarray>
#include <complex>
#include <memory.h>
#include <ctime>
using namespace std;

const int dr[]={0,-1,0,1,-1,1, 1,-1};
const int dc[]={1,0,-1,0, 1,1,-1,-1};
const double eps=1e-9;

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
typedef complex<double> pnt;
typedef vector<pnt> vpnt;
typedef vector<vector<pair<int, long long> > > Graph;

#define fr(i,a,b) for(int i(a),_b(b);i<=_b;++i)
#define frd(i,a,b) for(int i(a),_b(b);i>=_b;--i)
#define rep(i,n) for(int i(0),_n(n);i<_n;++i)
#define reps(i,a) fr(i,0,sz(a)-1)
#define fore(it,c) for(typeof((c).begin()) it=(c).begin();it!=(c).end();++it)
#define all(a) a.begin(),a.end()
#define pb push_back
#define mp make_pair
#define maximum(a) (*max_element(all(a)))
#define minimum(a) (*min_element(all(a)))
#define clr(u,a) memset(u,a,sizeof(u))
#define findx(a,u) (find(all(a),u)-a.begin())
#define two(X) (1LL<<(X))
#define contain(S,X) (((S)&two(X))!=0)

template<class T> void print(T const &x) {ostringstream os; os<<x; cout<<os.str()<<endl;}
template<class T> void print(vector<T> const &v) {ostringstream os; for(int i=0; i<v.size(); ++i){if(i)os<<' ';os<<v[i];} cout<<os.str()<<endl;}
template<class T> void print(vector<vector<T> > const &v){ostringstream os; for(int i=0;i<v.size();++i) {for(int j=0;j<v[i].size();++j){if(j)os<<' ';os<<v[i][j];}os<<endl;}cout<<os.str()<<endl;}
template<class T> void print(valarray<T> const &v) {ostringstream os; for(int i=0; i<v.size(); ++i){if(i)os<<' ';os<<v[i];} cout<<os.str()<<endl;}
template<class T> int sz(const T&c){return (int)c.size();}
template<class T> void srt(T&c){std::sort(c.begin(),c.end());}
template<class T> void checkmin(T &a,T b){if(b<a) a=b;}
template<class T> void checkmax(T &a,T b){if(b>a) a=b;}
template<class T> T sqr(T x){return x*x;}
template<class T, class U> T cast (U x) { ostringstream os; os<<x; T res; istringstream is(os.str()); is>>res; return res; }
template<class T> vector<T> split(string s, string x=" ") {vector<T> res; for(int i=0;i<s.size();i++){string a; while(i<(int)s.size()&&x.find(s[i])==string::npos)a+=s[i++]; if(!a.empty())res.push_back(cast<T>(a));} return res;}
template<class T> T inside(T r,T c,T R, T C){return r>=0 && r<R && c>=0 && c<C;}

char buf1[1<<21];
int pos1;

int nextInt() {
	while (buf1[pos1] <= ' ') ++pos1;
	int res = 0;
	while (buf1[pos1] > ' ') 
		res = res*10+(buf1[pos1++]&15);
	return res;
}


const int maxnodes = 100002;
const int maxedges = 700000;
const int inf = 2000000000;

int src, dest, edges;
int last[maxnodes], head[maxedges], prev[maxedges];
char flow[maxedges], cap[maxedges];
int dist[maxnodes], Q[maxnodes], work[maxnodes];
bool hasrev[maxedges];

void dinic_init() {
	memset(last, 255, sizeof(last));
	edges = 0;
}

void addedge(int u, int v, bool rev) {
	head[edges] = v;
	cap[edges] = 1;
	flow[edges] = 0;
	prev[edges] = last[u];
	last[u] = edges++;
	if (rev) {
		hasrev[edges] = hasrev[edges ^ 1] = true;
		head[edges] = u;
		cap[edges] = 0;
		flow[edges] = 0;
		prev[edges] = last[v];
		last[v] = edges++;		
	} else {
		hasrev[edges ^ 1] = false;
		edges++;
	}
}

bool dinic_bfs(int nodes) {
	memset(dist, 255, nodes * sizeof(int));
	dist[src] = 0;
	int sizeQ = 0;
	Q[sizeQ++] = src;
	for (int i = 0; i < sizeQ; i++) {
		int u = Q[i];
		for (int e = last[u]; e >= 0; e = prev[e]) {
			int v = head[e];
			if (flow[e] < cap[e] && dist[v] < 0) {
				dist[v] = dist[u] + 1;
				Q[sizeQ++] = v;
			}
		}
	}
	return dist[dest] >= 0;
}

bool dinic_dfs(int u) {
	if (u == dest)
		return true;
	for (int &e = work[u]; e >= 0; e = prev[e]) {
		int v = head[e];
		if (flow[e] < cap[e] && dist[v] == dist[u] + 1) {
			if (dinic_dfs(v)) {
				++flow[e];
				if(hasrev[e])
					--flow[e ^ 1];
				return true;
			}
		}
	}
	return false;
}

int maxFlow(int src, int dest, int nodes) {
	::src = src;
	::dest = dest;
	int result = 0;
	while (dinic_bfs(nodes)) {
		memcpy(work, last, nodes * sizeof(int));
		while (dinic_dfs(src))
			++result;
	}
	return result;
}

int main( int argc, char* argv[] ) {
	/*
	{
		freopen("input.txt","w",stdout);
		int n=50000;
		int m=50000;
		int p=150000;
		cout<<n<<" "<<m<<" "<<p<<endl;
		map<pii, bool> used;
		rep(i,p){
			int a,b;
			while(1){
				a=rand()%n;
				b=rand()%m;
				if(!used[mp(a,b)])break;
			}
			used[mp(a,b)]=true;
			cout<<a+1<<" "<<b+1<<endl;
		}
		exit(0);
	}
	*/
	
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	#endif	

	fread(buf1, 1, sizeof(buf1), stdin);
	
	//Scanner sc;
	int n = nextInt();
	int m = nextInt();
	int p = nextInt();

	dinic_init();
	int s=n+m;
	int t=n+m+1;

	rep(i,n) addedge(s, i, false);
	rep(i,p){
		int a = nextInt();
		int b = nextInt();
		addedge(a - 1, b - 1 + n, true);
	}
	rep(i,m) addedge(i + n, t, false);

	clock_t start=clock();	
	int res = maxFlow(s, t, n + m + 2);
	fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));

	printf("%d\n", res);

	return 0;
}
