#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
using namespace std;

typedef vector<int> vi;
typedef long long ll;

int t[1<<18];
int rt[1<<18];
int n;

int highestOneBit(int i) {
	i |= (i >> 1);
	i |= (i >> 2);
	i |= (i >> 4);
	i |= (i >> 8);
	i |= (i >> 16);
	return i - (i >> 1);
}

void inc1(int i) {
	while (i < n) {
		++t[i];
		i|=i+1;
	}
}

void dec1(int i) {
	while (i < n) {
		--t[i];
		i|=i+1;
	}
}

int highestBit;

int find(int k) {
	int idx = 0;
	int bitMask = highestBit;
	while (bitMask != 0) {
		int tIdx = idx + bitMask;
		if (tIdx < n && k >= t[tIdx-1]) {
			idx = tIdx;
			k -= t[tIdx-1];
		}
		bitMask >>= 1;
	}
	return idx;
}

char buf1[1<<26];
int pos1;

int nextInt() {
	while (buf1[pos1] <= ' ') ++pos1;
	int res = 0;
	while (buf1[pos1] > ' ') 
		res = res*10+(buf1[pos1++]&15);
	return res;
}

char buf2[1<<26];
int pos2;

void writeInt(int x) {
	char d[10];
	int c=0;
	while(true){		
		d[c++] = x%10 + '0';
		x/=10;
		//int y = (x * 52429LL) >> 19;
		//d[c++] = x - y*10 + '0';
		//x = y;
		if(x==0)break;
	}
	while(--c>=0)buf2[pos2++]=d[c];
}

void writeChar(char x) {
	buf2[pos2++]=x;
}

int main() {
	//freopen("input.txt","r",stdin);
	fread(buf1, 1, sizeof(buf1), stdin);
	n = 200000;
	for (int i = 0; i < n; ++i) {
		inc1(i);
	}
	copy(t, t + n, rt);

	int tc = nextInt();
	while (tc--) {		
		n = nextInt();
		highestBit = highestOneBit(n);
		copy(rt, rt + n, t);
		vi a(n);
		for (int i = 0; i < n; ++i) {
			a[i] = nextInt();
		}
		vi res(n);
		for (int i = n - 1; i >= 0; --i) {
			int p = find(i - a[i]);
			res[i] = p + 1;
			dec1(p);
		}
		for (int i = 0; i < res.size(); ++i) {
			if (i > 0) writeChar(' ');
			writeInt(res[i]);
		}
		writeChar('\n');
	}
	fwrite(buf2, 1, pos2, stdout);
}

