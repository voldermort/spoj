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

//clock_t start=clock();

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

const int MAXN = 86028121;
const int SQRT_MAXN = 16384;
const int S2 = 20000;
const int S = S2/2;
char nprime[SQRT_MAXN], bl[S];
int primes[SQRT_MAXN], cnt;

int main( int argc, char* argv[] ) {
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	#endif	

	/*
	freopen("input.txt","w",stdout);
	cout<<50000<<endl;
	fr(i,5000000-50000+1,5000000){
		cout<<i<<endl;
	}
	exit(0);
	*/

	Scanner sc;

	int t=sc.nextInt();
	vpii q(t);
	rep(i,t){
		int a = sc.nextInt();
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
	for (int k=0, maxk=MAXN/S2; k<=maxk; ++k) {
		memset (bl, 0, sizeof bl);
		int start = k * S2;
		for (int i=1; i<cnt; ++i){
			int from = max((start+primes[i]-1)/primes[i],3) * primes[i] - start;
			if((from&1) == 0) from += primes[i];
			from >>= 1;
			for (int j = from; j < S; j += primes[i])
				bl[j] = 1;
		}
		if (k == 0) {
			bl[0] = 1;
			if(++cnt2 == cur){
				while(1){
					res[q[pos].second] = 2;
					if(++pos == t) goto m1;
					cur = q[pos].first;
					if(cur!=cnt2)break;
				}
			}
		}

		int b = min(S, (MAXN-start+1)>>1);
		for (int i=0; i<b; i++)
			if (!bl[i])
				if(++cnt2 == cur){
					while(1){
						res[q[pos].second] = (i<<1)+start+1;
						if(++pos == t) goto m1;
						cur = q[pos].first;
						if(cur!=cnt2)break;
					}
				}
	}

	m1:;

	rep(i,t) printf("%d\n", res[i]);

	return 0;
}
