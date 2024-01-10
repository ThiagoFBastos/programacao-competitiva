#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

const long long inf = 1e10L;

void solve() {	
	int n;
	long long dist[4];
	cin >> n;
	for(int i = 0; i < 4; ++i) dist[i] = -inf;
	while(n--) {
		int x[2];
		cin >> x[0] >> x[1];
		for(int k = 0; k < 4; ++k) {
			auto v = 0;
			for(int i = 0; i < 2; ++i) {
				if(k & 1 << i) v += x[i];
				else v -= x[i];
			}
			dist[k] = max(dist[k], 0LL + v);
		}
	}
	auto ans = -inf;
	for(int k = 0; k < 4; ++k) ans = max(ans, dist[k] + dist[~k & 3]);
	cout << ans << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
