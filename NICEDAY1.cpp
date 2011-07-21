#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

struct entry1
{
	int x, y, z;
};

struct entry
{
	int x, y;
	bool operator<(const entry& o) const
	{
		return x < o.x;
	}
};

bool cmp_z(const entry1& a, const entry1& b)
{
	return a.z < b.z;
}

entry1 data1[100005];
entry data[100005];

set<entry> coastline;

// check inside coastline
bool inside(int i)
{
	set<entry>::iterator it = coastline.lower_bound(data[i]);
	if (it == coastline.begin())
		return false;
	return (--it)->y < data[i].y;
}

int main()
{
	//freopen("input.txt","r",stdin);

	int t;
	scanf("%d", &t);
	while (t--)
	{
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%d%d%d", &data1[i].x, &data1[i].y, &data1[i].z);
		sort(data1, data1+n, cmp_z);
		for (int i = 0; i < n; i++) data[i].x=data1[i].x,data[i].y=data1[i].y;
		coastline.clear();

		// first contestant is excellent
		int res = 1;
		coastline.insert(data[0]);

		vector<entry> inner;

		for (int i = 1; i < n; i++)
		{
			if (inside(i)) continue;

			// got new excellent contestant
			++res;

			// check the points it covers
			set<entry>::iterator it1 = coastline.lower_bound(data[i]);
			set<entry>::iterator it2 = it1;
			for (; it2 != coastline.end() && it2->y > data[i].y; it2++);

			// delete the points it covers
			coastline.erase(it1, it2);

			// insert this point
			coastline.insert(data[i]);
		}
		printf("%d\n", res);
	}
}
