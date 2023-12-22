#include "bits/stdc++.h"
using namespace std;

const int N = 1e5 + 1;
int p[N], r[N];
set<int> points[N];
vector<int> cols[N];
int n;

int find_set(int k) {
	return k == p[k] ? k : p[k] = find_set(p[k]);
}

void join(int a, int b) {
	a = find_set(a), b = find_set(b);
	if(a == b) return;
	else if(r[a] > r[b]) swap(a, b);
	
	p[a] = b;
	r[b] += r[a] == r[b];
	
	for(int y : points[a]) points[b].insert(y);
}

void solve() {

	cin >> n;
	
	for(int i = 0; i < N; ++i) p[i] = i;
	
	for(int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		points[y].insert(x);
		cols[x].push_back(y);
	}
	
	for(int x = 1; x < N; ++x) {
		int z = -1;
		for(int y : cols[x]) {
			if(int(size(points[find_set(y)])) > 1) {
				z = y;
				break;
			}
		}
		if(z < 0) continue;
		for(int y : cols[x]) join(y, z);
	}
	
	auto cnt = -n + 0LL;
	
	for(int x = 1; x < N; ++x) cnt += size(points[find_set(x)]);
	
	cout << cnt << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
