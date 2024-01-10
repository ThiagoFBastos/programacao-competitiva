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

const int N = 2e5 + 100;

set<ii> K[N];

void solve() {

	int n, q;

	cin >> n >> q;

	multiset<int> S;
	vector<int> a(n + 1), b(n + 1);

	for(int i = 1; i <= n; ++i) {
		cin >> a[i] >> b[i];
		K[b[i]].insert(make_pair(a[i], i));
	}

	for(int i = 1; i < N; ++i) {
		if(K[i].empty()) continue;
		S.insert(K[i].rbegin()->first);
	}

	while(q--) {
		int c, d;
		
		cin >> c >> d;

		if(d != b[c]) {
			if(!K[d].empty()) S.erase(S.find(K[d].rbegin()->first));
			S.erase(S.find(K[b[c]].rbegin()->first));
			K[b[c]].erase(make_pair(a[c], c));
			K[d].insert(make_pair(a[c], c));
			S.insert(K[d].rbegin()->first);
			if(!K[b[c]].empty()) S.insert(K[b[c]].rbegin()->first);
			b[c] = d;
		}

		cout << *S.begin() << '\n';
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
