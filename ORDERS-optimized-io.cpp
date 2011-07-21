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

int rt[200000];
int t[200000];
int a[200000];
int res[200000];
int n;
int bitMask;
char s[2000000];
int pdiv10[200001];
int pmod10[200001];

int highestOneBit(int i) {
    i |= (i >> 1);
    i |= (i >> 2);
    i |= (i >> 4);
    i |= (i >> 8);
    i |= (i >> 16);
    return i - (i >> 1);
}

void add(int i, int value) {
    while (i < n) {
        t[i] += value;
        //i += (i + 1) & -(i + 1);
        i |= i + 1;
    }
}

int find(int sum) {
    int pos = -1;
    for (int blockSize = bitMask; blockSize != 0; blockSize >>= 1) {
        int nextPos = pos + blockSize;
        if (nextPos < n && sum >= t[nextPos]) {
            pos = nextPos;
            sum -= t[nextPos];
        }
    }
    return pos;
}

int main() {
    for (int i = 0; i <= 200000; ++i) {
        pdiv10[i] = i / 10;
        pmod10[i] = i % 10;
    }
    n = 200000;
    for (int i = 0; i < n; ++i) {
        add(i, 1);
    }
    copy(t, t + n, rt);
    int tc;
    scanf("%d", &tc);
    while (tc--) {
        scanf("%d", &n);
        bitMask = highestOneBit(n);
        gets(s);
        gets(s);
        int j = 0;
        int k = 0;
        int v = 0;
        bool ok = false;
        while (1) {
            if (s[j] >= '0' && s[j] <= '9') {
                v = v * 10 + s[j] - '0';
                ok = true;
            } else if (ok) {
                a[k++] = v;
                v = 0;
                ok = false;
            }
            if (s[j] == 0) {
                break;
            }
            j++;
        }
        copy(rt, rt + n, t);
        for (int i = n - 1; i >= 0; --i) {
            int p = find(i - a[i]) + 1;
            res[i] = p + 1;
            add(p, -1);
        }
        int c = 0;
        char d[10];
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                s[c++] = ' ';
            }
            int m = 0;
            for (int x = res[i]; x > 0; x = pdiv10[x]) {
                d[m++] = pmod10[x] + '0';
            }
            for (int i = m - 1; i >= 0; --i) {
                s[c++] = d[i];
            }
        }
        s[c] = 0;
        puts(s);
    }
}

