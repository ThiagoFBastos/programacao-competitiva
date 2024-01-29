#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ii = pair<int, int>;
using ld = long double;

const int N = 1e7 + 10;

int fator[N];

void solve() {
	int n;
	cin >> n;

	map<int, vector<int>> A;
	vector<int> g(n), p(n), q(n);

	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		A[a].push_back(i);
	}

	int maxn = A.rbegin()->first;

	for(int k = 2; k * k <= maxn; ++k) {
		if(fator[k]) continue;
		for(int i = k ; i <= maxn; i += k) fator[i] = k;
	}

	for(auto& [k, a] : A) {
		vector<int> G {1};
		
		for(int K = k; K > 1; ) {
			int n = G.size(), f = fator[K] ? fator[K] : K;
			i64 p = 1;
			while(K % f == 0) {
				K /= f;
				p *= f;
				for(int i = 0; i < n; ++i) G.push_back(G[i] * p);
			}
		}
		if(G.size() < a.size()) {
			cout << "NO\n";
			return;
		}
		for(int i : a) {
			p[i] = G.back();
			q[i] = k / p[i];
			G.pop_back();
		}
	}

	cout << "YES\n";
	for(int i = 0; i < n; ++i) cout << p[i] << ' ' << q[i] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

