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

#define MAX 10000
#define SIZE 500

int a[30000];
int t[31000 / SIZE][MAX];

void update(int k, int i, int value) {
    while (i < MAX) {
        t[k][i] += value;
        i += (i + 1) & -(i + 1);
    }
}

// Returns sum of elements in range [0, i]
int sum(int k, int i) {
    int res = 0;
    while (i >= 0) {
        res += t[k][i];
        i -= (i + 1) & -(i + 1);
    }
    return res;
}

// Returns sum of elements in range [a, b]
int sum(int k, int a, int b) {
    return sum(k, b) - sum(k, a - 1);
}

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    vector<pii> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &a[i].first, &a[i].second);
    }
    cout << a[3].second;
}

