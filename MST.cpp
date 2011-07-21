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
		bool sign = false;
		if(*curPos == '-') {
			sign = true;
			++curPos;
		}
		int res = 0;
		while (*curPos > ' ') 
			res = res * 10 + (*(curPos++) & 15);
		return sign ? -res : res;
	}

	int nextChar() {
		ensureCapacity();
		while (*curPos <= ' ') ++curPos;
		return *(curPos++);
	}
};

long long prim(Graph &g, vector<int> &pred) {
	int n = g.size();
	pred.assign(n, -1);
	vector<bool> vis(n);
	vector<int> prio(n, INT_MAX);
	prio[0] = 0;
	priority_queue<pii, vector<pii> , greater<pii> > q;
	q.push(make_pair(0, 0));
	long long res = 0;

	while (!q.empty()) {
		int d = q.top().first;
		int u = q.top().second;
		q.pop();
		if (vis[u])
			continue;
		vis[u] = true;
		res += d;
		for (int i = 0; i < (int) g[u].size(); i++) {
			int v = g[u][i].first;
			if (vis[v])
				continue;
			int nprio = g[u][i].second;
			if (prio[v] > nprio) {
				prio[v] = nprio;
				pred[v] = u;
				q.push(make_pair(nprio, v));
			}
		}
	}
	return res;
}

int main( int argc, char* argv[] ) {
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	#endif	
	
	Scanner sc;
	int n = sc.nextInt();
	int m = sc.nextInt();

	Graph g(n);

	rep(i,m){
		int a = sc.nextInt();
		int b = sc.nextInt();
		int c = sc.nextInt();
		--a,--b;
		g[a].pb(mp(b,c));
		g[b].pb(mp(a,c));
	}

	vi pred;
	cout<<prim(g, pred)<<endl;

	return 0;
}
