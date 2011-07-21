#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;
#define rep(i,n) for(int i(0),_n(n);i<_n;++i)

const int MAXN = 200000;

struct node
{
	int cnt;
	int prio;
	int value;
	int sum;
	int pref;
	int suff;
	int maxs;
	node *l;
	node *r;
};

node treap[MAXN];
int t_cnt;
vi rnd;
node *root;


int cnt(node *p) {
	return p ? p->cnt : 0;
}

int sum(node *p) {
	return p ? p->sum : 0;
}

int maxs(node *p) {
	return p ? p->maxs : INT_MIN;
}

int pref(node *p) {
	return p ? p->pref : 0;
}

int suff(node *p) {
	return p ? p->suff : 0;
}

void update(node *p) {
	if(!p)return;
	p->cnt = 1 + cnt(p->l) + cnt(p->r);
	p->sum = p->value + sum(p->l) + sum(p->r);
	p->maxs = max( max(maxs(p->l), maxs(p->r)), max(0, suff(p->l)) + p->value + max(0, pref(p->r)));
	p->pref = max(pref(p->l), sum(p->l) + p->value + max(0, pref(p->r)));
	p->suff = max(suff(p->r), max(0, suff(p->l)) + p->value + sum(p->r));
}

void merge(node *&t, node *l, node *r) {
	if (!l)
		t = r;
	else if (!r)
		t = l;
	else if (l->prio < r->prio)
		merge(l->r, l->r, r), t = l;
	else
		merge(r->l, l, r->l), t = r;
	update(t);
}

void split(node *t, node *&l, node *&r, int key) {
	if (!t){
		l = r = NULL;
		return;
	}
	else if (key <= cnt(t->l)) 
		split(t->l, l, t->l, key), r = t;
	else 
		split(t->r, t->r, r, key - cnt(t->l) - 1), l = t;

	update(t);
}

void add(node *&t, node *it, int index) {
	if (!t)
		t = it;
	else if (it->prio < t->prio)
		split(t, it->l, it->r, index), t = it;
	else
		if (index <= cnt(t->l))
			add(t->l, it, index);
		else
			add(t->r, it, index - cnt(t->l) - 1);
	update(t);
}

void add(int index, int value) {
	node *it = &treap[t_cnt];
	it->value = value;
	it->prio = rnd[t_cnt];
	++t_cnt;
	it->cnt = 1;
	add(root, it, index);
}

void remove(node *&t, int index) {
	if (index == cnt(t->l))
		merge(t, t->l, t->r);
	else 
		if (index < cnt(t->l))
			remove(t->l, index);
		else
			remove(t->r, index - cnt(t->l) - 1);
	update(t);
}

void remove(int index) {
	remove(root, index);
}

void replace(node *&t, int index, int value) {
	if (index == cnt(t->l))
		t->value = value;
	else
		if (index < cnt(t->l))
			replace(t->l, index, value);
		else
			replace(t->r, index - cnt(t->l) - 1, value);
	update(t);
}

void replace(int index, int value) {
	replace(root, index, value);
}

int maxs(int a, int b) {
	node *l1, *r1;
	split(root, l1, r1, b + 1);
	node *l2, *r2;
	split(l1, l2, r2, a);
	int res = maxs(r2);
	node *t;
	merge(t, l2, r2);
	merge(root, t, r1);
	return res;
}


char buf1[1<<22];
int pos1;

char nextChar(){
	while (buf1[pos1] <= ' ') ++pos1;
	return buf1[pos1++];
}

int nextInt() {
	while (buf1[pos1] <= ' ') ++pos1;
	bool sign = false;
	if(buf1[pos1] == '-') {
		sign = true;
		++pos1;
	}
	int res = 0;
	while (buf1[pos1] > ' ') 
		res = res*10+(buf1[pos1++]&15);
	return sign ? -res : res;
}

char buf2[1<<22];
int pos2;

void writeInt(int x) {
	if(x<0){
		buf2[pos2++]='-';
		x=-x;
	}
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

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	#endif

	fread(buf1, 1, sizeof(buf1), stdin);

	int n=nextInt();

	vi a(n);
	rep(i,n)a[i]=nextInt();

	int q=nextInt();

	rep(i,n+q) rnd.push_back(i);
	random_shuffle(rnd.begin(), rnd.end());

	rep(i,n)add(i, a[i]);

	rep(i, q){
		char t = nextChar();
		int x,y;
		switch(t) {
			case 'I':
				x=nextInt();
				y=nextInt();
				add(x-1, y);
				break;
			case 'D':
				x=nextInt();
				remove(x-1);
				break;
			case 'R':
				x=nextInt();
				y=nextInt();
				replace(x-1, y);
				break;
			case 'Q':
				x=nextInt();
				y=nextInt();
				int res = maxs(x - 1, y - 1);
				writeInt(res);
				writeChar('\n');
				break;
		}
	}
	fwrite(buf2, 1, pos2, stdout);
}
