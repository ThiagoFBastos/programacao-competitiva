#include <iostream>
#include <string>
#include <queue>
#include <sstream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

class Tree
{
	private:

		vector<int> *neighbours;
		bool *seen;
		int V;

	public:

		Tree(int);
		~Tree();

		void addEdge(int, int);

		int vertex() const;

		string dfs(int);

		static const Tree create_tree(vector<int>);
};

Tree :: Tree(int V)
{
	this->V = V;

	seen = new bool[V] {0};
	neighbours = new vector<int>[V];
}

Tree :: ~Tree()
{
	delete[] seen;
	delete[] neighbours;
}

void Tree :: addEdge(int v1, int v2)
{
	neighbours[v1].push_back(v2);
	neighbours[v2].push_back(v1);
}

const Tree Tree :: create_tree(vector<int> seq)
{
	priority_queue<int, vector<int>, greater<int>> pq;

	int V = seq.size() + 1;

	int uso[V] = {0};
	

	for(int v : seq)
		++uso[v];

	for(int v = 0; v < V; ++v)
	{
		if(!uso[v])
			pq.push(v);
	}

	Tree t(V);

	for(int v : seq)
	{
		int w = pq.top();

		pq.pop();

		t.addEdge(v, w);

		if(--uso[v] == 0)
			pq.push(v);
	}

	int v1, v2;

	v1 = pq.top();

	pq.pop();

	v2 = pq.top();

	t.addEdge(v1, v2);

	return t;
}

string Tree :: dfs(int v)
{
	ostringstream os;

	os << "(" << v + 1;

	seen[v] = true;

	for(int w : neighbours[v])
	{
		if(!seen[w])
			os << " " << dfs(w);
	}

	os << ")";

	return os.str();
}

int Tree :: vertex() const
{
	return V;
}

int main()
{
	string entrada;

	ios_base :: sync_with_stdio(false);

	while(getline(cin, entrada))
	{
		istringstream is(entrada);
		vector<int> prufer_sequence;
		int v;

		while(is >> v)
			prufer_sequence.push_back(v - 1);

		Tree t = Tree :: create_tree(prufer_sequence);

		cout << t.dfs(t.vertex() - 1) << '\n';
	}
		
	return 0;
}