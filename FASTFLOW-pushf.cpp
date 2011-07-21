#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#include <boost/typeof/typeof.hpp>
#define typeof BOOST_TYPEOF
#endif
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

#include <list>
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n) FOR(i,0,n)
#define VAR(v,w) typeof(w) v=(w)
#define FORE(it,c) for(VAR(it,(c).begin());it!=(c).end();++it)
#define PB push_back
#define SIZE(c) ((int)(c).size())
typedef vector<int> VI;
typedef vector<string> VS;
template<class T>
class ARR2 {
	T *arr;
public:
	int n, m;
	ARR2(int n, int m) :
	n(n), m(m) {
		arr = new T[n * m];
	}
	ARR2(const ARR2<T>& a) :
	n(a.n), m(a.m) {
		arr = new T[n * m];
		REP(i,n * m)
			arr[i] = a.arr[i];
	}
	ARR2& operator=(ARR2& a) {
		if (&a != this)
			return *this;
		delete[] arr;
		n = a.n;
		m = a.m;
		arr = new T[n * m];
		REP(i,n * m)
			arr[i] = a.arr[i];
		return *this;
	}
	~ARR2() {
		delete[] arr;
	}
	T *operator[](int i) {
		return arr + i * m;
	}
};
template<class T>
class FLOW {
public:
	int n;
	ARR2<T> c, f;
	VI h, current;
	vector<T> e;
	FLOW(int n) :
	n(n), c(n, n), f(n, n), current(n) {
		REP(u,n)
			REP(v,n)
			c[u][v] = 0;
	}
	void edge(int u, int v, T w) {
		c[u][v] += w;
	}
	void initializePreflow(int s) {
		h = VI(n);
		e = vector<T> (n);
		REP(u,n)
			REP(v,n)
			f[u][v] = 0;
		h[s] = n;
		REP(u,n)
			f[u][s] = -(f[s][u] = e[u] = c[s][u]);
	}
	void push(int u, int v) {
		T d = min(e[u], (c[u][v] - f[u][v]));
		f[v][u] = -(f[u][v] += d);
		e[u] -= d;
		e[v] += d;
	}
	void lift(int u) {
		bool mod = 0;
		REP(v,n)
			if (f[u][v] < c[u][v] && (!mod || h[v] + 1 < h[u])) {
				h[u] = h[v] + 1;
				mod = 1;
			}
	}
	void discharge(int u) {
		while (e[u] > 0) {
			int v = current[u];
			if (v == n) {
				lift(u);
				current[u] = 0;
			} else if (f[u][v] < c[u][v] && h[u] == h[v] + 1)
				push(u, v);
			else
				current[u]++;
		}
	}
	T go(int s, int t) {
		initializePreflow(s);
		list<int> l;
		REP(u,n)
			if (u != s && u != t) {
				l.PB(u);
				current[u] = 0;
			}
			FORE(u,l) {
				int oldHeight = h[*u];
				discharge(*u);
				if (h[*u] > oldHeight) {
					l.push_front(*u);
					l.erase(u);
					u = l.begin();
				}
			}
			return e[t];
	}
};

int main( int argc, char* argv[] ) {
	ios::sync_with_stdio(false);
	//freopen("input.txt","r",stdin);

	
	int n,m;
	scanf("%d%d", &n,&m);

	FLOW<ll> flow(n);

	rep(i,m){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		flow.edge(a-1, b-1, c);
		flow.edge(b-1, a-1, c);
	}

	ll res = flow.go(0, n-1);

	printf("%lld\n", res);

	return 0;
}
