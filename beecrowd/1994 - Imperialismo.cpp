#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

class Graph
{
	std :: vector<int> *adj;
	int *d;
	int V;

	public:

		Graph(int);
		~Graph();
		void add_edge(int, int);
		int center();
};

Graph :: Graph(int v)
{
	adj = new std :: vector<int>[v];
	d = new int[v];
	V = v;

	memset(d, 0, v * sizeof(int));
}

Graph :: ~Graph()
{
	delete[] adj;
}

void Graph :: add_edge(int v1, int v2)
{
	adj[v1].push_back(v2);
	adj[v2].push_back(v1);

	++d[v1];
	++d[v2];
}

int Graph :: center()
{
	int *time {new int[V]};
	std :: queue<int> fila;
	int centro {}, k = 0;

	memset(time, -1, V * sizeof(int));

	for(int i = 0; i < V; ++i)
	{
		if(d[i] == 1)
		{
			time[i] = 0;
			fila.push(i);
		}
	}

	while(!fila.empty())
	{
		int w = fila.front();

		fila.pop();

		for(int u : adj[w])
		{
			if(time[u] == -1 && --d[u] == 1)
			{
				time[u] = 1 + time[w];
				fila.push(u);
			}
		}
	}

	for(int i = 0; i < V; ++i)
	{
		if(centro < time[i])
			centro = time[i];
	}

	for(int i = 0; i < V; ++i)
	{
		if(centro == time[i])
			++k;
	}

	delete[] time;

	return centro + k - 1;
}

static void read(int&);

void read(int& n)
{
	register int ch {getchar_unlocked()};

	while(ch < 48)
		ch = getchar_unlocked();

	n ^= n;

	while(ch > 47)
	{
		n = (n << 3) + (n << 1) + ch - 48;
		ch = getchar_unlocked();
	}
}

int main()
{
	int n;

	while(true)
	{
		scanf("%d", &n);

		if(n < 0)
			break;

		Graph grafo(n);

		for(int i = 1; i < n; ++i)
		{
			int v;

			read(v);
			grafo.add_edge(i, v - 1);
		}

		printf("%d\n", grafo.center());
	}

	return 0;
}
