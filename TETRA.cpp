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
template<class T> T inside(T r,T c,T R, T C){return r>=0 && r<R && c>=0 && c<C;}

double det(vector<vector<double> > a){
	const double EPS=1e-5;
	int n = a.size();
	double res = 1;
	for (int i=0; i<n; ++i) {
		int k = i;
		for (int j=i+1; j<n; ++j)
			if (abs (a[j][i]) > abs (a[k][i])) {
				k = j;
			}
		if (abs (a[k][i]) < EPS) {
			res = 0;
			break;
		}
		swap (a[i], a[k]);
		if (i != k)
			res = -res;
		res *= a[i][i];
		for (int j=i+1; j<n; ++j)
			a[i][j] /= a[i][i];
		for (int j=0; j<n; ++j)
			if (j != i && abs (a[j][i]) > EPS)
				for (int k=i+1; k<n; ++k)
					a[j][k] -= a[i][k] * a[j][i];
	}
	return res;
}

double square(double a, double b, double c) {
	return sqrt((a + b + c) * (-a + b + c) * (a - b + c) * (a + b - c)) / 4;
}

double volume(double d12, double d13, double d14, double d23, double d24, double d34) {
	vvd a(5,vd(5));
	a[0][1]=a[0][2]=a[0][3]=a[0][4]=1;
	a[1][2]=sqr(d12); a[1][3]=sqr(d13); a[1][4]=sqr(d14);
	a[2][3]=sqr(d23); a[2][4]=sqr(d24); 
	a[3][4]=sqr(d34);

	rep(i,5)rep(j,i)a[i][j]=a[j][i];
	return sqrt(det(a)/288);
}

int main( int argc, char* argv[] ) {
	ios::sync_with_stdio(false);
	//freopen("input.txt","r",stdin);
	
	int testCases;
	scanf("%d", &testCases);
	for(int testCase=1;testCase<=testCases;testCase++){
		int WX, WY, WZ, XY, XZ, YZ;
		scanf("%d%d%d%d%d%d", &WX, &WY, &WZ, &XY, &XZ, &YZ);

		double s = square(WX,WY,XY) + square(WX,XZ,WZ) + square(WY,YZ,WZ) + square(XY,XZ,YZ);
		double r = volume(WX,WY,WZ,XY,XZ,YZ) * 3 / s;

		printf("%.4f\n", r);
	}

	return 0;
}
