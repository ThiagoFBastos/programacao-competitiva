#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using vi = vector<int>;
using ii = pair<int, int>;
using li = pair<ll, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;

int n, m;
double dp[101];

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	while(true) {
		cin >> n >> m;

		if(n == 0 && m == 0)
			break;

		unordered_map<int, vi> p;

		p.reserve(n);

		for(int i = 1; i <= n; ++i) {
			int x;
			cin >> x;
			p[x].push_back(i);
			dp[i] = INT_MAX;
		}

		for(int i = 0; i < m; ++i) {
			int a;
			double x;
			cin >> a >> x;
			auto ptr = p.find(a);
			if(ptr != p.end()) {
				vi& v = ptr->second;
				for(int i = (int)v.size() - 1; i >= 0; --i) {
					int y = v[i];
					dp[y] = min(dp[y - 1] + x, dp[y]);
				}	
			}
		}
		if(dp[n] == INT_MAX)
			cout << "Impossible\n";
		else
			cout << setprecision(2) << fixed << dp[n] << '\n';
	}

	return 0;
}