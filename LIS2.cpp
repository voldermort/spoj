#include <cstdio>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

#define N 100000
typedef map<int, int>  MII;

int x[N], y[N];
MII chains[N+1];


int main() {
	//freopen("input.txt","r",stdin);

	int n;
	scanf("%d", &n);
	for(int i=0;i<n;i++) scanf("%d%d",&x[i],&y[i]);

	int res = 0;

	for(int i=0;i<n;i++) {
		int X = x[i], Y = y[i];

		int lo = 0, hi = res+1;

		while (hi - lo > 1) {
			int mid = (lo + hi) >> 1;

            MII& antichain = chains[mid];
            MII::iterator it = antichain.lower_bound(X);

	        if (it != antichain.begin() && (--it)->second < Y) 
				lo = mid; 
			else 
				hi = mid;
        }

		if (lo == res) ++res;
        MII& antichain = chains[lo + 1];
        MII::iterator it = antichain.lower_bound(X);

        if (it != antichain.end() && it->first == X) 
			if(it->second > Y) 
				it->second = Y;
			else 
				continue;
        else 
			it = antichain.insert(pair<int,int>(X,Y)).first;
        

        MII::iterator it2 = ++it;
        while(it2 != antichain.end() && it2->second >= Y) ++it2;
        antichain.erase(it, it2);
	}

    printf("%d\n", res);
}
