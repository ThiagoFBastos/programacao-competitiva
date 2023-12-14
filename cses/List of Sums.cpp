#include "bits/stdc++.h"
using namespace std;
using ii = pair<long long, int>;
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> b(n * (n - 1) / 2);
	for(int i = 0; i < int(b.size()); ++i) cin >> b[i];
	sort(b.begin(), b.end());
	vector<long long> a(n);
	for(int y : b) {
		long long a1 = b[0] - y + b[1];
		if((a1 & 1) || a1 <= 0) continue;
		a[0] = a1 / 2;
		a[1] = b[0] - a[0];
		a[2] = b[1] - a[0];
		if(a[1] < a[0]) continue;
		bool ok = true;
		int k = 2;
		queue<ii> S;
		priority_queue<ii, vector<ii>, greater<ii>> pq;
		pq.push({a[0] + a[1], 1});
		pq.push({a[1] + a[2], 2});
		S.push({2 * a[2], 2});
		for(int x : b) {
			if(pq.empty() || pq.top().first != x) {
				if(++k == n) {
					ok = false;
					break;
				}
				a[k] = x - a[0];
				while(!S.empty()) {
					auto [r, s] = S.front();
					S.pop();
					pq.push({r - a[s] + a[s + 1], s + 1});
				}
				pq.pop();
				S.push({x, k});
				S.push({2 * a[k], k});
			} else {
				auto [p, q] = pq.top();
				pq.pop();
				if(q == k) S.push({p, q});
				else pq.push({p - a[q] + a[q + 1], q + 1});
			}
		}
		if(!ok) continue;
		for(auto& x : a) cout << x << ' ';
		cout << '\n';
		break;
	}
	return 0;
}
