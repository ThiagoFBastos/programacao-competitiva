#include <cstdio>
#include <queue>
#include <deque>
#include <cstring>

static std :: deque<int> *adj {};
static int *grau {};
static bool *acesso {};

static void componente(int[], int&, int);
static void componente(int, int&, int);

void componente(int C[], int& i, int k)
{
	acesso[k] = false;
	C[i++] = k;

	for(int w : adj[k])
	{
		if(acesso[w])
			componente(C, i, w);
	}
}

void componente(int prop, int& i, int k)
{
	acesso[k] = false;

	++i;

	for(int w : adj[k])
	{
		if(acesso[w] && grau[w] >= prop)
			componente(prop, i, w);
	}
}

int main()
{
	int n, p, k;
	
	while(true)
	{
		int *C;
		int tam {};

		scanf("%d%d%d", &n, &p, &k);

		if(!n)
			break;

		C = new int[n];

		adj = new std :: deque<int>[n];
		grau = new int[n];
		acesso = new bool[n];

		memset(acesso, 1, sizeof(bool) * n);
		memset(grau, 0, sizeof(int) * n);

		for(int i = 0; i < p; ++i)
		{
			int v1, v2;

			scanf("%d%d", &v1, &v2);

			--v1;
			--v2;

			++grau[v1];
			++grau[v2];

			adj[v1].push_back(v2);
			adj[v2].push_back(v1);
		}

		for(int i = 0; i < n; ++i)
		{
			if(acesso[i])
			{
				std :: queue<int> fila;
				int j = 0;

				componente(C, j, i);

				for(int i = j - 1; i >= 0; --i)
				{
					if(grau[C[i]] < k)
						fila.push(C[i]);
				}

				while(!fila.empty())
				{
					int src = fila.front();

					fila.pop();

					for(int w : adj[src])
					{
						if(grau[w] >= k && --grau[w] < k)
							fila.push(w);
					}
				}
			}
		}

		memset(acesso, 1, n * sizeof(bool));

		for(int i = 0; i < n; ++i)
		{
			if(acesso[i] && grau[i] >= k)
			{
				int j = 0;

				componente(k, j, i);

				if(j > tam)
					tam = j;
			}
		}

		printf("%d\n", tam);

		delete[] adj;
		delete[] grau;
		delete[] acesso;
		delete[] C;
	}

	return 0;
}