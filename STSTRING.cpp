#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#include <boost/typeof/typeof.hpp>
#define typeof BOOST_TYPEOF
#endif
#include <algorithm>
#include <iostream>
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
#include <numeric>
#include <valarray>
#include <complex>
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
#define repd(i,n) for(int i((n)-1);i>=0;--i)
#define reps(i,a) fr(i,0,sz(a)-1)
#define all(a) a.begin(),a.end()
#define pb push_back
#define mp make_pair
#define fore(it,c) for(typeof((c).begin()) it=(c).begin();it!=(c).end();++it)
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

int main( int argc, char* argv[] ) {
	//freopen("input.txt","r",stdin);

	int x[10],y[10];
	string a,b;
	
	while(cin>>a>>b){
		if(a==b){
			cout<<0<<endl;
			continue;
		}

		clr(x,0);
		clr(y,0);		
		reps(i,a)x[i]=a[sz(a)-1-i]-'A';
		reps(i,b)y[i]=b[sz(b)-1-i]-'A';

		int res=0;
		int len=sz(a);

		while(1){			
			rep(i,10){
				if(++x[i]==10)x[i]=0;
				else break;
			}
			if(x[len])x[len]=0,++len;
			
			bool ok=len==sz(b);
			rep(i,sz(b))if(x[i]!=y[i]){ok=false;break;}
			if(ok)break;

			ok=true;
			rep(i,len-1)if(abs(x[i]-x[i+1])<=1){ok=false;break;}
			res+=ok;
		}

		cout<<res<<endl;
	}

	return 0;
}
