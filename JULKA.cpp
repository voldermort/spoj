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

const int maxlength = 200;

class bigint {
public:
	int oper, length, a[maxlength];
	bigint(int = 0);
	~bigint();
	int max(int a, int b);
	void check();
	void operator=(bigint m);
	void operator=(int m);
	void operator=(char *s);
	bool operator<(bigint m);
	bool operator<=(bigint m);
	bool operator>(bigint m);
	bool operator>=(bigint m);
	bool operator==(bigint m);
	bool operator!=(bigint m);
	bigint operator-();
	bigint operator+(bigint m);
	void operator+=(bigint m);
	bigint operator-(bigint m);
	void operator-=(bigint m);
	bigint operator*(bigint m);
	bigint operator*(int m);
	void operator*=(bigint m);
	void operator*=(int m);
	bigint operator/(bigint m);
	bigint operator/(int m);
	void operator/=(bigint m);
	void operator/=(int m);
	bigint operator%(bigint m);
	bigint operator%(int m);
	void operator%=(bigint m);
	void operator%=(int m);
};
bigint abs(bigint m);
bool read(bigint &m);
void write(bigint m);
void swrite(char *s, bigint m);
void writeln(bigint m);
bigint sqr(bigint m);
bigint sqrt(bigint m);
bigint gcd(bigint a, bigint b);
bigint lcm(bigint a, bigint b);

int bigint::max(int a, int b) {
	return (a > b) ? a : b;
}
bigint::bigint(int v) {
	(*this) = v;
	this->check();
}
bigint::~bigint() {
}
void bigint::check() {
	for (; length > 0 && a[length] == 0; length--)
		;
	if (length == 0)
		oper = 1;
}
void bigint::operator=(bigint m) {
	oper = m.oper;
	length = m.length;
	memcpy(a, m.a, maxlength * sizeof(int));
	this->check();
}
void bigint::operator=(int m) {
	oper = (m > 0) ? 1 : -1;
	m = abs(m);
	memset(a, 0, maxlength * sizeof(int));
	for (length = 0; m > 0; m = m / 10000)
		a[++length] = m % 10000;
	this->check();
}
void bigint::operator=(char *s) {
	int i, L;
	(*this) = 0;
	if (s[0] == '-' || s[0] == '+') {
		if (s[0] == '-')
			oper = -1;
		L = strlen(s);
		for (i = 0; i < L; i++)
			s[i] = s[i + 1];
	}
	L = strlen(s);
	length = (L + 3) / 4;
	for (i = 0; i < L; i++)
		a[(L - i + 3) / 4] = a[(L - i + 3) / 4] * 10 + (s[i] - 48);
	this->check();
}
bool bigint::operator<(bigint m) {
	if (oper != m.oper)
		return oper < m.oper;
	if (length != m.length)
		return oper * length < m.length * oper;
	for (int i = length; i >= 1; i--)
		if (a[i] != m.a[i])
			return a[i] * oper < m.a[i] * oper;
	return false;
}
bool bigint::operator<=(bigint m) {
	return !(m < (*this));
}
bool bigint::operator>(bigint m) {
	return m < (*this);
}
bool bigint::operator>=(bigint m) {
	return !((*this) < m);
}
bool bigint::operator==(bigint m) {
	return (!((*this) < m)) && (!(m < (*this)));
}
bool bigint::operator!=(bigint m) {
	return ((*this) < m) || (m < (*this));
}
bigint bigint::operator-() {
	bigint c = (*this);
	c.oper = -c.oper;
	c.check();
	return c;
}
bigint abs(bigint m) {
	bigint c = m;
	c.oper = abs(c.oper);
	c.check();
	return c;
}
bigint bigint::operator+(bigint m) {
	if (m.length == 0)
		return (*this);
	if (length == 0)
		return m;
	if (oper == m.oper) {
		bigint c;
		c.oper = oper;
		c.length = max(length, m.length) + 1;
		for (int i = 1, temp = 0; i <= c.length; i++)
			c.a[i] = (temp = (temp / 10000 + a[i] + m.a[i])) % 10000;
		c.check();
		return c;
	}
	return (*this) - (-m);
}
bigint bigint::operator-(bigint m) {
	if (m.length == 0)
		return (*this);
	if (length == 0)
		return (-m);
	if (oper == m.oper) {
		bigint c;
		if (abs(*this) >= abs(m)) {
			c.oper = oper;
			c.length = length;
			for (int i = 1, temp = 0; i <= length; i++)
				c.a[i] = ((temp = (-int(temp < 0) + a[i] - m.a[i])) + 10000) % 10000;
			c.check();
			return c;
		}
		return -(m - (*this));
	}
	return (*this) + (-m);
}
bool read(bigint &m) {
	char s[maxlength * 4 + 10];
	if (scanf("%s", &s) == -1)
		return false;
	for (int i = 0; s[i]; i++)
		if (!(s[i] >= '0' && s[i] <= '9' || (s[i] == '+' || s[i] == '-') && i == 0))
			return false;
	m = s;
	return true;
}
void swrite(char *s, bigint m) {
	int L = 0;
	if (m.oper == -1)
		s[L++] = '-';
	sprintf(s + L, "%d", m.a[m.length]);
	for (; s[L] != 0; L++)
		;
	for (int i = m.length - 1; i >= 1; i--) {
		sprintf(s + L, "%04d", m.a[i]);
		L += 4;
	}
	s[L] = 0;
}
void write(bigint m) {
	if (m.oper == -1)
		printf("-");
	printf("%d", m.a[m.length]);
	for (int i = m.length - 1; i >= 1; i--)
		printf("%04d", m.a[i]);
}
void writeln(bigint m) {
	write(m);
	printf("\n");
}
bigint bigint::operator*(bigint m) {
	bigint c;
	c.oper = oper * m.oper;
	c.length = length + m.length;
	for (int i = 1; i <= m.length; i++) {
		int number = m.a[i], j, temp = 0;
		for (j = 1; j <= length; j++)
			c.a[i + j - 1] += number * a[j];
		if (i % 10 == 0 || i == m.length)
			for (j = 1; j <= c.length; j++)
				c.a[j] = (temp = (temp / 10000) + c.a[j]) % 10000;
	}
	c.check();
	return c;
}
bigint bigint::operator*(int m) {
	if (m < 0)
		return -((*this) * (-m));
	if (m > 100000)
		return (*this) * bigint(m);
	bigint c;
	c.length = length + 1;
	c.oper = oper;
	int t = 0;
	for (int i = 1; i <= c.length; i++)
		c.a[i] = (t = (t / 10000 + a[i] * m)) % 10000;
	c.check();
	return c;
}
bigint bigint::operator/(bigint m) {
	if (m.length == 0) {
		printf("Division by zero.\n");
		exit(0);
	}
	if (abs(*this) < abs(m))
		return 0;
	bigint c, left;
	c.oper = oper / m.oper;
	m.oper = 1;
	c.length = length - m.length + 1;
	left.length = m.length - 1;
	memcpy(left.a + 1, a + length - left.length + 1, left.length * sizeof(int));
	for (int i = c.length; i >= 1; i--) {
		left = left * 10000 + a[i];
		int head = 0, tail = 10000, mid;
		while (head + 1 < tail) {
			mid = (head + tail) / 2;
			if (m * mid <= left)
				head = mid;
			else
				tail = mid;
		}
		c.a[i] = head;
		left -= m * head;
	}
	c.check();
	return c;
}
bigint bigint::operator/(int m) {
	if (m < 0)
		return -((*this) / (-m));
	if (m > 100000)
		return (*this) / bigint(m);
	bigint c;
	c.oper = oper;
	c.length = length;
	int t = 0;
	for (int i = c.length; i >= 1; i--)
		c.a[i] = (t = (t % m * 10000 + a[i])) / m;
	c.check();
	return c;
}
bigint bigint::operator %(bigint m) {
	return (*this) - ((*this) / m) * m;
}
bigint bigint::operator%(int m) {
	if (m < 0)
		return -((*this) % (-m));
	if (m > 100000)
		return (*this) % bigint(m);
	int t = 0;
	for (int i = length; i >= 1; i--)
		t = (t * 10000 + a[i]) % m;
	return t;
}
bigint sqr(bigint m) {
	return m * m;
}
bigint sqrt(bigint m) {
	if (m.oper < 0 || m.length == 0)
		return 0;
	bigint c, last, now, templast;
	c.length = (m.length + 1) / 2;
	c.a[c.length] = int(sqrt(double(m.a[c.length * 2] * 10000 + m.a[c.length * 2 - 1])) + 1e-6);
	templast.length = c.length * 2;
	templast.a[c.length * 2 - 1] = (c.a[c.length] * c.a[c.length]) % 10000;
	templast.a[c.length * 2] = (c.a[c.length] * c.a[c.length]) / 10000;
	templast.check();
	for (int i = c.length - 1; i >= 1; i--) {
		last = templast;
		int head = 0, tail = 10000, mid, j, temp;
		while (head + 1 < tail) {
			mid = (head + tail) / 2;
			now = last;
			now.a[2 * i - 1] += mid * mid;
			for (j = i + 1; j <= c.length; j++)
				now.a[i + j - 1] += mid * c.a[j] * 2;
			now.length++;
			for (j = 2 * i - 1, temp = 0; j <= now.length; j++)
				now.a[j] = (temp = (temp / 10000 + now.a[j])) % 10000;
			now.check();
			if (now <= m) {
				templast = now;
				head = mid;
			} else
				tail = mid;
		}
		c.a[i] = head;
	}
	c.check();
	return c;
}
bigint gcd(bigint a, bigint b) {
	return (b == 0) ? a : gcd(b, a % b);
}
bigint lcm(bigint a, bigint b) {
	return a * b / gcd(a, b);
}
void bigint::operator+=(bigint m) {
	(*this) = (*this) + m;
}
void bigint::operator-=(bigint m) {
	(*this) = (*this) - m;
}
void bigint::operator*=(bigint m) {
	(*this) = (*this) * m;
}
void bigint::operator/=(bigint m) {
	(*this) = (*this) / m;
}
void bigint::operator%=(bigint m) {
	(*this) = (*this) % m;
}
void bigint::operator*=(int m) {
	(*this) = (*this) * m;
}
void bigint::operator/=(int m) {
	(*this) = (*this) / m;
}
void bigint::operator%=(int m) {
	(*this) = (*this) % m;
}


int main( int argc, char* argv[] ) {
	ios::sync_with_stdio(false);
	//freopen("input.txt","r",stdin);
	
	int testCases=10;
	for(int testCase=1;testCase<=testCases;testCase++){
		int n;
		bigint a,b;

		read(a);
		read(b);

		bigint c2=(a-b)/2;
		bigint c1=c2 + b;

		writeln(c1);
		writeln(c2);
	}

	return 0;
}
