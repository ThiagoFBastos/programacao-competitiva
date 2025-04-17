#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

struct my_struct {
	char type;
	int a, av;	
	int b, bv;
	int p, pv;
	int e, ev;
	my_struct() {}
};

my_struct add(int p, int pv, int e, int ev) {
	my_struct d;
	d.type = 'I', d.p = p, d.pv = pv, d.e = e, d.ev = ev;
	return d;
}

my_struct rem(int e, int ev) {
	my_struct d;
	d.type = 'R', d.e = e, d.ev = ev;
	return d;
}

my_struct count(int a, int av, int b, int bv) {
	my_struct d;
	d.type = 'Q', d.a = a, d.av = av, d.b = b, d.bv = bv;
	return d;
}

struct BIT {
	vector<int> bit;
	
	BIT(int n) {
		bit.assign(n + 1, 0);
	}
	
	void upd(int k, int x) {
		for(++k; k < int(bit.size()); k += k & -k) bit[k] += x;
	}
	
	int query(int k) {
		int ans {};
		for(++k; k > 0; k -= k & -k) ans += bit[k];
		return ans;
	}
	
	int query(int l, int r) {
		if(l > r) return 0;
		return query(r) - query(l - 1);
	}
};

void solve() {
	int n, q;

	cin >> n;

	vector<int> a(n);
	map<int, int> v;
	map<ii, int> posicao;
	map<ii, vector<ii>> in;

	for(int& v : a) cin >> v;

	cin >> q;

	vector<my_struct> query(q);

	for(int i = 0; i < q; ++i) {
		char type;
		int a, b, p, e;
		cin >> type;
		if(type == 'I') {
			cin >> e >> p;
			query[i] = add(p, v[p], e, v[e]);
			in[ii(p, v[p])].emplace_back(e, v[e]);
		} else if(type == 'R') {
			cin >> e;
			query[i] = rem(e, v[e]);
			++v[e];
		} else {
			cin >> a >> b;
			query[i] = count(a, v[a], b, v[b]);
		}
	}

	int pos = 0;

	function<void(ii)> dfs = [&](ii x) {
		auto& adj = in[x];
		posicao[x] = pos++;
		while(!adj.empty()) {
			ii y = adj.back();
			adj.pop_back();
			dfs(y);
		}
	};

	for(int i = 0; i < n; ++i) dfs(ii(a[i], 0));

	BIT bit(pos);

	for(int v : a) bit.upd(posicao[ii(v, 0)], 1);

	for(auto& x : query) {
		char type = x.type;
		if(type == 'I') bit.upd(posicao[ii(x.e, x.ev)], 1);
		else if(type == 'R') bit.upd(posicao[ii(x.e, x.ev)], -1);
		else {
			int l = posicao[ii(x.a, x.av)];
			int r = posicao[ii(x.b, x.bv)];
			if(l > r) swap(l, r);
			cout << bit.query(l, r) - 2 << '\n';
		}
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
