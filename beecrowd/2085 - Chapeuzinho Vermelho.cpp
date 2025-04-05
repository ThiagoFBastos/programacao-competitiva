#include <bits/stdc++.h>

using namespace std;

static vector<int> *N;
static long long *caminhos, *melhor_caminho;

static void dfs(int);

void dfs(int v)
{
	caminhos[v] = 0;
	
	for(int w : N[v])
	{
		if(caminhos[w] == -1)
			dfs(w);
			
		if(caminhos[w] != -1)
		{
			melhor_caminho[v] = max(melhor_caminho[v], melhor_caminho[w]);
			caminhos[v] += caminhos[w];
		}
	}
	
	melhor_caminho[v] += caminhos[v];
}

int main()
{
	int n, m;
	
	scanf("%d%d", &n, &m);
	
	N = new vector<int>[n];
	caminhos = new long long[n];
	melhor_caminho = new long long[n];
	
	memset(caminhos, -1, n * sizeof(long long));
	memset(melhor_caminho, -1, n * sizeof(long long));
	
	caminhos[n - 1] = melhor_caminho[n - 1] = 1;
	
	for(int k = 0; k < m; ++k)
	{
		int u, v;
		
		scanf("%d%d", &u, &v);
		
		N[u - 1].push_back(v - 1);
	}
	
	dfs(0);
	
	printf("%lld\n", melhor_caminho[0]);
	
	return 0;
}