#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5;
int n, t[MAXN], p[MAXN], res[MAXN], cycle_size[MAXN];
void dfs(int v) {
	if(cycle_size[v] != -1)
		res[v] = cycle_size[v];
	else {
		int u = t[v];
		if(res[u] == -1) dfs(u);
		res[v] = 1 + res[u];
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	bool vis[MAXN];
	cin >> n;
	for(int i = 0; i < n; ++i) {
		cin >> t[i];
		--t[i];
		vis[i] = false;
		res[i] = p[i] = cycle_size[i] = -1;
	}
	for(int v = 0; v < n; ++v) {
		if(p[v] == -1) {
			int u = v, k = 0;
			stack<int> S;
			while(true) {
				S.push(u);
				p[u] = k++;
				u = t[u];
				if(vis[u]) break;
				else if(p[u] != -1) {
					int w;
					do
					{
						w = S.top();
						S.pop();
						cycle_size[w] = k - p[u];
						vis[w] = true;
					} while(w != u);
					break;
				}
			}
			while(!S.empty()) {
				vis[S.top()] = true;
				S.pop();
			}
		}
	}
	for(int v = 0; v < n; ++v) if(res[v] == -1) dfs(v);
	for(int v = 0; v < n; ++v) cout << res[v] << ' ';
	cout << '\n';
	return 0;
}
