#pragma GCC optimize("O3")
#pragma GCC target("mmx", "sse", "sse2", "sse3", "sse4", "avx")

#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree<T,  null_type , less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

int n, q;
vector<ordered_set<int>> S;
vector<int> id;

void merge(int a, int b) {
	if(S[a].size() > S[b].size()) swap(a, b);
	id[n++] = b;
	for(int val : S[a]) S[b].insert(val);
}

void solve() {
	cin >> n >> q;
	
	S.resize(n);
	id.resize(n + q);
	
	for(int i = 0; i < n; ++i) {
		id[i] = i;
		S[i].insert(i + 1);
	}
	
	while(q--) {
		string t;
		int a, b;
		cin >> t >> a >> b;
		--a, --b;
		if(t == "GET") cout << *S[id[a]].find_by_order(b) << '\n';
		else merge(id[a], id[b]);
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}