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
#include <cstring>
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

char a[10001],b[10001],c[20005];

vector<ll> karatsubaMultiply(vector<ll> &a, vector<ll> &b){
	int n=a.size();
	vector<ll> res(n+n);
	if(n<=64){
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)res[i+j]+=a[i]*b[j];
		return res;			
	}

	int k=n/2;
	vector<ll> a1(a.begin(),a.begin()+k);
	vector<ll> a2(a.begin()+k,a.end());
	vector<ll> b1(b.begin(),b.begin()+k);
	vector<ll> b2(b.begin()+k,b.end());

	vector<ll> a1b1=karatsubaMultiply(a1,b1);
	vector<ll> a2b2=karatsubaMultiply(a2,b2);

	for(int i=0;i<k;i++)a2[i]+=a1[i];
	for(int i=0;i<k;i++)b2[i]+=b1[i];

	vector<ll> r=karatsubaMultiply(a2,b2);		
	for(int i=0;i<a1b1.size();i++)r[i]-=a1b1[i];
	for(int i=0;i<a2b2.size();i++)r[i]-=a2b2[i];

	for(int i=0;i<r.size();i++)res[i+k]+=r[i];
	for(int i=0;i<a1b1.size();i++)res[i]+=a1b1[i];
	for(int i=0;i<a2b2.size();i++)res[i+n]+=a2b2[i];
	return res;		
}

int main( int argc, char* argv[] ) {
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	#endif	
	
	vl p10(10);
	p10[0]=1;
	rep(i,9)p10[i+1]=p10[i]*10;

	int testCases;
	scanf("%d", &testCases);
	for(int testCase=1;testCase<=testCases;testCase++){
		scanf("%s %s",a,b);		
		int n1=strlen(a);
		int n2=strlen(b);
		vl x((n1+7)/8),y((n2+7)/8);
		rep(i,n1)x[i/8]+=p10[i%8]*(a[n1-1-i]-'0');
		rep(i,n2)y[i/8]+=p10[i%8]*(b[n2-1-i]-'0');
		while(sz(x)<sz(y))x.pb(0);
		while(sz(x)>sz(y))y.pb(0);
		while(sz(x)&sz(x)-1)x.pb(0),y.pb(0);
		vl res=karatsubaMultiply(x,y);
		fr(i,0,sz(res)-2)res[i+1]+=res[i]/p10[8],res[i]%=p10[8];

		vl r;
		reps(i,res)rep(j,8)r.pb(res[i]/p10[j]%10);

		int k=sz(r)-1;
		while(k && r[k]==0)k--;
		k++;		
		r.resize(k);
		clr(c,' ');
		c[k]=0;
		rep(i,k)c[i]=r[k-1-i]+'0';
		
		printf("%s\n", c);
	}

	return 0;
}
