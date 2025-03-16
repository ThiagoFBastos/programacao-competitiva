#pragma GCC target("sse,mmx,sse2")
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

const int maxn = 2e5, mod = 1e9 + 7;

int dp[maxn][2], n, cnt, cur[maxn], pai[maxn], a[maxn];
vi t[maxn];

ll exp_mod(int, int);
void tour();
void dfs();

ll exp_mod(int n, int p) {
	ll res = 1;
	while(p > 0) {
		if(p & 1) res = res * n % mod;
		n = 1ll * n * n % mod;
		p >>= 1;
	}
	return res;
}

void tour() {
	for(int i = 0; i < n; ++i) {
		cur[i] = t[i].size();
		pai[i] = -1;
	}
	stack<int> S;
	pai[0] = 0;
	S.push(0);
	while(!S.empty()) {
		int u = S.top();
		S.pop();
		while(--cur[u] >= 0) {
			int v = t[u][cur[u]];
			if(pai[u] == v) continue;
			pai[v] = u;
			S.push(u);
			S.push(v);	
			break;				
		}
		if(cur[u] < 0) {
			bool folha = true;
			int a = 1;
			for(int v : t[u]) {
				if(v == pai[u]) continue;
				folha = false;
				a = 1ll * a * dp[v][0] % mod;
			}
			if(folha) 
				dp[u][0] = dp[u][1] = 1;
			else {
				a <<= 1;
				if(a >= mod) a -= mod;
				dp[u][0] = dp[u][1] = a;
			}
		}
	}
}

void dfs() {
	for(int i = 0; i < n; ++i)
		cur[i] = t[i].size();
	stack<int> S;
	S.push(0);
	while(!S.empty()) {
		int u = S.top();
		S.pop();
		if(cur[u] == (int)t[u].size()) {
			a[u] = 1;
			for(int v : t[u]) a[u] = 1ll * a[u] * dp[v][0] % mod;
			a[u] <<= 1;
			if(a[u] >= mod) a[u] -= mod;
			if(t[u].empty()) ++cnt;
			else cnt += a[u];
			if(cnt >= mod) cnt -= mod;
		}
		while(--cur[u] >= 0) {
			int v = t[u][cur[u]];
			if(v == pai[u]) continue;
			int A = a[u] * exp_mod(2 * dp[v][0], mod - 2) % mod;
			if(t[u].size() == 1u) dp[u][0] = dp[u][1] = 1;
			else {
				A <<= 1;
				if(A >= mod) A -= mod;
				dp[u][0] = dp[u][1] = A;
			}
			S.push(u);
			S.push(v);
			break;
		}
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		t[a].push_back(b);
		t[b].push_back(a);
	}
	tour();
	dfs();
	cout << cnt << '\n';
	return 0;
}