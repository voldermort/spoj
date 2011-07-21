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
#include <ctime>
clock_t start=clock();

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

const int maxh = 17;
const int maxn = 1 << maxh;

char s[10][maxn];
int n1;

const int K = 26;
struct state {
	int pos, length, link, v, w;
	int next[K];
};
state st[maxn*2-1];
int cnt, last;
pii a[maxn*2-1];
int b[maxn*2-1];

void init() {
	st[0].link = -1;
	st[0].pos = -1;
	st[0].w = INT_MAX;
	memset (st[0].next, -1, sizeof st[0].next);
	++cnt;
}

void sa_extend (int position, char c) {
	int nlast = cnt++;
	st[nlast].length = st[last].length + 1;
	st[nlast].pos = position;
	st[nlast].w = INT_MAX;
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
			st[cnt].pos = -1;
			st[cnt].w = INT_MAX;
			for (; p!=-1 && st[p].next[c]==q; p=st[p].link)
				st[p].next[c] = cnt;
			st[q].link = st[nlast].link = cnt;
			++cnt;
		}
	}
	last = nlast;
}

void build_dfa(char *s, int n){
	init();
	for (size_t i=0; i<n; ++i) {
		sa_extend (i, s[i]-'a');
	}
}

void lcs (char* b, int n2) {	
	int p = 0,  len = 0;
	for (size_t i=0; i<n2; ++i) {
		char cur = b[i]-'a';
		if (st[p].next[cur] == -1) {
			for (; p!=-1 && st[p].next[cur] == -1; p=st[p].link);
			if (p == -1) {
				p = len = 0;
				continue;
			}
			len = st[p].length;
		}	
		++len;			
		p = st[p].next[cur];
		checkmax(st[p].v, len);
	}
	rep(i,cnt){
		if(::b[i]==0)continue;
		checkmax(st[st[::b[i]].link].v, st[::b[i]].v);
	}
	rep(i,cnt)checkmin(st[i].w, st[i].v), st[i].v=0;
}

int main( int argc, char* argv[] ) {
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	#endif	

	int n=0;
	vi len;
	while(!feof(stdin)){
		gets(s[n]);
		int L=strlen(s[n]);
		if(L){
			len.pb(L);
			++n;
		}
	}

	int m=min_element(all(len))-len.begin();

	build_dfa(s[m], len[m]);
	n1 = len[m];

	rep(i,cnt) a[i]=mp(st[i].length,i);
	sort(a, a + cnt, greater<pii>());
	rep(i,cnt) b[i] = a[i].second;

	rep(i,n)if(i!=m){
		lcs(s[i],len[i]);
	}
	fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));

	int res = 0;
	rep(i,cnt) checkmax(res, min(st[i].length, st[i].w));
	printf("%d\n", res);
	return 0;
}
