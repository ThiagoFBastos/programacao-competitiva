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

void solve() {
	int n, m;	

	cin >> n >> m;

	n <<= 1;

	vector<int> a(n);

	for(int& v : a) cin >> v;

	if(m % 2) {
		map<int, int> frq;
		bool even = true;
		for(int v : a) ++frq[v];
		for(auto [_, y] : frq) even = even && y % 2 == 0;
		cout << (even ? "Bob\n" : "Alice\n");
	} else {
		map<int, array<int, 2>> frq;
		int pairs = 0;
		bool odd = false;

		for(int v : a) {
			int u = (v + m / 2) % m;	
			++frq[min(u, v)][u < v];
		}
		
		for(auto [_, v] : frq) {
			if(v[0] % 2 && v[1] % 2) ++pairs;
			odd = odd || (v[0] + v[1]) % 2;
		}

		if(odd || pairs % 2) cout << "Alice\n";
		else cout << "Bob\n";
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
