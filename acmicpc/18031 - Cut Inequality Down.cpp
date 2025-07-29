#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;

template<bool roll = false>
struct uf {
	vector<int> par, rank, sz;
	vector<tuple<int, int, int>> stackUPD;

	uf() {}

	uf(int n) {
		par.resize(n);
		rank.assign(n, 0);
		sz.assign(n, 1);
		iota(par.begin(), par.end(), 0);
	}
	
	int findSet(int v) {
		if constexpr(roll)
			return v == par[v] ? v : par[v] = findSet(par[v]);
		else
			return v == par[v] ? v : findSet(par[v]);
	}

	bool same(int a, int b) {
		return findSet(a) == findSet(b);
	}
	
	bool join(int a, int b) {
		a = findSet(a);
		b = findSet(b);

		if(a == b) return false;
		else if(rank[a] > rank[b]) swap(a, b);
		
		if constexpr(roll)
			stackUPD.emplace_back(a, b, rank[b]);

		par[a] = b;
		rank[b] += rank[a] == rank[b];
		sz[b] += sz[a];

		return true;
	}

	bool rollback() {
		if constexpr(roll) {
			if(stackUPD.empty()) return false;
			int u, v, r;
			tie(u, v, r) = stackUPD.back();
			stackUPD.pop_back();
			sz[v] -= sz[u];
			par[u] = u;
			rank[v] = r;
			return true;
		} else
			return false;
	}
};

void solve() {
	int n, l, u, q;
	
	cin >> n >> l >> u;
		
	vector<int> a(n);
	map<ii, int> mp;
	
	for(int& v : a) cin >> v;

	cin >> q;

	vector<tuple<int, int, int>> in(q);
	vector<tuple<int, int, int, int>> out(q);
	
	for(int i = 0; i < q; ++i) {
		int lo, hi, x;
		cin >> lo >> hi >> x;
		--lo, --hi;
		in[i] = {lo, x, i};
		out[i] = {hi, x, i, lo};
		if(!mp.count({x,lo})) mp[{x,lo}] = mp.size();
	}

	uf dsu(mp.size());
	set<pair<i64, int>> st;
	i64 ad = 0;
	vector<i64> value(mp.size()), ans(q);

	sort(rall(in));
	sort(rall(out));

	for(int i = 0; i < n; ++i) {

		while(!in.empty()) {
			auto [lo, x, k] = in.back();
			if(lo != i) break;
			in.pop_back();
			int j = mp[{x, lo}];
			value[j] = x - ad;
			st.emplace(x - ad, j);
		}

		ad += a[i];

		if(auto it = st.lower_bound(make_pair(u - ad + 1, -1)); it != st.end()) {
			int f = it->sc;
			while(it != st.end()) {
				dsu.join(f, it->sc);
				it = st.erase(it);
			}
			value[dsu.findSet(f)] = u - ad;
			st.emplace(u - ad, dsu.findSet(f));
		}

		if(!st.empty() && st.begin()->fi + ad < l) {
			int f = st.begin()->sc;
			auto it = st.begin();
			while(it != st.end() && it->fi + ad < l) {
				dsu.join(f, it->sc);
				it = st.erase(it);
			}
			value[dsu.findSet(f)] = l - ad;
			st.emplace(l - ad, dsu.findSet(f));
		}

		while(!out.empty()) {
			auto [hi, x, k, lo] = out.back();
			if(hi != i) break;
			out.pop_back();
			ans[k] = value[dsu.findSet(mp[{x, lo}])] + ad;
		}
	}

	for(i64 v : ans) cout << v << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}