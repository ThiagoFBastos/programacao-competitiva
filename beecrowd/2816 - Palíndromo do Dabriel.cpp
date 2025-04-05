#include <cstdio>
#include <vector>
#include <deque>
#include <cstring>

#define MOD 1000000007

static std :: vector<int> *neighbours;
static char *string;
static bool *is_open;
static int *contagem;

static void dfs(int);

void dfs(int v)
{
	is_open[v] = false;

	for(int w : neighbours[v])
	{
		if(is_open[w])
		{
			contagem[w] = string[w] == '*' || string[w] == string[v];
			string[w] = string[v];
			dfs(w);
		}
	}
}

int main(void)
{
	int n, c, resposta = 1;

	std :: deque<int> ordem;

	scanf("%d%d", &n, &c);

	neighbours = new std :: vector<int>[n];
	contagem = new int[n];
	string = new char[n + 1];
	is_open = new bool[n];

	memset(is_open, 1, n * sizeof(bool));

	scanf("%s", string);

	for(int k = 0; k < n; ++k)
	{
		if(string[k] == '*')
		{
			ordem.push_back(k);
			contagem[k] = 26;
		}

		else
		{
			ordem.push_front(k);
			contagem[k] = 1;
		}
	}

	for(int k = 0; k < n / 2; ++k)
	{
		int i = n - k - 1;

		neighbours[k].push_back(i);
		neighbours[i].push_back(k);
	}
	
	for(int k = 0; k < c; ++k)
	{
		int v1, v2;

		scanf("%d%d", &v1, &v2);

		--v1;
		--v2;

		if(n - v1 - 1 != v2)
		{
			neighbours[v1].push_back(v2);
			neighbours[v2].push_back(v1);
		}
	}

	for(int v : ordem)
	{
		if(is_open[v])
			dfs(v);

		resposta = 1LL * resposta * contagem[v] % MOD;
	}

	printf("%d\n", resposta);

	return 0;
}