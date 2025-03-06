#include <cstdio>
#include <cmath>
#include <vector>

static std :: vector<int> calc_divisores(unsigned[], long long);

std :: vector<int> calc_divisores(unsigned primo[], long long n)
{
	std :: vector<int> divisores {1};

	if(!(n & 1))
	{
		long long power {2};

		do
		{
			divisores.emplace(divisores.end(), power);
			power <<= 1;

		} while(!(n & power - 1));

		n = (n << 1) / power;
	}

	for(int i = 0; primo[i] * primo[i] <= n; ++i)
	{
		if(n % primo[i] == 0)
		{
			long long power {primo[i]};
			size_t proc = divisores.size();

			do
			{

				for(int k = 0; k < proc; ++k)
					divisores.emplace(divisores.end(), power * divisores[k]);

				power *= primo[i];

			} while(n % power == 0);
			
			n = n * primo[i] / power;
		}
	}

	if(n > 1)
	{
		size_t proc = divisores.size();

		for(int k = 0; k < proc; ++k)
			divisores.emplace(divisores.end(), n * divisores[k]);
	}

	return divisores;
}

int main()
{
	unsigned primo[4792];
	int k = 3, i = 1;
	int p, q, casos;

	primo[0] = 3;	

	start:

	k += 2;

	if(i < 4792)
	{
		for(int j = 0; primo[j] * primo[j] <= k; ++j)
		{
			if(k % primo[j] == 0)
				goto start;
		}

		primo[i++] = k;
		goto start;
	}

	scanf("%d", &casos);

	for(k = 1; k <= casos; ++k)
	{
		long long X {0x100000000LL}, Y;

		scanf("%d%d", &p, &q);

		if(q)
		{
			std :: vector<int> divisores = calc_divisores(primo, q < 0 ? -1LL * q : q);

			for(int divisor : divisores)
			{
				long long y, x;

				x = q / divisor;
				y = x - divisor;

				if(X > x && (x + y) * y == p && x > y)
				{
					X = x;
					Y = y;
				}
				
				x *= -1;
				y = x - divisor;

				if(X > x && (x + y) * y == p)
				{
					X = x;
					Y = y;
				}
			}
		}

		else if(p >= 0)
		{
			int P = sqrt(p);

			if(P * P == p) 
			{
				X = 0;
				Y = -P;
			}

			P = sqrt(p >> 1);

			if(P * P << 1 == p)
			{
				X = -P;
				Y = -P;
			}			
		}

		printf("Case %d:\n", k);

		if(X > 32767 || Y > 32767 || X < -32768 || Y < -32768)
			puts("Impossible.");
		else
			printf("%hd %hd\n", (short)X, (short)Y);
	}

	return 0;
}