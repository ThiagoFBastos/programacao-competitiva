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
const int maxn = 5150;
map<string, int> S;
int n, m, tipico[maxn], query[100];
vi G[maxn];
void dfs(int v) {
	if(tipico[v] != -1) return;
	tipico[v] = 0;
	for(int u : G[v]) {
		dfs(u);
		if(tipico[u] > G[u].size() / 2) ++tipico[v];
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	memset(query, -1, sizeof query);
	memset(tipico, -1, sizeof tipico);
	cin >> n;
	for(int i = 0; i < n; ++i) {
		string ing;
		cin >> ing;
		S[ing] = i;
		tipico[i] = 1;	
	}
	cin >> m;
	for(int l = 0; l < m; ++l) {
		string porcao;
		int k, i;
		cin >> porcao >> k;
		auto it = S.find(porcao);
		if(it == S.end()) i = S[porcao] = S.size();
		else i = it->second;
		query[l] = i;
		while(k--) {
			string ing;
			int j;
			cin >> ing;
			it = S.find(ing);
			if(it == S.end()) j = S[ing] = S.size();
			else j = it->second;
			G[i].push_back(j);
		}
	}
	for(int k = 0; k < S.size(); ++k) dfs(k);
	for(int l = 0; l < m; ++l) {
		int k = query[l];
		cout << (tipico[k] > G[k].size() / 2 ? "porcao tipica\n" : "porcao comum\n");
	}
	return 0;
}