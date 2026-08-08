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

const i64 inf = 1e17L + 100;

ld point(i64 a0, i64 b0, i64 a1, i64 b1) {
	return (b1 - b0) / ld(a0 - a1);
}

bool cmp(array<int, 4> a, array<int, 4> b) {
	return a[0] < b[0];
}

void solve() {
	int n, m;
	
	cin >> n >> m;
	
	vector<array<int, 4>> A(m), B(m);
	vector<i64> dp(m, inf);
	vector<deque<pair<i64, i64>>> dq(n);
	i64 ans = inf;
	
	dq[0].emplace_back(0LL, 0LL);
	
	for(int i = 0; i < m; ++i) {
		int a, b, s, t;
		cin >> a >> b >> s >> t;
		--a, --b;
		A[i] = {t, s, b, i};
		B[i] = {s, t, a, i};
	}
	
	sort(A.begin(), A.end(), cmp);
	sort(B.begin(), B.end(), cmp);
	
	int i = 0, j = 0;
	
	while(i < m || j < m) {
		if(j == m || A[i][0] <= B[j][0]) {
			i64 a, b;
			auto& q = dq[A[i][2]];
			
			a = -2 * A[i][0];
			
			if(A[i][2] == n - 1) ans = min(ans, dp[A[i][3]]);
			
			b = dp[A[i][3]] + (i64)A[i][0] * A[i][0];
			
			while((int)q.size() >= 2) {
				int n = q.size();
				auto [a1, b1] = q[n - 1];
				auto [a2, b2] = q[n - 2];
				if(point(a, b, a1, b1) > point(a1, b1, a2, b2)) break;
				q.pop_back();
			}
			
			q.emplace_back(a, b);
			
			++i;
		} else {
			auto& q = dq[B[j][2]];
			
			while((int)q.size() >= 2) {
				auto [a1, b1] = q[0];
				auto [a2, b2] = q[1];
				if(a1 * B[j][0] + b1 < a2 * B[j][0] + b2) break;
				q.pop_front();
			}
			
			if(!q.empty()) {
				auto [a, b] = q[0];
				dp[B[j][3]] = a * B[j][0] + b + (i64)B[j][0] * B[j][0];
			}
			
			++j;
		}
	}
	
	cout << ans << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
