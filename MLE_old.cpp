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
		bool sign = false;
		if(*curPos == '-') {
			sign = true;
			++curPos;
		}
		int res = 0;
		while (*curPos > ' ') 
			res = res * 10 + (*(curPos++) & 15);
		return sign ? -res : res;
	}
};

const int maxn = 100000;
int tx[maxn * 4];
int ty[maxn * 4];
bool divX[maxn * 4];

bool cmpX(const pii &a, const pii &b) {
	return a.first < b.first;
}

bool cmpY(const pii &a, const pii &b) {
	return a.second < b.second;
}

void buildTree(int node, int left, int right, pii points[]) {
	if (left > right)
		return;
	int mid = (left + right) >> 1;

	//sort(points + left, points + right + 1, divX ? cmpX : cmpY);
	int minx = INT_MAX;
	int maxx = INT_MIN;
	int miny = INT_MAX;
	int maxy = INT_MIN;
	for (int i = left; i <= right; i++) {
		minx = min(minx, points[i].first);
		maxx = max(maxx, points[i].first);
		miny = min(miny, points[i].second);
		maxy = max(maxy, points[i].second);
	}
	divX[node] = (maxx - minx) >= (maxy - miny);
	nth_element(points + left, points + mid, points + right + 1, divX[node] ? cmpX : cmpY);

	tx[node] = points[mid].first;
	ty[node] = points[mid].second;
	if (left == right)
		return;
	buildTree(node * 2, left, mid - 1, points);
	buildTree(node * 2 + 1, mid + 1, right, points);
}

long long closestDist;
int closestNode;

void findNearestNeighbour(int node, int left, int right, int x, int y) {
	if (left > right)
		return;
	int dx = x - tx[node];
	int dy = y - ty[node];
	long long d = dx * (long long) dx + dy * (long long) dy;
	if (closestDist > d && d) {
		closestDist = d;
		closestNode = node;
	}
	if (left == right)
		return;

	int delta = divX[node] ? dx : dy;
	long long delta2 = delta * (long long) delta;
	int mid = (left + right) >> 1;
	int n1 = node << 1;
	int l1 = left;
	int r1 = mid - 1;
	int n2 = node << 1 | 1;
	int l2 = mid + 1;
	int r2 = right;
	if (delta > 0)
		swap(l1, l2), swap(r1, r2), swap(n1, n2);

	findNearestNeighbour(n1, l1, r1, x, y);
	if (delta2 < closestDist)
		findNearestNeighbour(n2, l2, r2, x, y);
}

int findNearestNeighbour(int n, int x, int y) {
	closestDist = LLONG_MAX;
	findNearestNeighbour(1, 0, n - 1, x, y);
	return closestNode;
}

int main( int argc, char* argv[] ) {
	#ifndef ONLINE_JUDGE
	freopen("input-nn.txt","r",stdin);
	freopen("output.txt","w",stdout);	
	#endif

	/*
	freopen("input-nn.txt","w",stdout);
	cout<<1<<endl;
	int n=100000;
	cout<<n<<endl;
	set<pii> s;
	rep(i,n){
	int x=rand();
	int y=rand();
	pii p=mp(x,y);
	if(s.count(p)){i--; continue;}
	s.insert(p);			
	cout<<x<<" "<<y<<endl;
	}
	exit(0);
	*/

	Scanner sc;
	int testCases = sc.nextInt();
	for(int testCase=1;testCase<=testCases;testCase++){
		int n = sc.nextInt();
		vpii p(n);
		rep(i,n){
			p[i].first = sc.nextInt();
			p[i].second= sc.nextInt();
		}

		buildTree(1, 0, n-1, &(vpii(p)[0]));

		//fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));

		rep(i,n){
			findNearestNeighbour(n, p[i].first, p[i].second);
			printf("%lld\n", closestDist);			
		}
	}

	//fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));

	return 0;
}
