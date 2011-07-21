#include <cstdio>
#include <algorithm>

using namespace std;

struct entry {
	int h, w;
	bool operator<(const entry &o) const {
		if(h!=o.h)return h>o.h;
		return w<o.w;
	}
};

bool cmp_w(entry a, entry b) {
	return a.w<b.w;
}

#define MAX 5000

entry d[MAX];

int main() {
	freopen("input.txt","r",stdin);

	int t;
	scanf("%d", &t);

	while(t--){
		int n;
		scanf("%d", &n);
		for(int i=0;i<n;i++) scanf("%d%d", &d[i].w, &d[i].h);
		sort(d, d+n);

		int res=n;
		entry* last = d;

		for(int j=0;j<n;j++){
			entry *it = lower_bound(d, last, d[j], cmp_w);
			if(it != last) {
				--res;
				it->w = d[j].w;
			} else {
				*(last++) = d[j];
			}
		}

		while(--last<d) {
			if(last->h == (last-1)->h) --res;
		}

		printf("%d\n", res);
	}
}
