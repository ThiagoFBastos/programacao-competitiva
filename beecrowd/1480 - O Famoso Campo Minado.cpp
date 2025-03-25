#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;

#define MINA -2
#define DICA -3
#define COBERTO -1

int n, m, k, M[22][22], eh_mina[22][22];

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	for(; ;) {
		cin >> n >> m >> k;
		if(!(n || m || k)) break;
		memset(&M[0][0], 0, sizeof M);
		memset(&eh_mina[0][0], 0, sizeof eh_mina);
		for(int i = 1; i <= n; ++i) {
			char ch;
			for(int j = 1; j <= m; ++j) {
				cin >> ch;
				M[i][j] = isdigit(ch) ? ch - '0' : COBERTO;
			}
		}
		while(k--) {
			int a, b;
			cin >> a >> b;
			eh_mina[a][b] = 1;
		}
		for(int a = 1; a <= n * m; ++a) {
			for(int i = 1; i <= n; ++i) {
				for(int j = 1; j <= m; ++j) {
					if(M[i][j] >= 0) {
						int coberto = 0, mina = 0;
						for(int p = -1; p <= 1; ++p) {
							for(int q = -1; q <= 1; ++q) {
								if(M[i + p][j + q] == MINA) ++mina;
								else if(M[i + p][j + q] == COBERTO) ++coberto;
							}
						}
						if(mina == M[i][j]) {
							for(int p = -1; p <= 1; ++p)
								for(int q = -1; q <= 1; ++q)
									if(M[i + p][j + q] == COBERTO)
										M[i + p][j + q] = DICA;
						} 
						else if(coberto + mina == M[i][j]) {
							for(int p = -1; p <= 1; ++p)
								for(int q = -1; q <= 1; ++q)
									if(M[i + p][j + q] == COBERTO)
										M[i + p][j + q] = MINA;
						}
					}
				}
			}
			for(int i = 1; i <= n; ++i) {
				for(int j = 1; j <= m; ++j) {
					if(M[i][j] == DICA) {
						M[i][j] = 0;
						for(int p = -1; p <= 1; ++p)
							for(int q = -1; q <= 1; ++q)
								M[i][j] += eh_mina[i + p][j + q];
					}
				}
			}
		}
		bool ok = true;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j) if(M[i][j] == COBERTO) ok = false;
		cout << (ok ? "Possivel\n" : "Impossivel\n");
	}
	return 0;
}