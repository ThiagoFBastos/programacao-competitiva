#include <bits/stdc++.h>

using namespace std;

using esquina = pair<int, int>;

struct cmp
{
	bool operator()(esquina a, esquina b)
	{
		return a.second > b.second;
	}
};

int main()
{
	int n, m;
	
	scanf("%d%d", &n, &m);
	
	auto Nout = new vector<esquina>[n];
	auto Nin = new vector<esquina>[n];
	auto custo = new int*[2];
	
	custo[0] = new int[n];
	custo[1] = new int[n];
	
	for(int k = 0; k < n; ++k)
		custo[0][k] = custo[1][k] = INT_MIN;
	
	int src1, dest1, src2, dest2;
	
	scanf("%d%d%d%d", &src1, &dest1, &src2, &dest2);
	
	--src1, --dest1, --src2, --dest2;
	
	for(int k = 0; k < m; ++k)
	{
		int u, v, cst;
		
		scanf("%d%d%d", &u, &v, &cst);
		
		--u, --v;
		
		Nout[u].push_back({v, cst});
		
		Nin[v].push_back({u, cst});
	}
	
	priority_queue<esquina, vector<esquina>, cmp> pq1, pq2;
	
	pq1.push({src1, 0});
	
	while(!pq1.empty())
	{
		int src, cst;
		
		src = pq1.top().first;
		cst = pq1.top().second;
		
		pq1.pop();	
		
		if(custo[0][src] == INT_MIN)
		{
			custo[0][src] = cst;
				
			if(src == dest1)
				break;
				
			for(auto edge : Nout[src])
			{
				int dest = edge.first;
				
				if(custo[0][dest] == INT_MIN)
					pq1.push({dest, cst + edge.second});
			}
		}	
	}
	
	pq2.push({src2, 0});
	
	while(!pq2.empty())
	{
		int src, cst;
		
		src = pq2.top().first;
		cst = pq2.top().second;
		
		pq2.pop();	
		
		if(custo[1][src] == INT_MIN)
		{
			custo[1][src] = cst;
			
			if(src == dest2)
				break;
					
			for(auto edge : Nout[src])
			{
				int dest = edge.first;
			
				if(custo[1][dest] == INT_MIN)
					pq2.push({dest, cst + edge.second});
			}
		}	
	}
	
	queue<int> Q1, Q2;
	bool **seen {new bool*[2]};
	
	seen[0] = new bool[n];
	seen[1] = new bool[n];
	
	for(int k = 0; k < n; ++k)
		seen[0][k] = seen[1][k] = true;
	
	Q1.push(dest1);
	
	seen[0][dest1] = false;
	
	while(!Q1.empty())
	{
		int dest = Q1.front();
			
		Q1.pop();
		
		if(dest == src1)
			continue;
			
		for(auto edge : Nin[dest])
		{
			int src = edge.first;
			
			if(seen[0][src] && custo[0][src] + edge.second == custo[0][dest])
			{
				seen[0][src] = false;
				Q1.push(src);
			}
		}
	}
	
	
	Q2.push(dest2);
	
	seen[1][dest2] = false;
	
	while(!Q2.empty())
	{
		int dest = Q2.front();
			
		Q2.pop();
		
		if(dest == src2)
			continue;
			
		for(auto edge : Nin[dest])
		{
			int src = edge.first;
			
			if(seen[1][src] && custo[1][src] + edge.second == custo[1][dest])
			{
				seen[1][src] = false;
				Q2.push(src);
			}
		}
	}
	
	int menor_custo = INT_MAX;
	
	for(int v = 0; v < n; ++v)
	{
		if(!seen[0][v] && !seen[1][v] && custo[0][v] == custo[1][v])
			menor_custo = min(menor_custo, custo[0][v]);
	}
	
	if(menor_custo == INT_MAX) 
		menor_custo = -1;
	
	printf("%d\n", menor_custo);
	
	return 0;
}