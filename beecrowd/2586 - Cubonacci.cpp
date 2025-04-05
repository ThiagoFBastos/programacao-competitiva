#include <cstdio>

using namespace std;

int main() {

	long long int x[9][3], a[9][3];
	int n;

	scanf("%d", &n);

	for(int i = 0; i < n; ++i) {

		int it;

		scanf("%d", &it);

		for(int k = 0; k < 9; ++k)
			for(int j = 0; j < 3; ++j)
				scanf("%lld", &x[k][j]);

		while(it--) {

			for(int k = 0; k < 9; ++k)
				for(int j = 0; j < 3; ++j)
					a[k][j] = x[k][j];

			for(int k = 0; k < 6; ++k) {

				for(int j = 0; j < 3; ++j) {

					x[k][j] += a[k + 3][j];

					if(k % 3) {

						x[k][j] += a[k - 1][j] + a[k + 2][j];

						if(j)
							x[k][j] += a[k - 1][j - 1] + a[k + 2][j - 1];

						if(j < 2)
							x[k][j] += a[k - 1][j + 1] + a[k + 2][j + 1];
					}

					if(j)
						x[k][j] += a[k][j - 1] + a[k + 3][j - 1];

					if(k % 3 < 2) {

						x[k][j] += a[k + 1][j] + a[k + 4][j];

						if(j)
							x[k][j] += a[k + 1][j - 1] + a[k + 4][j - 1];

						if(j < 2)
							x[k][j] += a[k + 1][j + 1] + a[k + 4][j + 1];
					}

					if(j < 2)
						x[k][j] += a[k][j + 1] + a[k + 3][j + 1];
				}
			}

			for(int k = 3; k < 6; ++k) {

				for(int j = 0; j < 3; ++j) {

					x[k][j] += a[k - 3][j];

					if(k > 3) {

						x[k][j] += a[k - 4][j];

						if(j)
							x[k][j] += a[k - 4][j - 1];
						if(j < 2) 
							x[k][j] += a[k - 4][j + 1];
					}

					if(j) 
						x[k][j] += a[k - 3][j - 1];

					if(k < 5) {

						x[k][j] += a[k - 2][j];

						if(j)
							x[k][j] += a[k - 2][j - 1];

						if(j < 2) 
							x[k][j] += a[k - 2][j + 1];
					}

					if(j < 2) 
						x[k][j] += a[k - 3][j + 1];
				}
			}

			for(int k = 6; k < 9; ++k) {

				for(int j = 0; j < 3; ++j) {

					x[k][j] += a[k - 3][j];

					if(k > 6) {

						x[k][j] += a[k - 1][j] + a[k - 4][j];

						if(j)
							x[k][j] += a[k - 1][j - 1] + a[k - 4][j - 1];

						if(j < 2) 
							x[k][j] += a[k - 1][j + 1] + a[k - 4][j + 1];
					}

					if(j) 
						x[k][j] += a[k][j - 1] + a[k - 3][j - 1];

					if(k < 8) {

						x[k][j] += a[k + 1][j] + a[k - 2][j];

						if(j)
							x[k][j] += a[k + 1][j - 1] + a[k - 2][j - 1];

						if(j < 2) 
							x[k][j] += a[k + 1][j + 1] + a[k - 2][j + 1];
					}

					if(j < 2) 
						x[k][j] += a[k][j + 1] + a[k - 3][j + 1];
				}
			}
		}

		for(int k = 0; k < 9; ++k) {

			for(int j = 0; j < 2; ++j)
				printf("%lld ", x[k][j]);
			printf("%lld\n", x[k][2]);
		}

	}

	return 0;
}