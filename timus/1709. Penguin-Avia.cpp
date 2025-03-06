#include <bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2")

#define f first
#define s second

using namespace std;

typedef long long ll;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;

#define MAXN 100

class UnionFind {

	vi rank, pa;

	public:

	UnionFind() {


	}

	UnionFind(int n) {

		rank.resize(n);
		pa.resize(n);

		for(int v = 0; v < n; ++v)
			pa[v] = v, rank[v] = 0;		
	}

	int findSet(int v) {
		return v == pa[v] ? v : pa[v] = findSet(pa[v]);
	}

	void link(int v1, int v2) {
		if(rank[v1] < rank[v2]) pa[v1] = v2;
		else {
			pa[v2] = v1;
			if(rank[v1] == rank[v2]) ++rank[v1];
		}
	}
};

UnionFind S;

int G[MAXN][MAXN], M[MAXN][MAXN], n;
bool ac[MAXN];

void dfs(int v) {

	ac[v] = false;

	for(int k = 0; k < n; ++k) {

		if(G[v][k] && ac[k]) {

			S.link(S.findSet(v), S.findSet(k));
			M[v][k] = M[k][v] = 1;
			
			dfs(k);
		}
	}
}

int main() {
  
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int a, b;

	cin >> n >> a >> b;

	for(int k = 0; k < n; ++k) {

		ac[k] = true;

		for(int i = 0; i < n; ++i) {

			M[k][i] = 0;
			G[k][i] = 0;
		}
	}

	for(int k = 0; k < n; ++k) {

		cin.ignore();

		for(int i = 0; i < n; ++i) {

			char c;

			cin >> c;
		
			G[k][i] = c - '0';
		}
	}

	S = UnionFind(n);
	
	for(int k = 0; k < n; ++k) {

		if(ac[k])
			dfs(k);
	}

	ll c = 0;

	for(int k = 0; k < n; ++k){

		for(int j = 0; j < n; ++j)
			if(G[k][j] && !M[k][j]) {c += a; M[k][j] = -1;}
	}

	c /= 2;

	for(int k = 0; k < n; ++k) {

		int u = S.findSet(k);

		for(int j = k + 1; j < n; ++j) {

			int v = S.findSet(j);

			if(u != v) { 

				c += b;
				M[k][j] = M[j][k] = 2;
				S.link(u, v);
			}
		} 
	}

	cout << c << '\n';

	for(int k = 0; k < n; ++k) {
		for(int j = 0; j < n; ++j) {
			if(M[k][j] == 0 || M[k][j] == 1) cout << 0;
			else if(M[k][j] == -1) cout << 'd';
			else cout << 'a';
		}
		cout << '\n';
	}
    return 0;
}