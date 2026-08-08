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
const int maxn = 2e5;
int c[maxn], n, m;
vi g[maxn];
bool ok = true;
void solve();
int calc();
void solve() {
	if(!ok) return;
	vi vis(n, -1);
	for(int v = 0; v < n; ++v) {
		if(c[v] != -1 && vis[v] == -1) {
			queue<int> S;
			S.push(v);
			vis[v] = 1;
			while(!S.empty()) {
				int u = S.front();
				S.pop();
				for(int v : g[u]) {
					if(c[v] == -1) {
						vis[v] = 1;
						c[v] = 1 ^ c[u];
						S.push(v);
					} else if(c[v] == c[u]) {
						ok = false;
						return;
					}
				}
			}
		}
	}
}
int calc() {
	if(!ok) return 0;
	vi C(n, -1);
	int res = 0;
	for(int v = 0; v < n; ++v) {
		if(c[v] == -1 && C[v] == -1) {
			queue<int> S;
			int z = 0, o = 0;
			S.push(v);
			C[v] = 0;
			while(!S.empty()) {
				int u = S.front();
				S.pop();
				if(C[u]) ++o;
				else ++z;
				for(int w : g[u]) {
					if(C[w] == -1) {
						C[w] = C[u] ^ 1;
						S.push(w);
					} else if(C[w] == C[u]) {
						ok = false;
						return 0;
					}
				}
			}
			res += min(z, o);
		}
	}
	return res;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int res = 0;
	cin >> n >> m;
	memset(c, -1, n * sizeof(int));
	for(int i = 0; i < m; ++i) {
		int a, b, r;
		cin >> a >> b >> r;
		--a, --b;
		if(r == 2) {
			if(c[a] == 0 || c[b] == 0) 
				ok = false;
			else 
				c[a] = c[b] = 1;	
		} else if(r == 0) {
			if(c[a] == 1 || c[b] == 1) 
				ok = false;
			else
				c[a] = c[b] = 0;
		} else {	
			g[a].push_back(b);
			g[b].push_back(a);
		}
	}
	solve();	
	for(int v = 0; v < n; ++v) if(c[v] == 1) ++res;
	res += calc();
	if(ok) cout << res << '\n';
	else cout << "impossible\n";
	return 0;
}