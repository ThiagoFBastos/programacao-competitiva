#include <cstdio>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int main()
{
	int n, k, ganho;
	long long custo {};
	int *gramas, *precos;
	priority_queue<int, vector<int>, greater<int>> pq;

	scanf("%d%d", &n, &k);	

	gramas = new int[n];
	precos = new int[n];

	for(int i = 0; i < n; ++i)
		scanf("%d", gramas + i);

	scanf("%d", &ganho);

	for(int i = 0; i < n; ++i)
		scanf("%d", precos + i);

	for(int i = 0; i < n; ++i)
	{
		pq.push(precos[i]);

		if(gramas[i] > k)
		{
			int aumento = (1LLU * gramas[i] - k + ganho - 1) / ganho; 

			k += aumento * ganho;

			for(int j = 0; j < aumento; ++j)
			{
				if(pq.empty())
				{
					custo = -1;
					i = n;
					break;
				}

				custo += pq.top();
				pq.pop();
			}
		}
	}

	printf("%lld\n", custo);

	return 0;
}