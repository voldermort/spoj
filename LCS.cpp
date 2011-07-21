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
#include <stack>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <cassert>
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
#define allen(a) a.begin(),a.end()
#define pb push_back
#define mp make_pair
#define maximum(a) (*max_element(allen(a)))
#define minimum(a) (*min_element(allen(a)))
#define clr(x,a) memset(x,a,sizeof(x))
#define findx(a,x) (find(allen(a),x)-a.begin())
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

const int maxh = 18;
const int maxn = 1 << maxh;

char s1[maxn];
char s2[maxn];

const int K = 26;
struct state {
	int length, link;
	int next[K];
};
state st[maxn*2-1];
int cnt, last;

void init() {
	st[0].link = -1;
	memset (st[0].next, -1, sizeof st[0].next);
	++cnt;
}

void sa_extend (char c) {
	int nlast = cnt++;
	st[nlast].length = st[last].length + 1;
	memset (st[nlast].next, -1, sizeof st[0].next);
	int p;
	for (p=last; p!=-1 && st[p].next[c]==-1; p=st[p].link)
		st[p].next[c] = nlast;
	if (p == -1)
		st[nlast].link = 0;
	else {
		int q = st[p].next[c];
		if (st[p].length + 1 == st[q].length)
			st[nlast].link = q;
		else {
			st[cnt].length = st[p].length + 1;
			memcpy (st[cnt].next, st[q].next, sizeof st[0].next);
			st[cnt].link = st[q].link;
			for (; p!=-1 && st[p].next[c]==q; p=st[p].link)
				st[p].next[c] = cnt;
			st[q].link = st[nlast].link = cnt;
			++cnt;
		}
	}
	last = nlast;
}

int lcs (char* a, char* b, int n1, int n2) {
	init();
	for (size_t i=0; i<n1; ++i) {
		sa_extend (a[i]-'a');
	}
	int p = 0,  len = 0,  best = 0;
	for (size_t i=0; i<n2; ++i) {
		char cur = b[i]-'a';
		if (st[p].next[cur] == -1) {
			for (; p!=-1 && st[p].next[cur] == -1; p=st[p].link) ;
			if (p == -1) {
				p = len = 0;
				continue;
			}
			len = st[p].length;
		}
		p = st[p].next[cur];
		if (++len > best){
			best = len;
		}
	}
	return best;
}

int main( int argc, char* argv[] ) {
	ios::sync_with_stdio(false);
	//freopen("input.txt","r",stdin);
	
	gets(s1);
	gets(s2);
	int n1=strlen(s1);
	int n2=strlen(s2);
	
	//int t1=clock();
	int res;
	if(n1<n2) res = lcs(s1, s2, n1, n2);
	else res = lcs(s2, s1, n2, n1);
	//cout<<clock()-t1<<endl;

	printf("%d\n", res);
	return 0;
}
