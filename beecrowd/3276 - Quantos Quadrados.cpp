#include "bits/stdc++.h"
using namespace std;
using Vetor = pair<int, int>;
#define x first
#define y second
typedef long double ld;
bool perpendicular(Vetor a, Vetor b) {
	return a.x * b.x + a.y * b.y == 0;
}
bool paralela(Vetor a, Vetor b) {
	swap(b.x, b.y);
	b.x *= -1;
	return perpendicular(a, b);
}
ld dist(Vetor a, Vetor b, Vetor c) {
	Vetor u, v;
	u = {b.x - a.x, b.y - a.y};
	v = {c.x - a.x, c.y - a.y};
	int k = abs(u.x * v.y - u.y * v.x);
	return 1LL * k * k / ld(u.x * u.x + u.y * u.y);
}
void solve() {
	int n;
	long long cnt = 0;
	cin >> n;
	vector<Vetor> a(n), b(n);
	vector<vector<int>> p(n);
	vector<vector<ld>> d(n);
	vector<int> grupo(n), g(n, -1);
	for(int i = 0; i < n; ++i) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		a[i] = {x1, y1};
		b[i] = {x2, y2};
		grupo[i] = i;
	}
	for(int i = 0; i < n; ++i) {
		if(grupo[i] != i) continue;
		p[i].push_back(i);
		for(int j = i + 1; j < n; ++j) {
			if(paralela({a[i].x - b[i].x, a[i].y - b[i].y}, {a[j].x - b[j].x, a[j].y - b[j].y})) {
				grupo[j] = i;
				p[i].push_back(j);
			}
		}
	}
	for(int i = 0; i < n; ++i) {
		for(int j = i + 1; j < n; ++j) {
			if(perpendicular({a[i].x - b[i].x, a[i].y - b[i].y}, {a[j].x - b[j].x, a[j].y - b[j].y})) {
				g[grupo[i]] = grupo[j];
				g[grupo[j]] = grupo[i];
			}
		}
	}
	for(int i = 0; i < n; ++i) {
		for(int k = 0; k < size(p[i]); ++k) {
			for(int j = k + 1; j < size(p[i]); ++j) {
				int u = p[i][k], v = p[i][j];
				d[i].push_back(dist(a[u], b[u], a[v]));
			}
		}
		sort(d[i].begin(), d[i].end());
	}
	for(int i = 0; i < n; ++i) {
		if(g[i] == -1) continue;
		for(int k = 0; k < size(p[i]); ++k) {
			for(int j = k + 1; j < size(p[i]); ++j) {
				int u = p[i][k], v = p[i][j];
				ld h = dist(a[u], b[u], a[v]);
				auto L = lower_bound(d[g[i]].begin(), d[g[i]].end(), h);
				auto R = upper_bound(d[g[i]].begin(), d[g[i]].end(), h);
				cnt += R - L;
			}
		}
	}
	cout << cnt / 2 << '\n';
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}