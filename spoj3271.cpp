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
//    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        x--;
        a[i] = x;
        update(i / SIZE, x, 1);
    }
    int q;
    cin >> q;
    for (int w = 0; w < q; ++w) {
        int b;
        cin >> b;
        if (b == 0) {
            int i, v;
            scanf("%d%d", &i, &v);
            v--;
            i--;
            update(i / SIZE, a[i], -1);
            a[i] = v;
            update(i / SIZE, a[i], 1);
        }
        if (b == 1) {
            int i, j, k;
            scanf("%d%d%d", &i, &j, &k);
            i--;
            j--;
            k--;
            int res = 0;
            for (int p = (i + SIZE - 1) / SIZE; p < j / SIZE; ++p) {
                res += sum(p, k + 1, MAX-1);
            }
            if ((i + SIZE - 1) / SIZE * SIZE >= j) {
                for (int p = i; p <= j; ++p) {
                    if (a[p] > k) {
                        res++;
                    }
                }
            } else {
                for (int p = i; p < (i + SIZE - 1) / SIZE
                        * SIZE; ++p) {
                    if (a[p] > k) {
                        res++;
                    }
                }
                for (int p = j / SIZE * SIZE; p <= j; ++p) {
                    if (a[p] > k) {
                        res++;
                    }
                }
            }
            cout << res << endl;
        }
    }
}

