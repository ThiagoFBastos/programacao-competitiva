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
 
const int INF = 1e9;
 
struct X {
	int d, j, b, type;
	X(int d, int j, int b, int type) : d {d}, j {j}, b {b}, type {type} {}
};
 
const int N = 3e4, K = 173;
 
int dist[N][K], n, m, s, t, j;
 
vector<int> jumps[N];
queue<X> q;
 
void solve() {
 
	cin >> n >> m;
	
	for(int i = 0; i < n; ++i)
	for(int j = 0; j * j <= n; ++j)
		dist[i][j] = -1;
 
	for(int i = 0; i < m; ++i) {
		int b, p;
		cin >> b >> p;
		if(i == 0) s = b, j = p;
		else if(i == 1) t = b;
		jumps[b].push_back(p);
	}
 
	for(int i = 0; i < n; ++i) {
		auto& v = jumps[i];
		sort(v.begin(), v.end());
		v.resize(unique(v.begin(), v.end()) - v.begin());
	}
 
	if(j * j <= n) {
		dist[s][j] = 0;
		q.emplace(0, j, s, 0);
	} else {
		q.emplace(0, j, s, -1);
		q.emplace(0, j, s, 1);
	}
 
	while(!q.empty()) {
		auto [d, j, b, type] = q.front();
 
		if(b == t) {
			cout << d << '\n';
			return;
		}
 
		q.pop();
 
		if(type == -1) {
			if(b - j >= 0) q.emplace(d + 1, j, b - j, -1);
		} else if(type == 1) {
			if(b + j < n) q.emplace(d + 1, j, b + j, 1);
		} else {
			if(b - j >= 0 && dist[b - j][j] == -1) {
				dist[b - j][j] = 1 + d;
				q.emplace(d + 1, j, b - j, 0);
			}
			if(b + j < n && dist[b + j][j] == -1) {
				dist[b + j][j] = 1 + d;
				q.emplace(d + 1, j, b + j, 0);
			}
		}
 
		while(!jumps[b].empty()) {
			int p = jumps[b].back();
			jumps[b].pop_back();
			if(p * p <= n) {
				if(b - p >= 0 && dist[b - p][p] == -1) {
					dist[b - p][p] = d + 1;
					q.emplace(d + 1, p, b - p, 0);
				}
				if(b + p < n && dist[b + p][p] == -1) {
					dist[b + p][p] = d + 1;
					q.emplace(d + 1, p, b + p, 0);
				}
			} else {
				if(b - p >= 0) q.emplace(d + 1, p, b - p, -1);
				if(b + p < n) q.emplace(d + 1, p, b + p, 1);
			}
		}
	}
 
	cout << "-1\n";
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
