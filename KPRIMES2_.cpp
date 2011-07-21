#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#include <boost/typeof/typeof.hpp>
#define __typeof BOOST_TYPEOF
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
#include <climits>
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
#define fore(it,c) for(__typeof((c).begin()) it=(c).begin();it!=(c).end();++it)
#define all(a) a.begin(),a.end()
#define pb push_back
#define mp make_pair
#define maximum(a) (*max_element(all(a)))
#define minimum(a) (*min_element(all(a)))
#define clr(x,a) memset(x,a,sizeof(x))
#define findx(a,x) (find(all(a),x)-a.begin())
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
template<class T> bool inside(T r,T c,T R, T C){return r>=0 && r<R && c>=0 && c<C;}

clock_t start=clock();

char buf1[1<<22];
int pos1;

int nextInt() {
	while (buf1[pos1] <= ' ') ++pos1;
	int res = 0;
	while (buf1[pos1] > ' ') 
		res = res*10+(buf1[pos1++]&15);
	return res;
}

char buf2[1<<22];
int pos2;

void writeInt(int x) {
	char d[10];
	int c=0;
	while(true){		
		d[c++] = x%10 + '0';
		x/=10;
		if(x==0)break;
	}
	while(--c>=0)buf2[pos2++]=d[c];
}

void writeChar(char x) {
	buf2[pos2++]=x;
}


const int MAXN = 982451653;
const int SQRT_MAXN = 32768;
const int S = 55000;
char nprime[SQRT_MAXN], bl[S];
int primes[SQRT_MAXN], cnt;

int main( int argc, char* argv[] ) {
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	#endif	

	fread(buf1, 1, sizeof(buf1), stdin);

	/*
	freopen("input.txt","w",stdout);
	cout<<100000<<endl;
	fr(i,50000000-100000+1,50000000){
		cout<<i<<endl;
	}
	exit(0);
	*/

	//Scanner sc;

	int t=nextInt();
	vpii q(t);
	rep(i,t){
		int a = nextInt();
		q[i] = mp(a, i);
	}
	srt(q);
	vi res(t);

	int nsqrt = (int) sqrt (MAXN + .0);
	for (int i=2; i<=nsqrt; ++i)
		if (!nprime[i]) {
			primes[cnt++] = i;
			for (int j=i+i; j<=nsqrt; j+=i)
				nprime[j] = 1;
		}

	int cur = q[0].first;
	int pos = 0;
	int cnt2 = 0;
	for (int k=0, maxk=MAXN/S; k<=maxk; ++k) {
		memset (bl, 0, sizeof bl);
		int start = k * S;
		for (int i=0; i<cnt; ++i){
			for (int j = max((start+primes[i]-1)/primes[i],2) * primes[i] - start; j<S; j+=primes[i])
				bl[j] = 1;
		}
		if (k == 0)
			bl[0] = bl[1] = 1;
		int b = min(S, MAXN-start+1);
		for (int i=0; i<b; ++i)
			if (!bl[i])
				if(++cnt2 == cur){
					res[q[pos].second] = i+start;
					++pos;
					if(pos == t) goto m1;
					cur = q[pos].first;
				}
	}

	m1:;

	rep(i,t) {
		//printf("%d\n", res[i]);
		writeInt(res[i]);
		writeChar('\n');
	}

	fwrite(buf2, 1, pos2, stdout);

	fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));

	return 0;
}
