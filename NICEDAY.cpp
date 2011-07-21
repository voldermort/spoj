#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

struct entry
{
	int x, y, z;
	bool operator<(const entry& o) const
	{
		return x < o.x;
	}
};

bool cmp_z(const entry& a, const entry& b)
{
	return a.z < b.z;
}

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
		for (int i = 0; i < n; i++) scanf("%d%d%d", &data[i].x, &data[i].y, &data[i].z);
		sort(data, data+n, cmp_z);
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
			inner.clear();
			for (set<entry>::iterator it = coastline.lower_bound(data[i]); it != coastline.end() && it->y > data[i].y; it++)
				inner.push_back(*it);

			// delete the points it covers
			for (int i = 0; i < inner.size(); i++)
				coastline.erase(inner[i]);

			// insert this point
			coastline.insert(data[i]);
		}
		printf("%d\n", res);
	}
}
