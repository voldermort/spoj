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

struct Node {
	pii p;
	Node* left;
	Node* right;
	bool divX;
};

bool cmpX(const pii &a, const pii &b) {
	return a.first < b.first;
}

bool cmpY(const pii &a, const pii &b) {
	return a.second < b.second;
}

Node* root;

Node* buildTree(int left, int right, pii points[]) {
	if (left >= right)
		return NULL;
	
	int mid = (left + right) >> 1;

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
	bool divX = (maxx - minx) >= (maxy - miny);
	nth_element(points + left, points + mid, points + right, divX ? cmpX : cmpY);

	Node *node = new Node;
	node->p = points[mid];
	node->left = buildTree(left, mid, points);
	node->right = buildTree(mid + 1, right, points);
	node->divX = divX;
	return node;
}

ll closestDist;
Node* closestNode;

void findNearestNeighbour(Node* node, int x, int y) {
	if (node == NULL)
		return;
	int dx = x - node->p.first;
	int dy = y - node->p.second;

	long long d = dx * (long long) dx + dy * (long long) dy;
	if (closestDist > d && d) {
		closestDist = d;
		closestNode = node;
	}

	int delta = node->divX ? dx : dy;
	long long delta2 = delta * (long long) delta;

	Node *node1 = node->left;
	Node *node2 = node->right;
	if(delta > 0) swap(node1, node2);

	findNearestNeighbour(node1, x, y);
	if (delta2 < closestDist) {
		findNearestNeighbour(node2, x, y);
	}
}

Node* findNearestNeighbour(int x, int y) {
	closestDist = LLONG_MAX;
	findNearestNeighbour(root, x, y);
	return closestNode;
}

int main( int argc, char* argv[] ) {
	#ifndef ONLINE_JUDGE
	freopen("input-nn.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif	

	Scanner sc;
	int testCases = sc.nextInt();
	for(int testCase=1;testCase<=testCases;testCase++){
		int n = sc.nextInt();
		vpii p(n);
		rep(i,n){
			p[i].first = sc.nextInt();
			p[i].second= sc.nextInt();
		}

		root = buildTree(0, n, &(vpii(p)[0]));

		//fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));

		rep(i,n){
			findNearestNeighbour(p[i].first, p[i].second);
			printf("%lld\n", closestDist);			
		}
	}

	fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));

	return 0;
}
