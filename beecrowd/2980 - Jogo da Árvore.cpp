#include <cstdio>
#include <vector>
#include <utility>
#include <cstring>
#include <algorithm>
using namespace std;

class Tree
{
	private:

		vector<pair<int, int>> *edges;
		int *h, *points;
		int hmax;

		void dfs(int);

	public:

		Tree(int);

		void addEdge(int, int, int);

		int get_max_points(int, int);
};

Tree :: Tree(int v)
{

	edges = new vector<pair<int, int>>[v];

	h = new int[v];

	points = new int[v];

	memset(h, -1, v * sizeof(int));
}

void Tree :: addEdge(int v1, int v2, int cost)
{
	edges[v1].push_back({v2, cost});
	edges[v2].push_back({v1, cost});
}

int Tree :: get_max_points(int v, int hmax)
{
	this->hmax = hmax;

	h[v] = 0;

	dfs(v);

	return points[v];
}

void Tree :: dfs(int v1)
{
	points[v1] = 0;

	if(h[v1] < hmax - 1)
	{
		int max_points {};

		for(auto E : edges[v1])
		{
			int v2 = E.first;

			if(h[v2] == -1)
			{
				h[v2] = 1 + h[v1];

				dfs(v2);

				max_points = max(E.second + points[v2], max(max_points, (hmax - h[v1]) * E.second));
			}
		}

		points[v1] = max_points;
	}
}

int main()
{
	int n, hmax, start;

	scanf("%d", &n);

	Tree T(n);

	for(int k = 1; k < n; ++k)
	{
		int v1, v2, cost;

		scanf("%d%d%d", &v1, &v2, &cost);

		T.addEdge(v1 - 1, v2 - 1, cost);
	}

	scanf("%d%d", &hmax, &start);

	printf("%d", T.get_max_points(start - 1, hmax));

	return 0;
}