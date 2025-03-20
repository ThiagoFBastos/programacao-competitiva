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
using i128 = __int128;

void solve() {
	int n, m;

	cin >> n >> m;

	vector<vector<int>> a(n);	
	vector<int> s(n, 0);
	int _1 = 0;

	for(int i = 0; i < n; ++i) {
		a[i].resize(m);
		for(int& v : a[i]) {
			cin >> v;
			s[i] += v;
		}
		_1 += s[i];
	}

	if(_1 % n) {
		cout << "-1\n";
		return;
	}

	_1 /= n;

	vector<tuple<int, int, int>> op;

	for(int j = 0; j < m; ++j) {
		stack<int> need, give;
		for(int i = 0; i < n; ++i) {
			if(s[i] > _1 && a[i][j]) {
				if(need.empty()) give.push(i);
				else {
					int k = need.top();		
					--s[i], ++s[k];
					op.pb({k + 1, i + 1, j + 1});
					need.pop();
				}
			} else if(s[i] < _1 && !a[i][j]) {
				if(give.empty()) need.push(i);
				else {
					int k = give.top();
					++s[i], --s[k];
					op.pb({k + 1, i + 1, j + 1});
					give.pop();
				}
			}
		}
	}

	cout << op.size() << '\n';
	for(auto [x, y, z] : op) cout << x << ' ' << y << ' ' << z << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
