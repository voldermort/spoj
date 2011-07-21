#include <cstdio>
#include <ctype.h>
#include <algorithm>
#include <memory.h>
using namespace std;

#define MAXN 1024

int t[MAXN][MAXN];
int t2[MAXN][MAXN];
int R, C;

#define BUFSIZE 1<<20
char buf1[BUFSIZE];
int pos1 = BUFSIZE;

char getChar() {
	if(pos1 == BUFSIZE){
		fread(buf1, 1, BUFSIZE, stdin);
		pos1 = 0;
	}
	return buf1[pos1++];
}

int nextInt() {
	char x;
	bool neg = false;
	while (true){
		x = getChar();
		if(x=='-')neg=true;
		else if(isdigit(x))break;
	}
	int res = 0;
	while (isdigit(x)) {
		res = res*10+(x&15);
		x = getChar();
	}
	return neg?-res:res;
}

char nextChar() {
	char x;
	while (!isalpha(x = getChar()));
	return x;
}

char buf2[BUFSIZE];
int pos2;

void putChar(char x) {
	if(pos2 == BUFSIZE) {
		fwrite(buf2, 1, BUFSIZE, stdout);
		pos2=0;
	}
	buf2[pos2++]=x;
}

void writeInt(int x) {
	char d[10];
	int c=0;
	while(true){		
		d[c++] = x%10 + '0';
		x/=10;
		if(x==0)break;
	}
	while(--c>=0)putChar(d[c]);
}

void add(int r, int c, int value) {
	for (int i = r; i < R; i += (i + 1) & -(i + 1))
		for (int j = c; j < C; j += (j + 1) & -(j + 1))
			t[i][j] += value;
}

int sum(int r, int c) {
	int res = 0;
	for (int i = r; i >= 0; i -= (i + 1) & -(i + 1))
		for (int j = c; j >= 0; j -= (j + 1) & -(j + 1))
			res += t[i][j];
	return res;
}

int sum(int r1, int c1, int r2, int c2) {
	return sum(r2, c2) - sum(r1 - 1, c2) - sum(r2, c1 - 1) + sum(r1 - 1, c1 - 1);
}

void set(int r, int c, int value) {
	add(r, c, -t2[r][c] + value);
}
int main() {
	//freopen("input.txt","r",stdin);

	int tc=nextInt();
	while(tc--){
		int n = nextInt();
		R = C = n;
		memset(t, 0, sizeof(t));
		memset(t2, 0, sizeof(t2));

		while(true){
			char s;
			nextChar();
			s = nextChar();
			nextChar();

			if(s=='E'){
				int r=nextInt();
				int c=nextInt();
				int v=nextInt();
				set(r, c, v);
			} else if(s=='U') {
				int r1=min(nextInt(),R-1);
				int c1=min(nextInt(),C-1);
				int r2=min(nextInt(),R-1);
				int c2=min(nextInt(),C-1);
				r1=max(r1,0);
				c1=max(c1,0);
				r2=max(r2,0);
				c2=max(c2,0);
				writeInt(sum(r1,c1,r2,c2));
				putChar('\n');
			} else 
				break;
		}
		putChar('\n');
	}

	fwrite(buf2, 1, pos2, stdout);
}
