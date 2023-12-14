#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
class disjoint_set {
	vi p, r;
	int w;
	public:
	disjoint_set(int n) {
		p.resize(n);
		r.resize(n);
		w = n;
		for(int v = 0; v < n; ++v) {
			p[v] = v;
			r[v] = 0;
		}
	}
	int find_set(int v) {
		return v == p[v] ? v : p[v] = find_set(p[v]);
	}
	void join(int v1, int v2) {
		v1 = find_set(v1);
		v2 = find_set(v2);
		if(v1 == v2) return;
		else if(r[v1] < r[v2]) p[v1] = v2;
		else {
			p[v2] = v1;
			if(r[v1] == r[v2]) ++r[v1];
		}
		--w;
	}
	int comp() {
		return w;
	}
};
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int MAXN = 1e5;
	int n, m, k, res[2 * MAXN];
	pair<int, int> e[2 * MAXN], q[2 * MAXN];
	bool use[2 * MAXN];
	cin >> n >> m >> k;
	memset(use, 0, m * sizeof(bool));
	for(int i = 0; i < m; ++i) {
		cin >> e[i].first >> e[i].second;
		--e[i].first, --e[i].second;
		if(e[i].first > e[i].second) swap(e[i].first, e[i].second);
	}
	sort(e, e + m);
	for(int i = 0; i < k; ++i) {
		cin >> q[i].first >> q[i].second;
		--q[i].first, --q[i].second;
		if(q[i].first > q[i].second) swap(q[i].first, q[i].second);
		int j = lower_bound(e, e + m, q[i]) - e;
		use[j] = true;
	}
	disjoint_set S(n);
	for(int i = 0; i < m; ++i) {
		if(use[i]) continue;
		S.join(e[i].first, e[i].second);
	} 
	for(int i = k - 1; i >= 0; --i) {
		res[i] = S.comp();
		S.join(q[i].first, q[i].second);
	}
	for(int i = 0; i < k; ++i) cout << res[i] << ' ';
	cout << '\n';
	return 0;
}
