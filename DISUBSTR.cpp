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


unsigned char mask[]={0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
#define tget(i) ( (t[(i)/8]&mask[(i)%8]) ? 1 : 0 )
#define tset(i, b) t[(i)/8]=(b) ? (mask[(i)%8]|t[(i)/8]) : ((~mask[(i)%8])&t[(i)/8])
#define chr(i) (cs==sizeof(int)?((int*)s)[i]:((unsigned char *)s)[i])
#define isLMS(i) (i>0 && tget(i) && !tget(i-1))
// find the start or end of each bucket
void getBuckets(unsigned char *s, int *bkt, int n, int K, int cs, bool end) {
	int i, sum=0;
	for(i=0; i<=K; i++) bkt[i]=0; // clear all buckets
	for(i=0; i<n; i++) bkt[chr(i)]++; // compute the size of each bucket
	for(i=0; i<=K; i++) { sum+=bkt[i]; bkt[i]=end ? sum : sum-bkt[i]; }
}
// compute SAl
void induceSAl(unsigned char *t, int *SA, unsigned char *s, int *bkt,
			   int n, int K, int cs, bool end) {
				   int i, j;
				   getBuckets(s, bkt, n, K, cs, end); // find starts of buckets
				   for(i=0; i<n; i++) {
					   j=SA[i]-1;
					   if(j>=0 && !tget(j)) SA[bkt[chr(j)]++]=j;
				   }
}
// compute SAs
void induceSAs(unsigned char *t, int *SA, unsigned char *s, int *bkt,
			   int n, int K, int cs, bool end) {
				   int i, j;
				   getBuckets(s, bkt, n, K, cs, end); // find ends of buckets
				   for(i=n-1; i>=0; i--) {
					   j=SA[i]-1;
					   if(j>=0 && tget(j)) SA[--bkt[chr(j)]]=j;
				   }
}
// find the suffix array SA of s[0..n-1] in {1..K}^n
// require s[n-1]=0 (the sentinel!), n>=2
// use a working space (excluding s and SA) of at most 2.25n+O(1) for a constant alphabet
void SA_IS(unsigned char *s, int *SA, int n, int K, int cs) {
	int i, j;
	unsigned char *t=(unsigned char *)malloc(n/8+1); // LS-type array in bits
	// Classify the type of each character
	tset(n-2, 0); tset(n-1, 1); // the sentinel must be in s1, important!!!
	for(i=n-3; i>=0; i--)
		tset(i, (chr(i)<chr(i+1) || (chr(i)==chr(i+1) && tget(i+1)==1))?1:0);
	// stage 1: reduce the problem by at least 1/2
	// sort all the S-substrings
	int *bkt = (int *)malloc(sizeof(int)*(K+1)); // bucket array
	getBuckets(s, bkt, n, K, cs, true); // find ends of buckets
	for(i=0; i<n; i++) SA[i]=-1;
	for(i=1; i<n; i++)
		if(isLMS(i)) SA[--bkt[chr(i)]]=i;
	induceSAl(t, SA, s, bkt, n, K, cs, false);
	induceSAs(t, SA, s, bkt, n, K, cs, true);
	free(bkt);
	// compact all the sorted substrings into the first n1 items of SA
	// 2*n1 must be not larger than n (proveable)
	int n1=0;
	for(i=0; i<n; i++)
		if(isLMS(SA[i])) SA[n1++]=SA[i];
	// find the lexicographic names of all substrings
	for(i=n1; i<n; i++) SA[i]=-1; // init the name array buffer
	int name=0, prev=-1;
	for(i=0; i<n1; i++) {
		int pos=SA[i]; bool diff=false;
		for(int d=0; d<n; d++)
			if(prev==-1 || chr(pos+d)!=chr(prev+d) || tget(pos+d)!=tget(prev+d))
			{ diff=true; break; }
			else if(d>0 && (isLMS(pos+d) || isLMS(prev+d))) break;
			if(diff) { name++; prev=pos; }
			pos=(pos%2==0)?pos/2:(pos-1)/2;
			SA[n1+pos]=name-1;
	}
	for(i=n-1, j=n-1; i>=n1; i--)
		if(SA[i]>=0) SA[j--]=SA[i];
	// stage 2: solve the reduced problem
	// recurse if names are not yet unique
	int *SA1=SA, *s1=SA+n-n1;
	if(name<n1)
		SA_IS((unsigned char*)s1, SA1, n1, name-1, sizeof(int));
	else // generate the suffix array of s1 directly
		for(i=0; i<n1; i++) SA1[s1[i]] = i;
	// stage 3: induce the result for the original problem
	bkt = (int *)malloc(sizeof(int)*(K+1)); // bucket array
	// put all left-most S characters into their buckets
	getBuckets(s, bkt, n, K, cs, true); // find ends of buckets
	for(i=1, j=0; i<n; i++)
		if(isLMS(i)) s1[j++]=i; // get p1
	for(i=0; i<n1; i++) SA1[i]=s1[SA1[i]]; // get index in s
	for(i=n1; i<n; i++) SA[i]=-1; // init SA[n1..n-1]
	for(i=n1-1; i>=0; i--) {
		j=SA[i]; SA[i]=-1;
		SA[--bkt[chr(j)]]=j;
	}
	induceSAl(t, SA, s, bkt, n, K, cs, false);
	induceSAs(t, SA, s, bkt, n, K, cs, true);
	free(bkt); free(t);
}


const int maxn = 1 << 16;
char s[maxn];
int p[maxn];
int rank[maxn];
int lcp[maxn];
unsigned int res;

void process(char s[], int n) {
	if (n == 0) {
		return;
	}
	if (n == 1) {
		p[0]=0;
		rank[0]=0;
		return;
	}
	SA_IS((unsigned char*)s, p, n+1, 256, 1);

	for (int i = 0; i < n; i++) {
		rank[p[i+1]] = i;
	}
	int h = 0;
	for (int i = 0; i < n; i++) {
		if (rank[i] < n - 1) {
			int j = p[rank[i] + 1 + 1];
			while (s[i + h] == s[j + h]) {
				++h;
			}
			//lcp[rank[i]] = h;
			res -= h;
			if (h > 0) {
				--h;
			}
		}
	}
}


int main( int argc, char* argv[] ) {
	ios::sync_with_stdio(false);
	//freopen("input.txt","r",stdin);
	
	int testCases;
	scanf("%d", &testCases);
	gets(s);
	for(int testCase=1;testCase<=testCases;testCase++){
		gets(s);
		int n = strlen(s);

		res = n;
		res = res*(res+1)/2;

		process(s,n);

		//rep(i,n-1)sum-=lcp[i];

		printf("%u\n", res);
	}

	return 0;
}
