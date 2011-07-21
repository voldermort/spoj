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

vi up1,down1,a1;

class Point {
public:
	int x, y;
	Point(int x, int y) :
	x(x), y(y) {
	}
};

bool cmp(Point a, Point b) {
	return a.x < b.x || a.x == b.x && a.y < b.y;
}
bool cw(Point &a, Point &b, Point &c) {
	return ll(b.x - a.x) * (c.y - a.y) - ll(b.y - a.y) * (c.x - a.x) < 0;
}

bool ccw(Point &a, Point &b, Point &c) {
	return ll(b.x - a.x) * (c.y - a.y) - ll(b.y - a.y) * (c.x - a.x) > 0;
}

void convex_hull(vector<Point> & a) {
	if (a.size() == 1)
		return;
	sort(a.begin(), a.end(), &cmp);
	Point p1 = a[0], p2 = a.back();
	vector<Point> up, down;
	up1.clear();
	down1.clear();
	up.push_back(p1); up1.pb(0);
	down.push_back(p1); down1.pb(0);
	for (size_t i = 1; i < a.size(); ++i) {
		if (i == a.size() - 1 || ccw(p1, a[i], p2)) {
			while (up.size() >= 2 && !ccw(up[up.size() - 2], up[up.size() - 1], a[i]))
				up.pop_back(),up1.pop_back();
			up.push_back(a[i]),up1.push_back(i);
		}
		if (i == a.size() - 1 || cw(p1, a[i], p2)) {
			while (down.size() >= 2 && !cw(down[down.size() - 2], down[down.size() - 1], a[i]))
				down.pop_back(),down1.pop_back();
			down.push_back(a[i]),down1.push_back(i);
		}
	}
	if (up[0].x == up.back().x && up[0].y == up.back().y)
		up.erase(up.end() - 1),up1.erase(up1.end()-1);
	a.clear();a1.clear();	
	for (size_t i = 0; i < up.size(); ++i)
		a.push_back(up[i]),a1.push_back(up1[i]);
	for (size_t i = down.size() - 2; i > 0; --i)
		a.push_back(down[i]),a1.push_back(down1[i]);
}

double square(vector<Point> p){
	double res=0;
	int n=p.size();
	reps(i,p)res+=p[i].x*p[(i+1)%n].y - p[i].y*p[(i+1)%n].x;
	return abs(res)/2;
}

int main( int argc, char* argv[] ) {
	ios::sync_with_stdio(false);
	freopen("input.txt","r",stdin);
	//freopen("output.txt", "w", stdout);
	
	int testCases;
	scanf("%d", &testCases);
	for(int testCase=1;testCase<=testCases;testCase++){
		int n;
		scanf("%d", &n);
		vector<Point> p;
		rep(i,n){
			int x,y;
			scanf("%d%d", &x,&y);
			p.pb(Point(x,y));
		}
		
		convex_hull(p);

		double res=square(p);
		printf("%.2\n", res);

		reps(i,p){
			if(i)printf(" ");
			printf("%d", a1[i] + 1);
		}
		printf("\n\n");
	}

	return 0;
}
