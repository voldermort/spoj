#include <cstdio>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

struct entry
{
	int x, y;
	bool operator<(const entry& o) const
	{
		if (x!=o.x) return x < o.x;
		return y < o.y;
	}
};

#define N 100000

int x[N], y[N];
set<entry> chains[N + 1];


int main() {
	//freopen("input.txt", "r", stdin);

	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%d%d", &x[i], &y[i]);

	int res = 0;

	for(int i=0; i<n; i++) {
		entry e;
		e.x = x[i];
		e.y = -2000000000;

		int lo = 0, hi = res + 1;

		while (hi - lo > 1) {
			int mid = (lo + hi) / 2;

			set<entry>& antichain = chains[mid];
			set<entry>::iterator it = antichain.lower_bound(e);

			if (it != antichain.begin() && (--it)->y < y[i]) 
				lo = mid; 
			else 
				hi = mid;
		}

		if (lo == res) ++res;
		set<entry>& antichain = chains[lo + 1];
		set<entry>::iterator it = antichain.lower_bound(e);

		if (it != antichain.end() && it->x == x[i] && it->y <= y[i])
				continue;

		e.y = y[i];
		it = antichain.insert(e).first;

		set<entry>::iterator it2 = ++it;
		for(; it2 != antichain.end() && it2->y >= y[i]; ++it2);
		antichain.erase(it, it2);
	}

	printf("%d\n", res);
}
