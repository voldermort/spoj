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
#include <stdio.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(x) (x).begin(),(x).end()
#define CLR(x,a) memset(x,a,sizeof(x))
#define PI 2*acos(0.0)
#define MP make_pair
typedef vector<int> vi;
typedef long long ll;
typedef pair<int, int> pii;
template<class T> void print(vector<T> const &v) {
	ostringstream os;
	for (int i = 0; i < v.size(); ++i) {
		if (i > 0) {
			os << ' ';
		}
		os << v[i];
	}
	cout << os.str() << endl;
}

int t[200000];
int n;

int highestOneBit(int i) {
	i |= (i >> 1);
	i |= (i >> 2);
	i |= (i >> 4);
	i |= (i >> 8);
	i |= (i >> 16);
	return i - (i >> 1);
}

void update(int i, int value) {
	while (i < n) {
		t[i] += value;
		i += (i + 1) & -(i + 1);
	}
}

// Returns sum of elements in range [0, i]
int sum(int i) {
	int res = 0;
	while (i >= 0) {
		res += t[i];
		i -= (i + 1) & -(i + 1);
	}
	return res;
}

// Returns sum of elements in range [a, b]
int sum(int a, int b) {
	return sum(b) - sum(a - 1);
}

// number of free places in [x, n - 1]
int getFree(int x) {
	return n - x - sum(x, n - 1);
}

int getFreeKthElementFromRight(int k) {
	int lo = 0;
	int hi = n - 1;
	while (lo < hi) {
		int mid = (lo + hi + 1) / 2;
		int midVal = getFree(mid);
		if (midVal < k) {
			hi = mid - 1;
		} else {
			lo = mid;
		}
	}
	return hi;
}

int find(int k) {
	int idx = 0;
	int bitMask = highestOneBit(n);
	while (bitMask != 0) {
		int tIdx = idx + bitMask;
		if (tIdx <= n && k >= t[tIdx - 1]) {
			idx = tIdx;
			k -= t[tIdx - 1];
		}
		bitMask >>= 1;
	}
	return idx - 1;
}

int main() {
	int tc;
	scanf("%d", &tc);
	while (tc--) {
		fill(t, t + 200000, 0);
		scanf("%d", &n);
		vi a(n);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			update(i, 1);
		}
		vi res(n);
		for (int i = n - 1; i >= 0; --i) {
			int p = find(i - a[i]) + 1;
			res[i] = p + 1;
			update(p, -1);
		}
		for (int i = 0; i < res.size(); ++i) {
			if (i > 0) {
				printf(" ");
			}
			printf("%d", res[i]);
		}
		printf("\n");
	}
}

