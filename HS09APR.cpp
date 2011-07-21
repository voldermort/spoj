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

vd gauss(vvd a, vd b) {
	int n = b.size();
	vd res = b;
	for (int i = 0; i < n; i++) {
		int k = i;
		for (int j = i + 1; j < n; j++) {
			if (abs(a[j][i]) > abs(a[k][i])) {
				k = j;
			}
		}
		swap(a[i], a[k]);
		swap(res[i], res[k]);
		for (int j = i + 1; j < n; j++) {
			a[i][j] /= a[i][i];
		}
		res[i] /= a[i][i];
		for (int j = 0; j < n; j++) {
			if (j != i && a[j][i] != 0) {
				for (int p = i + 1; p < n; p++) {
					a[j][p] -= a[i][p] * a[j][i];
				}
				res[j] -= res[i] * a[j][i];
			}
		}
	}
	return res;
}

int main( int argc, char* argv[] ) {
	ios::sync_with_stdio(false);
	//freopen("input.txt","r",stdin);

	int n;
	scanf("%d",&n);

	vd x(n),y(n);

	rep(i,n)scanf("%lf%lf",&x[i],&y[i]);
	
	vd p(7);
	p[0]=n;
	rep(i,n){
		double v=1;
		rep(j,6){
			v*=x[i];
			p[j+1]+=v;			
		}
	}

	vvd a(4,vd(4));

	a[0][0]=p[6]; a[0][1]=p[5]; a[0][2]=p[4]; a[0][3]=p[3];
	a[1][0]=p[5]; a[1][1]=p[4]; a[1][2]=p[3]; a[1][3]=p[2];
	a[2][0]=p[4]; a[2][1]=p[3]; a[2][2]=p[2]; a[2][3]=p[1];
	a[3][0]=p[3]; a[3][1]=p[2]; a[3][2]=p[1]; a[3][3]=p[0];

	vd b(4);
	rep(i,n){
		double v=1;
		b[3]+=y[i]*v; v*=x[i];
		b[2]+=y[i]*v; v*=x[i];
		b[1]+=y[i]*v; v*=x[i];
		b[0]+=y[i]*v; 
	}

	b = gauss(a, b);
	
	printf("%.2f %.2f %.2f %.2f\n", b[0], b[1], b[2], b[3]);

	return 0;
}
