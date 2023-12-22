#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
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

const int N = 50, K = 20;

i64 cost[N][K][N][K];

void solve() {
	int n;

	cin >> n;

	vector<string> s(n);
	vector<int> c(n);

	using T = tuple<i64, int, int, int, int>;
	priority_queue<T, vector<T>, greater<T>> pq;

	for(int i = 0; i < n; ++i) cin >> s[i] >> c[i];

	for(int i = 0; i < n; ++i)
		for(int j = 0; j < (int)s[i].size(); ++j)
			for(int k = 0; k < n; ++k)
				for(int l = 0; l < (int)s[k].size(); ++l)
					cost[i][j][k][l] = -1;

	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			pq.emplace(c[i] + (i!=j) * c[j], i, 0, j, 0);

	while(!pq.empty()) {
		auto [x, a, lo, b, hi] = pq.top(); pq.pop();

		if(cost[a][lo][b][hi] != -1) continue;

		cost[a][lo][b][hi] = x;

		auto& p = s[a];
		auto& q = s[b];

		if(p[lo] != q[(int)q.size() - hi - 1]) continue;

		if(a == b && abs(lo - (int)q.size() + hi + 1) <= 1) {
			cout << x << '\n';
			return;
		}
		
		if(lo + 1 < (int)p.size() && hi + 1 < (int)q.size()) {
			if(cost[a][lo+1][b][hi+1] == -1)
				pq.emplace(x, a, lo + 1, b, hi + 1);
		} else if(lo + 1 < (int)p.size()) {
			for(int i = 0; i < n; ++i) {
				if(cost[a][lo+1][i][0] != -1) continue;
				pq.emplace(x+c[i]*(i!=a),a,lo+1,i,0);
			}
		} else if(hi + 1 < (int)q.size()) {
			for(int i = 0; i < n; ++i) {
				if(cost[i][0][b][hi+1] != -1) continue;
				pq.emplace(x+c[i]*(i!=b),i,0,b,hi+1);
			}
		} else {
			cout << x << '\n';
			return;
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
