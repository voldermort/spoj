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
};

bool cmp_z(const entry1& a, const entry1& b)
{
	return a.z < b.z;
}

entry1 data1[100005];
entry data[100005];

struct cmp_x {
	bool operator() (int a, int b) const
	{
		return data[a].x < data[b].x;
	}
};

set<int,cmp_x> coastline;

// check inside coastline
bool inside(int i)
{
	set<int,cmp_x>::iterator it = coastline.lower_bound(i);
	if (it == coastline.begin())
		return false;
	return data[*--it].y < data[i].y;
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
		coastline.insert(0);

		vector<int> inner;

		for (int i = 1; i < n; i++)
		{
			if (inside(i)) continue;

			// got new excellent contestant
			++res;

			// check the points it covers
			inner.clear();
			for (set<int,cmp_x>::iterator it = coastline.lower_bound(i); it != coastline.end() && data[*it].y > data[i].y; it++)
				inner.push_back(*it);

			// delete the points it covers
			for (int j = 0; j < inner.size(); j++)
				coastline.erase(inner[j]);

			// insert this point
			coastline.insert(i);
		}
		printf("%d\n", res);
	}
}
