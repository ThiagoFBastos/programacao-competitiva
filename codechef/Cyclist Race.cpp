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

struct LiChao {
	vector<pair<i64, i64>> st;
	vector<int> coords;

	LiChao(int l, int r) {
		coords.resize(r - l + 1);
		iota(all(coords), l);
		st.resize(4 * coords.size());
	}

	LiChao(vector<int>& c) : coords {c} {
		sort(all(coords));
		coords.resize(unique(all(coords)) - coords.begin());
		st.resize(4 * coords.size());
	}

	void fill(pair<i64, i64> x) {
		std :: fill(all(st), x);
	}

	i64 eval(pair<i64, i64> f, int x) {
		return x * f.fi + f.sc;
	}

	void add(pair<i64, i64> f) {
		add(f, 0, (int)coords.size() - 1);
	}

	void add(pair<i64, i64> f, int l, int r, int p = 1) {
		int m = (l + r) / 2;

		bool v1 = eval(f, coords[l]) > eval(st[p], coords[l]);
		bool v2 = eval(f, coords[m]) > eval(st[p], coords[m]);

		if(v2) swap(f, st[p]);

		if(l == r) return;
		else if(v1 != v2) add(f, l, m, 2 * p);
		else add(f, m + 1, r, 2 * p + 1);
	}

	i64 query(int x) {
		return query(x, 0, (int)coords.size() -1);
	}

	i64 query(int x, int l, int r, int p = 1) {
		i64 y = eval(st[p], x);
		if(l == r) return y;
		int m = (l + r) / 2;
		return max(y, x <= coords[m] ? query(x, l, m, 2 * p) : query(x, m + 1, r, 2 * p + 1));
	}
};

void solve() {
	int n, q;

	cin >> n >> q;

	vector<int> T;
	vector<i64> x(n + 1, 0), speed(n + 1, 0), upd(n + 1, 0);
	vector<tuple<int, int, int, int>> e(q);
	
	for(int i = 0; i < q; ++i) {
		int type;
		cin >> type;
		if(type == 1) {
			int tms, id, new_speed;
			cin >> tms >> id >> new_speed;
			e[i] = {1, tms, id, new_speed};
		} else {
			int tms;
			cin >> tms;
			e[i] = {2, tms, -1, -1};
			T.pb(tms);
		}
	}	

	LiChao cht(T);
	
	cht.fill({0, 0});

	for(auto& v : e) {
		int type, tms, id, new_speed;

		tie(type, tms, id, new_speed) = v;

		if(type == 1) {
			x[id] += speed[id] * (tms - upd[id] + 0ll);
			speed[id] = new_speed;
			upd[id] = tms;
			cht.add({new_speed, x[id] - (i64)new_speed * tms});
		} else
			cout << cht.query(tms) << '\n';
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