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
typedef vector<vector<pair<int,long long> > > Graph;

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

vi p;

void getPrimes(int n){
	vb primes(n+1,true);
	for(int i=2;i<=n;i++){
		for(int j=i+i;j<=n;j+=i)primes[j]=false;
	}
	fr(i,2,n)if(primes[i])p.push_back(i);
}

bool isPrime(int x){
	if(x<=1)return false;
	for(int i=0;i<sz(p)&&p[i]*p[i]<=x;i++)
		if(x%p[i]==0)return false;
	return true;
}

int pow(int a,int p,int mod){
	ll res=1;
	while(p){
		if(p&1)res=res*a%mod;
		a=ll(a)*a%mod;
		p/=2;
	}
	return res;
}

bool isProbablePrime(int x){
	if (x == 2)
		return true;
	if (x == 1 || (x & 1) == 0)
		return false;
	int y = x - 1;
	int u = 0;
	while((y&1)==0)y>>=1,u++;
	for (int iterations = 0; iterations < 50; iterations++) {
		int b = ((rand()<<16)+rand())%(x - 1) + 1;
		int z = (int) pow(b, y, x);
		int j = 0;
		while (!(j == 0 && z == 1 || z == x - 1)) {
			if (j > 0 && z == 1 || ++j == u)
				return false;
			z = (int) pow(z, 2, x);
		}
	}
	return true;
}


int main( int argc, char* argv[] ) {
	srand(10);
	ios::sync_with_stdio(false);
	//freopen("input.txt","r",stdin);
	//freopen("output.txt", "w", stdout);
	//getPrimes(32000);
	//cout<<isProbablePrime(1000099999);

	int t;
	scanf("%d", &t);
	rep(i,t){
		int a,b;
		scanf("%d%d",&a,&b);
		int cnt=0;
		fr(i,a,b)if(isProbablePrime(i))printf("%d\n", i),cnt++;
		printf("\n");
		//printf("%d",cnt);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
