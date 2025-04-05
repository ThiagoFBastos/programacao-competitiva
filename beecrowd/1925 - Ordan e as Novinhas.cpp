#include <cstdio>
#include <vector>

using namespace std;

vector<int> novinhas;
int qnt_novinhas;
short n, m; 
int ** mapa {};

void dfs(int k, int j) {

	++qnt_novinhas;

	mapa[k][j] = novinhas.size();

	if(k && mapa[k - 1][j] == -2)
		dfs(k - 1, j);

	if(k < n - 1 && mapa[k + 1][j] == -2)
		dfs(k + 1, j);

	if(j && mapa[k][j - 1] == -2)
		dfs(k, j - 1);

	if(j < m - 1 && mapa[k][j + 1] == -2)
		dfs(k, j + 1);
}

bool not_in(vector<int> arr, int value) {

	for(int i = 0; i < arr.size(); ++i) {

		if(value == arr[i])
			return false;
	}

	return true;
}

int main() {

	short x, y;
	int max {0};

	scanf("%hd%hd", &n, &m);

	mapa = new int*[n];

	for(int i = 0; i < n; ++i) {

		char ch;

		mapa[i] = new int[m];

		getchar();

		for(int j = 0; j < m; ++j) {

			ch = getchar();

			if(ch == '*')
				mapa[i][j] = -1;

			else if(ch == 'n')
				mapa[i][j] = -2;

			else
				mapa[i][j] = -3;
		}
	}

	for(int i = 0; i < n; ++i) {

		for(int j = 0; j < m; ++j) {

			if(mapa[i][j] == -1) {

				int aplicacoes = 0;
				vector<int> pos;
				
				if(i) {

					if(mapa[i - 1][j] == -2) {

						qnt_novinhas = 0;

						dfs(i - 1, j);

						pos.push_back(novinhas.size());
						aplicacoes += qnt_novinhas;
						novinhas.push_back(qnt_novinhas);
					}

					else if(mapa[i - 1][j] >= 0) {

						pos.push_back(mapa[i - 1][j]);
						aplicacoes += novinhas[mapa[i - 1][j]];	
					}
				}

				if(i < n - 1) {

					if(mapa[i + 1][j] == -2) {

						qnt_novinhas = 0;

						dfs(i + 1, j);

						pos.push_back(novinhas.size());
						aplicacoes += qnt_novinhas;
						novinhas.push_back(qnt_novinhas);
					}

					else if(mapa[i + 1][j] >= 0 && not_in(pos, mapa[i + 1][j])) {

						pos.push_back(mapa[i + 1][j]);
						aplicacoes += novinhas[mapa[i + 1][j]];	
					}
				}

				if(j) {

					if(mapa[i][j - 1] == -2) {

						qnt_novinhas = 0;

						dfs(i, j - 1);

						pos.push_back(novinhas.size());
						aplicacoes += qnt_novinhas;
						novinhas.push_back(qnt_novinhas);
					}

					else if(mapa[i][j - 1] >= 0 && not_in(pos, mapa[i][j - 1])) {

						pos.push_back(mapa[i][j - 1]);
						aplicacoes += novinhas[mapa[i][j - 1]];	
					}
				}

				if(j < m - 1) {

					if(mapa[i][j + 1] == -2) {

						qnt_novinhas = 0;

						dfs(i, j + 1);

						pos.push_back(novinhas.size());
						aplicacoes += qnt_novinhas;
						novinhas.push_back(qnt_novinhas);
					}

					else if(mapa[i][j + 1] >= 0 && not_in(pos, mapa[i][j + 1])) {

						pos.push_back(mapa[i][j + 1]);
						aplicacoes += novinhas[mapa[i][j + 1]];	
					}
				}

				if(aplicacoes > max)
					x = j, y = i, max = aplicacoes;
			}
		}
	}

	printf("%hd,%hd\n", y + 1, x + 1);

	return 0;
}