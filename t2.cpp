#include <assert.h> 
#include <ctype.h> 
#include <float.h> 
#include <math.h> 
#include <stdio.h> 
#include <string> 
#include <stdlib.h> 
#include <time.h> 
#include <algorithm> 
#include <numeric> 
#include <functional> 
#include <utility> 
#include <vector> 
#include <list> 
#include <set> 
#include <map> 
#include <queue> 
#include <stack> 
#include <sstream> 
#include <iostream> 
#include <memory.h>

using namespace std; 

const int MAX_SIZE = 20000;
static char input[MAX_SIZE];
struct Scanner
{
#if 1
	Scanner()
	{
		int sz = fread(input, 1, sizeof(input), stdin);
		curPos = input;
	}
	int nextInt()
	{
		int gap = input + MAX_SIZE - curPos;
		if (gap < 100)
		{
			memcpy(input, curPos, gap);
			fread(input + gap, 1, sizeof(input) - gap, stdin);
			curPos = input;

		}
		while (*curPos < '0') curPos++;

		int res = 0;
		while (*curPos >= '0') 
		{
			res = res * 10 + (*curPos) - '0';
			curPos++;
		}
		return res;
	}
	char* curPos;
#else
	int nextInt()
	{
		int a;
		scanf("%d", &a);

		return a;
	}
#endif


};

int N;

struct Graph
{
	int head[100000];
	int next[200000];
	int dest[200000];
};

Graph ga, gb;

void readGraph(Scanner& sc, Graph& g)
{
	fill(g.head, g.head + N, -1);

	int edge = 0;
	for (int i = 0; i < N - 1; i++)
	{
		int u = sc.nextInt() - 1;
		int v = sc.nextInt() - 1;

		g.next[edge] = g.head[u];
		g.dest[edge] = v;
		g.head[u] = edge++;

		g.next[edge] = g.head[v];
		g.dest[edge] = u;
		g.head[v] = edge++;
	}
}


int dfs(Graph& g, int v, int p, vector<int>& c)
{
	int res = 1;
	for (int j = g.head[v]; j != -1; j = g.next[j])
	{
		int t = g.dest[j];
		if (t == p)
			continue;

		res += dfs(g, t, v, c);
	}

	if (c[0] == -1 && res >= N / 2 + 1 )
	{
		c[0] = v;
	}

	if (res * 2 == N)
	{
		c[1] = v;
	}

	return res;
}

void findCenter(Graph& g, vector<int>& c)
{
	c.assign(2, -1);
	dfs(g, 0, -1, c);

	if (c[0] == c[1] || c[1] == -1)
		c.resize(1);
}

typedef int lhash;
lhash l[100000];
lhash h[100000];

lhash getHash(Graph& g, int v, int p)
{ 
	for (int j = g.head[v]; j != -1; j = g.next[j])
	{
		int t = g.dest[j];
		if (t == p)
			continue;

		l[t] = getHash(g, t, v);
	}

	int hSize = 0;
	for (int j = g.head[v]; j != -1; j = g.next[j])
	{
		int t = g.dest[j];
		if (t == p)
			continue;

		h[hSize++] = l[t];
	}
	sort(h, h + hSize);

	lhash res = 1;

	for (int i = 0; i < hSize; i++)
	{
		res = res * 311177 + h[i];
	}
	res = res * 311171 + (hSize + 1);

	return res;
}

void Generate()
{
	srand(time(0));
	int T = 200;

	printf("%d\n", T);

	while (T--)
	{
		int N = rand() % 10 + 1;
		printf("%d\n", N);

		vector<int> parent(N, -1);
		for (int i = 1; i < N; i++)
			parent[i] = rand() % i;

		vector<int> o(N);
		for (int i = 0; i < N; i++) 
			o[i] = i;

		random_shuffle(o.begin(), o.end());

		for (int i = 1; i < N; i++)
		{
			printf("%d %d\n", o[i] + 1, o[parent[i]] + 1);
		}

		random_shuffle(o.begin(), o.end());

		for (int i = 1; i < N; i++)
		{
			printf("%d %d\n", o[i] + 1, o[parent[i]] + 1);
		}

	}
}

int main(int argc, char* argv[])
{
#ifndef ONLINE_JUDGE
	freopen("test.in", "r", stdin);
#endif


	//Generate();
	//return 0;

	Scanner sc;

	int T = sc.nextInt();
	while (T--)
	{
		N = sc.nextInt();
		assert (N >= 1 && N <= 100000);

		readGraph(sc, ga);
		readGraph(sc, gb);

		vector<int> ca, cb;

		findCenter(ga, ca);
		findCenter(gb, cb);

		bool same = false; 
		lhash ha[2] = {-1, -1};

		for (int j = 0; j < cb.size() && !same; j++)
		{
			lhash hb = getHash(gb, cb[j], -1);

			for (int i = 0; i < ca.size(); i++)
			{		
				if (ha[i] == -1)
				{
					ha[i] = getHash(ga, ca[i], -1);
				}

				if (ha[i] == hb)
				{
					same = true;
					break;
				}
			}
		}

		printf("%s\n", same ? "YES" : "NO");

	}

	return 0;
}

