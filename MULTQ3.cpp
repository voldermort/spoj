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

	int nextChar() {
		ensureCapacity();
		while (*curPos <= ' ') ++curPos;
		return *(curPos++);
	}
};

const int MAXN = 1<<17;
int t[3][2*MAXN], add[2*MAXN];

void buildTree(int node, int left, int right) {
	t[0][node] = right - left + 1;
	if (left == right) return;
	int mid = (left + right) >> 1;
	buildTree(node * 2, left, mid);
	buildTree(node * 2 + 1, mid + 1, right);
}

void init() {
	buildTree(1, 0, MAXN - 1);
}

int sum(int node, int left, int right, int a, int b, int sumAdd) {
	sumAdd += add[node];
	sumAdd %= 3;
	if (a == left && b == right) {
		return t[(3-sumAdd)%3][node];
	}
	int res = 0;
	int mid = (left + right) >> 1;
	if (a <= mid) {
		res += sum(node * 2, left, mid, a, min(b, mid), sumAdd);
	}
	if (mid + 1 <= b) {
		res += sum(node * 2 + 1, mid + 1, right, max(a, mid + 1), b, sumAdd);
	}
	return res;
}

int sum(int a, int b) {
	return sum(1, 0, MAXN - 1, a, b, 0);
}

void inc(int node, int left, int right, int a, int b) {
	if (a == left && b == right) {
		++add[node];
		add[node]%=3;
	} else {
		int mid = (left + right) >> 1;
		int n0 = node * 2;
		int n1 = node * 2 + 1;
		if (a <= mid) {
			inc(n0, left, mid, a, min(b, mid));
		}
		if (mid + 1 <= b) {
			inc(n1, mid + 1, right, max(a, mid + 1), b);
		}
		rep(i,3) t[i][node] = t[(3+i-add[n0])%3][n0] + t[(3+i-add[n1])%3][n1];
	}
}

void inc(int a, int b) {
	inc(1, 0, MAXN - 1, a, b);
}


int main( int argc, char* argv[] ) {
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif	

	init();

	Scanner sc;
	int n=sc.nextInt();
	int q=sc.nextInt();

	rep(i,q){
		int t=sc.nextInt();
		int a=sc.nextInt();
		int b=sc.nextInt();

		if(t==0){
			inc(a,b);
		} else {
			printf("%d\n", sum(a,b));
		}
	}

	return 0;
}
