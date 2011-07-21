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

#include <memory.h>
using namespace std;

#define FOR(i,a,n) for (int i = (a); i < (n); ++i)
#define FORE(i,a,n) for (int i = (a); i <= (n); ++i)
#define FORD(i,a,b) for (int i = (a); i >= (b); --i)
#define REP(i,n) FOR(i,0,n)
#define REPE(i,n) FORE(i,0,n)
#define LL long long
#define FIR(n) REP(i,n)
#define FJR(n) REP(j,n)
#define ALL(v) v.begin(), v.end()

#define FI FIR(n)
#define FJ FJR(n)
#define FR(i,a) FOR(i,a,n)
#define REPN(i) REP(i,n)

typedef pair<int, int> PI;

int source[1 << 15];
int n, nq;
map<int, int> posMap;
PI q[250000];
int l1[200001];
int l2[200001];
int res[200001];

int a[1 << 15];
void add(int pos) {for (++pos;pos <= n; pos += pos&-pos) ++a[pos];}
int sum(int upto) {int res = 0; for(;upto; upto &= upto-1) res += a[upto]; return res;}
int sum(int from, int upto) {return sum(upto) - sum(from);}

#define GI(n) scanf("%d", &n)
#define GI2(n1, n2) scanf("%d %d", &n1, &n2)

#define INF 1000000
int vis[1000001];

int main( int argc, char* argv[] ) {

//freopen("input.txt", "rt", stdin);
	memset(vis, -1, sizeof vis);
	GI(n); 
	FI {
		int k;
		GI(k);
		source[i] = vis[k];
		vis[k] = i;
	}

	GI(nq);
	FIR(nq) {
		GI2(l1[i], l2[i]); 
		q[i].first = --l1[i]; 
		q[i].second = i;
	}
	int nn = nq;
	FI if (source[i] >= 0) {
		q[nn].first = source[i];
		q[nn].second = INF + i;
		++nn;
	}
	sort(q, q+nn, greater<PI>());
	
	memset(a, 0, sizeof a);
	FIR(nn) 
		if (q[i].second >= INF)
			add(q[i].second - INF);
		else {
			int pos = q[i].second;
			res[pos] = l2[pos] - l1[pos] - sum(l1[pos], l2[pos]);
		}

	FIR(nq)
		printf("%d\n", res[i]);

}