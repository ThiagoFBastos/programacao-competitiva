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
	
	int n; 
	i64 k;

	cin >> n >> k;

	vector<pair<i64, i64>> monster(n);
	multiset<i64> P;

	for(auto& [h, _] : monster) cin >> h;
	for(auto& [_, p] : monster) {
		cin >> p;
		P.insert(p);
	}

	sort(rall(monster));

	i64 damage = 0;
	
	while(!monster.empty() && k > 0) {
		auto [h, p] = monster.back();

		h -= damage;

		while(h > k && k > 0) {
			h -= k;
			damage += k;
			k -= *P.begin();
		}

		h -= k;
		damage += k;

		if(h > 0) {
			cout << "NO\n";
			return;
		}
		
		while(!monster.empty() && monster.back().fi <= damage) {
			auto [h, p] = monster.back();
			P.erase(P.find(p));
			monster.pop_back();
		}

		if(!P.empty()) k -= *P.begin();
	}

	cout << (monster.empty() ? "YES\n" : "NO\n");
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}

