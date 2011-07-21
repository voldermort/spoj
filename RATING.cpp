#include <cstdio>
#include <algorithm>
using namespace std;

struct item {
	int x, y;
	int pos;

	bool operator<(const item &o) const {
		if(x!=o.x)return x<o.x;
		return y<o.y;
	}
};

#define MAXN 300000
#define MAXT 100001
template<class T> void checkmax(T &a,T b){if(b>a) a=b;}

item items[MAXN];
int res[MAXN];
int t[MAXT];
int n;
int maxy;

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
		if(x==0)break;
	}
	while(--c>=0)buf2[pos2++]=d[c];
}

void writeChar(char x) {
	buf2[pos2++]=x;
}

void inc(int i) {
	for (; i <= maxy; i += i & -i)
		++t[i];
}

int sum(int i) {
	int res = 0;
	for (; i > 0; i &= i - 1)
		res += t[i];
	return res;
}

int main() {
	//freopen("input.txt","r",stdin);
	fread(buf1, 1, sizeof(buf1), stdin);

	n = nextInt();

	for(int i=0;i<n;i++) {
		items[i].x = nextInt();
		items[i].y = nextInt();
		items[i].pos = i;
		checkmax(maxy, items[i].y);
	}

	sort(items, items + n);

	int prev=-1;
	for(int i=0;i<n;i++){
		if(i && items[i-1].x == items[i].x && items[i-1].y == items[i].y)
			res[items[i].pos] = prev;
		else
			res[items[i].pos] = prev = sum(items[i].y);
		inc(items[i].y);
	}

	for(int i=0;i<n;i++) {
		writeInt(res[i]);
		writeChar('\n');
	}

	fwrite(buf2, 1, pos2, stdout);
}
