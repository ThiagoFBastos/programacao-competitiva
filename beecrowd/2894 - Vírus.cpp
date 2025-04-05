#include <bits/stdc++.h>

using namespace std;

static vector<int> *N;
static int *low, *pre, *pai, *pos, *ts, e, s; 
static vector<pair<int, int>> pontes;

static void dfs(int);

void dfs(int v)
{
	pre[v] = e++;
	low[v] = pre[v];
	ts[v] = 1;
	
	for(int w : N[v])
	{
		if(pre[w] == -1)
		{
			pai[w] = v;
			
			dfs(w);
			
			ts[v] += ts[w];
			
			if(pre[v] < low[w])
				pontes.push_back({v, w});
			
			low[v] = min(low[v], low[w]);
		}
		
		else if(w != pai[v])
			low[v] = min(low[v], pre[w]);
			
		else
			pai[v] = v;
	}
	
	pos[v] = s++;
}

int main()
{	
	int tests;
	
	ios_base :: sync_with_stdio(false);
	
	cin >> tests;
	
	while(tests--)
	{
		int V, E, id;
		
		cin >> V >> E >> id;
		
		N = new vector<int>[V];
		pre = new int[V];
		low = new int[V];
		ts = new int[V];
		pai = new int[V];
		pos = new int[V];
		
		for(int i = 0; i < V; ++i)
		{
			pre[i] = -1;
			pai[i] = -1;
			ts[i] = 0;
		}
		
		for(int i = 0; i < E; ++i)
		{
			int v1, v2;
			
			cin >> v1 >> v2;
			
			--v1;
			--v2;
			
			N[v1].push_back(v2);
			N[v2].push_back(v1);
		}
		
		e = s = 0;
		
		pai[0] = 0;
		
		dfs(0);
		
		--id;
		
		int iso = 0;

		for(auto [v1, v2] : pontes)
		{
			int X = V - ts[v2], Y = ts[v2];
		
			if(pre[id] >= pre[v2] && pos[v2] >= pos[id])
				iso = max(iso, X);
			
			else
				iso = max(iso, Y);
		}
		
		cout << iso << '\n';
		
		delete[] N;
		delete[] pre;
		delete[] low;
		delete[] ts;
		delete[] pai;
		delete[] pos;
		
		pontes.clear();
	}

	return 0;
}