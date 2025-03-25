#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
#define f first
#define s second
#define EPS 1e-9
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned ui;
using vi = vector<int>;
using vvi = vector<vi>;
using ii = pair<int, int>;
using vii = vector<ii>;
#define MAXN 1000
int color[MAXN];
bool is_bipartite(vvi& G, int v) {
	for(int u : G[v]) {
		if(color[u] == 0) {
			color[u] = -color[v];
			if(!is_bipartite(G, u)) return false;
		}
		else if(color[u] == color[v]) return false;
	}
	return true;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    int t, T[MAXN][2];
    cin >> t;
    for(int c = 1; c <= t; ++c) {
        int n;
		cin >> n;
		vvi G(n);
		for(int k = 0; k < n; ++k) {
			color[k] = 0;
			cin >> T[k][0] >> T[k][1];
		}
		for(int k = 0; k < n; ++k) {
			for(int i = k + 1; i < n; ++i) {
				if(max(T[k][0], T[i][0]) < min(T[k][1], T[i][1])) {
					G[k].push_back(i);
					G[i].push_back(k);
				}
			}
		}
		bool flag = true;
		for(int k = 0; k < n; ++k) {
			if(color[k] == 0) {
				color[k] = 1;
				if(!is_bipartite(G, k)) {
					flag = false;
					break;
				}
			}
		}
		cout << "Case #" << c << ": ";
		if(flag) {
			string ans;
			for(int k = 0; k < n; ++k) {
				if(color[k] == 1) ans.push_back('J');
				else ans.push_back('C');
			}
			cout << ans << '\n';
		}
		else cout << "IMPOSSIBLE\n";
    }
	return 0;
}