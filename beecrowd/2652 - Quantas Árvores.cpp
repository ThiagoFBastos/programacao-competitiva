#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#include <numeric>

using namespace std;

class Tree
{
	private:

		vector<int> *neighbours;
		vector<int> C;
		
		string name1, name2;
		int *lv, *pa;
		int V, levels;

		void set_levels(int);

	public:

		Tree(int);

		void addEdge(int, int);
		vector<int> centro();

		void get_canonical_name();

		string canonical_name(int);

		static bool is_isomorphic(Tree, Tree);
};

Tree :: Tree(int V)
{
	this->V = V;

	lv = new int[V];
	pa = new int[V];

	neighbours = new vector<int>[V];
}

void Tree :: addEdge(int v1, int v2)
{
	neighbours[v1].push_back(v2);
	neighbours[v2].push_back(v1);
}

vector<int> Tree :: centro()
{
	queue<int> fila;
	vector<int> C;
	int degree[V], vida[V];

	memset(vida, -1, V * sizeof(int));

	for(int k = 0; k < V; ++k)
	{
		degree[k] = neighbours[k].size();

		if(degree[k] == 1)
		{
			vida[k] = 0;
			fila.push(k);
		}
	}

	while(!fila.empty())
	{
		int v = fila.front();

		fila.pop();

		for(int w : neighbours[v])
		{
			if(vida[w] == -1 && --degree[w] == 1)
			{
				vida[w] = 1 + vida[v];
				fila.push(w);
			}
		}
	}

	int vida_maxima {};

	for(int v = 0; v < V; ++v)
	{
		if(vida_maxima < vida[v])
			vida_maxima = vida[v];
	}

	for(int v = 0; v < V; ++v)
	{
		if(vida_maxima == vida[v])
			C.push_back(v);
	}

	return C;
}

void Tree :: set_levels(int v)
{
	for(int w : neighbours[v])
	{
		if(lv[w] == -1)
		{
			pa[w] = v;
			lv[w] = 1 + lv[v];
			levels = max(levels, lv[w]);

			set_levels(w);
		}
	}
}

bool Tree :: is_isomorphic(Tree t1, Tree t2)
{
	return t1.V == t2.V && t1.C.size() == t2.C.size() && (t1.name1 == t2.name1 || t1.name1 == t2.name2);
}

void Tree :: get_canonical_name()
{
	C = centro();
	
	levels = 0;

	memset(lv, -1, V * sizeof(int));

	lv[C[0]] = 0;

	set_levels(C[0]);

	++levels;

	name1 = canonical_name(C[0]);

	if(C.size() > 1)
	{
		levels = 0;
		
		memset(lv, -1, V * sizeof(int));

		lv[C[1]] = 0;

		set_levels(C[1]);

		++levels;

		name2 = canonical_name(C[1]);
	}
}

string Tree :: canonical_name(int root)
{
	string name[V];
	
	vector<int> *level = new vector<int>[levels];
	vector<string> *child_names = new vector<string>[V];		

	for(int v = 0; v < V; ++v)
	{
		level[lv[v]].push_back(v);

		if(lv[v] == levels - 1)
			name[v] = "10";
	}

	for(int k = levels - 2; k >= 0; --k)
	{
		for(int w : level[k + 1])
			child_names[pa[w]].push_back(name[w]);

		for(int w : level[k])
		{
			sort(child_names[w].begin(), child_names[w].end());
			name[w] = accumulate(child_names[w].begin(), child_names[w].end(), "1"s) + "0"s;
		}
	}


	delete[] child_names;
	delete[] level;

	return name[root];
}

int main()
{
	int n, count {};
	vector<Tree> trees;
	
	ios_base :: sync_with_stdio(false);
	
	cin >> n;

	int qu[n] = {0};

	for(int i = 0; i < n; ++i)
	{
		int m;

		cin >> m;

		Tree T(m);

		for(int j = 1; j < m; ++j)
		{
			int v;

			cin >> v;

			T.addEdge(v - 1, j);
		}

		T.get_canonical_name();

		trees.push_back(T);
	}

	qu[0] = 1;

	for(int k = 1; k < n; ++k)
	{
		qu[k] = 1;

		for(int j = k - 1; j >= 0; --j)
		{
			if(Tree :: is_isomorphic(trees[k], trees[j]))
			{
				qu[j] = 0;
				break;
			}
		}
	}

	for(int k = 0; k < n; ++k)
		count += qu[k];

	cout << count << '\n';

	
	return 0;
}