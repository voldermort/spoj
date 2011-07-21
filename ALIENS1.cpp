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
#include <list>
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
template<class T> int sz(const T&c){return (int)c.size();}
template<class T> void srt(T&c){std::sort(c.begin(),c.end());}
template<class T> void checkmin(T &a,T b){if(b<a) a=b;}
template<class T> void checkmax(T &a,T b){if(b>a) a=b;}
template<class T> T sqr(T x){return x*x;}
template<class T, class U> T cast (U x) { ostringstream os; os<<x; T res; istringstream is(os.str()); is>>res; return res; }
template<class T> vector<T> split(string s, string x=" ") {vector<T> res; for(int i=0;i<s.size();i++){string a; while(i<(int)s.size()&&x.find(s[i])==string::npos)a+=s[i++]; if(!a.empty())res.push_back(cast<T>(a));} return res;}
template<class T> T inside(T r,T c,T R, T C){return r>=0 && r<R && c>=0 && c<C;}


// Functions
// =========
inline double mb_sqr (double r) {return r*r;}

// Class Declarations
// ==================

// smallest enclosing ball of a set of n points in dimension d
template <int d> 
class Miniball;

// smallest ball with a set of n <= d+1 points *on the boundary*
template <int d> 
class Miniball_b; 

// point in dimension d
template <int d> 
class Point;


// Class Definitions
// =================

// Miniball
// --------

template <int d>
class Miniball {
public:
	// types
	typedef typename std::list<Point<d> >::iterator         It;
	typedef typename std::list<Point<d> >::const_iterator   Cit;

private:
	// data members
	std::list<Point<d> > L;            // internal point set
	Miniball_b<d>        B;            // the current ball
	It                   support_end;  // past-the-end iterator of support set

	// private methods
	void        mtf_mb (It k);
	void        pivot_mb (It k);
	void        move_to_front (It j);
	double      max_excess (It t, It i, It& pivot) const;

public:
	// creates an empty ball
	Miniball() {}

	// copies p to the internal point set
	void        check_in (const Point<d>& p);

	// builds the smallest enclosing ball of the internal point set
	void        build ();

	// returns center of the ball (undefined if ball is empty)
	Point<d>       center() const;

	// returns squared_radius of the ball (-1 if ball is empty)
	double      squared_radius () const;

	// returns size of internal point set
	int         nr_points () const;

	// returns begin- and past-the-end iterators for internal point set
	Cit         points_begin () const;
	Cit         points_end () const;

	// returns size of support point set; this set has the following properties:
	// - there are at most d+1 support points, 
	// - all support points are on the boundary of the computed ball, and
	// - the smallest enclosing ball of the support point set equals the 
	//   smallest enclosing ball of the internal point set
	int         nr_support_points () const;

	// returns begin- and past-the-end iterators for internal point set
	Cit         support_points_begin () const;
	Cit         support_points_end () const;

	// assesses the quality of the computed ball. The return value is the
	// maximum squared distance of any support point or point outside the 
	// ball to the boundary of the ball, divided by the squared radius of
	// the ball. If everything went fine, this will be less than e-15 and
	// says that the computed ball approximately contains all the internal
	// points and has all the support points on the boundary.
	// 
	// The slack parameter that is set by the method says something about
	// whether the computed ball is really the *smallest* enclosing ball 
	// of the support points; if everything went fine, this value will be 0; 
	// a positive value may indicate that the ball is not smallest possible,
	// with the deviation from optimality growing with the slack
	double      accuracy (double& slack) const;

	// returns true if the accuracy is below the given tolerance and the
	// slack is 0
	bool        is_valid (double tolerance = 1e-15) const;
};


// Miniball_b
// ----------

template <int d>
class Miniball_b {
private:
	// data members
	int                 m, s;   // size and number of support points
	double              q0[d];

	double              z[d+1];
	double              f[d+1];
	double              v[d+1][d];
	double              a[d+1][d];

	double              c[d+1][d];
	double              sqr_r[d+1];

	double*             current_c;      // refers to some c[j]
	double              current_sqr_r;

public:
	Miniball_b() {reset();}

	// access
	const double*       center() const;
	double              squared_radius() const;
	int                 size() const;
	int                 support_size() const;
	double              excess (const Point<d>& p) const;

	// modification
	void                reset(); // generates empty sphere with m=s=0
	bool                push (const Point<d>& p);
	void                pop ();

	// checking
	double              slack() const;
};

// Point (inline)
// -------------
template <int d>
class Point {
private:
	double coord [d];

public:
	// default
	Point()
	{}

	// copy from Point
	Point (const Point& p)
	{
		for (int i=0; i<d; ++i)
			coord[i] = p.coord[i];
	}

	// copy from double*
	Point (const double* p)
	{
		for (int i=0; i<d; ++i)
			coord[i] = p[i];
	}

	// assignment
	Point& operator = (const Point& p)
	{
		if (this != &p)
			for (int i=0; i<d; ++i)
				coord[i] = p.coord[i];
		return *this;
	}

	// coordinate access
	double& operator [] (int i)
	{
		return coord[i];
	}
	const double& operator [] (int i) const
	{
		return coord[i];
	}
	const double* begin() const
	{
		return coord;
	}
	const double* end() const
	{
		return coord+d;
	}
};


// Class Implementations
// =====================

// Miniball
// --------

template <int d>
void Miniball<d>::check_in (const Point<d>& p)
{
	L.push_back(p);
}


template <int d>
void Miniball<d>::build ()
{
	B.reset();
	support_end = L.begin();
	pivot_mb (L.end());
}


template <int d>
void Miniball<d>::mtf_mb (It i)
{
	support_end = L.begin();
	if ((B.size())==d+1) return;
	for (It k=L.begin(); k!=i;) {
		It j=k++;
		if (B.excess(*j) > 0) {
			if (B.push(*j)) {
				mtf_mb (j);
				B.pop();
				move_to_front(j);
			}
		}
	}
}

template <int d>
void Miniball<d>::move_to_front (It j)
{
	if (support_end == j)
		support_end++;
	L.splice (L.begin(), L, j);
}


template <int d>
void Miniball<d>::pivot_mb (It i)
{
	It t = ++L.begin();
	mtf_mb (t);
	double max_e, old_sqr_r = -1;
	do {
		It pivot;
		max_e = max_excess (t, i, pivot);
		if (max_e > 0) {
			t = support_end;
			if (t==pivot) ++t;
			old_sqr_r = B.squared_radius();
			B.push (*pivot);
			mtf_mb (support_end);
			B.pop();
			move_to_front (pivot);
		}
	} while ((max_e > 0) && (B.squared_radius() > old_sqr_r));
}


template <int d>
double Miniball<d>::max_excess (It t, It i, It& pivot) const
{
	const double *c = B.center(), sqr_r = B.squared_radius();
	double e, max_e = 0;
	for (It k=t; k!=i; ++k) {
		const double *p = (*k).begin();
		e = -sqr_r;
		for (int j=0; j<d; ++j)
			e += mb_sqr(p[j]-c[j]);
		if (e > max_e) {
			max_e = e;
			pivot = k;
		}
	}
	return max_e;
}



template <int d>
Point<d> Miniball<d>::center () const
{
	return Point<d>(B.center());
}

template <int d>
double Miniball<d>::squared_radius () const
{
	return B.squared_radius();
}


template <int d>
int Miniball<d>::nr_points () const
{
	return L.size();
}

template <int d>
typename Miniball<d>::Cit Miniball<d>::points_begin () const
{
	return L.begin();
}

template <int d>
typename Miniball<d>::Cit Miniball<d>::points_end () const
{
	return L.end();
}


template <int d>
int Miniball<d>::nr_support_points () const
{
	return B.support_size();
}

template <int d>
typename Miniball<d>::Cit Miniball<d>::support_points_begin () const
{
	return L.begin();
}

template <int d>
typename Miniball<d>::Cit Miniball<d>::support_points_end () const
{
	return support_end;
}



template <int d>
double Miniball<d>::accuracy (double& slack) const
{
	double e, max_e = 0;
	int n_supp=0;
	Cit i;
	for (i=L.begin(); i!=support_end; ++i,++n_supp)
		if ((e = std::abs (B.excess (*i))) > max_e)
			max_e = e;

	// you've found a non-numerical problem if the following ever fails
	assert (n_supp == nr_support_points());

	for (i=support_end; i!=L.end(); ++i)
		if ((e = B.excess (*i)) > max_e)
			max_e = e;

	slack = B.slack();
	return (max_e/squared_radius());
}


template <int d>
bool Miniball<d>::is_valid (double tolerance) const
{
	double slack;
	return ( (accuracy (slack) < tolerance) && (slack == 0) );
}



// Miniball_b
// ----------

template <int d>
const double* Miniball_b<d>::center () const
{
	return current_c;
}

template <int d>
double Miniball_b<d>::squared_radius() const
{
	return current_sqr_r;
}

template <int d>
int Miniball_b<d>::size() const
{
	return m;
}

template <int d>
int Miniball_b<d>::support_size() const
{
	return s;
}

template <int d>
double Miniball_b<d>::excess (const Point<d>& p) const
{
	double e = -current_sqr_r;
	for (int k=0; k<d; ++k)
		e += mb_sqr(p[k]-current_c[k]);
	return e;
}



template <int d>
void Miniball_b<d>::reset ()
{
	m = s = 0;
	// we misuse c[0] for the center of the empty sphere
	for (int j=0; j<d; ++j)
		c[0][j]=0;
	current_c = c[0];
	current_sqr_r = -1;
}


template <int d>
void Miniball_b<d>::pop ()
{
	--m;
}


template <int d>
bool Miniball_b<d>::push (const Point<d>& p)
{
	int i, j;
	double eps = 1e-32;
	if (m==0) {
		for (i=0; i<d; ++i)
			q0[i] = p[i];
		for (i=0; i<d; ++i)
			c[0][i] = q0[i];
		sqr_r[0] = 0;
	} else {
		// set v_m to Q_m
		for (i=0; i<d; ++i)
			v[m][i] = p[i]-q0[i];

		// compute the a_{m,i}, i< m
		for (i=1; i<m; ++i) {
			a[m][i] = 0;
			for (j=0; j<d; ++j)
				a[m][i] += v[i][j] * v[m][j];
			a[m][i]*=(2/z[i]);
		}

		// update v_m to Q_m-\bar{Q}_m
		for (i=1; i<m; ++i) {
			for (j=0; j<d; ++j)
				v[m][j] -= a[m][i]*v[i][j];
		}

		// compute z_m
		z[m]=0;
		for (j=0; j<d; ++j)
			z[m] += mb_sqr(v[m][j]);
		z[m]*=2;

		// reject push if z_m too small
		if (z[m]<eps*current_sqr_r) {
			return false;
		}

		// update c, sqr_r
		double e = -sqr_r[m-1];
		for (i=0; i<d; ++i)
			e += mb_sqr(p[i]-c[m-1][i]);
		f[m]=e/z[m];

		for (i=0; i<d; ++i)
			c[m][i] = c[m-1][i]+f[m]*v[m][i];
		sqr_r[m] = sqr_r[m-1] + e*f[m]/2;
	}
	current_c = c[m];
	current_sqr_r = sqr_r[m];
	s = ++m;
	return true;
}

template <int d>
double Miniball_b<d>::slack () const
{
	double l[d+1], min_l=0;
	l[0] = 1;
	for (int i=s-1; i>0; --i) {
		l[i] = f[i];
		for (int k=s-1; k>i; --k)
			l[i]-=a[k][i]*l[k];
		if (l[i] < min_l) min_l = l[i];
		l[0] -= l[i];
	}
	if (l[0] < min_l) min_l = l[0];
	return ( (min_l < 0) ? -min_l : 0);
}

// Point
// -----

// Output
template <int d>
std::ostream& operator << (std::ostream& os, const Point<d>& p)
{
	os << "(";
	for (int i=0; i<d-1; ++i)
		os << p[i] << ", ";
	os << p[d-1] << ")";
	return os;
}


int main( int argc, char* argv[] ) {
	ios::sync_with_stdio(false);
	//freopen("input.txt","r",stdin);
	
	int testCases;
	scanf("%d", &testCases);
	for(int testCase=1;testCase<=testCases;testCase++){
		int n;
		scanf("%d", &n);

		Miniball<2> mb;

		Point<2> p;
		for (int i=0; i<n; ++i) {
			double c[2];
			scanf("%lf%lf", &c[0],&c[1]);
			mb.check_in(Point<2>(c));
		}

		mb.build();

		Point<2> center = mb.center();
		double r = sqrt(mb.squared_radius());

		printf("%.2f\n", r);
		printf("%.2f %.2f\n", center[0],center[1]);
	}

	return 0;
}
