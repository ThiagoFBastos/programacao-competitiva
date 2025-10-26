#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree<T ,  null_type , less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

int n, id = 1;
vector<vector<int>> g;
vector<int> val;
vector<i64> inv;
vector<ordered_set<int>> A;

void dfs() {

	stack<ii> st;
	
	st.emplace(0, 0);
	
	while(!st.empty()) {
		auto [u, f] = st.top();
		
		st.pop();
		
		if(val[u] != -1) {
			A[u].insert(val[u]);
			continue;
		}
		
		if(f > 0) {
			int v = g[u][f - 1];
			
			inv[u] += inv[v];
			
			if(A[v].size() > A[u].size()) A[u].swap(A[v]);
			
			i64 e = 0, d = 0;
			
			for(int x : A[v]) {
				int cnt = A[u].order_of_key(x);
				e += cnt;
				d += (int)A[u].size() - cnt;
			}
			
			inv[u] += min(e, d);
			
			while(!A[v].empty()) {
				A[u].insert(*A[v].begin());
				A[v].erase(A[v].begin());
			}
		}
		
		if(f < (int)g[u].size()) {
			st.emplace(u, f + 1);
			st.emplace(g[u][f], 0);
		}
	}
}

void solve() {	
	cin >> n;
	
	vector<int> a;
	
	while(true) {
		int x;
		cin >> x;
		if(cin.eof()) break;
		a.push_back(x);
	}
	
	g.resize(size(a) + 1);
	val.assign(size(a) + 1, -1);
	A.resize(size(a) + 1);
	inv.resize(size(a) + 1);
	
	stack<ii> st;
	
	st.emplace(0, 0);
	
	for(int x : a) {
		g[st.top().first].push_back(id);
		++st.top().second;
		if(x == 0) st.emplace(id, 0);
		else {
			val[id] = x;
			while(!st.empty() && st.top().second == 2) st.pop();
		}
		++id;
	}
	
	dfs();
	
	cout << inv[0] << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
