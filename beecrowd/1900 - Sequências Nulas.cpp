#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

const i64 RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();

struct chash {
	i64 operator()(i64 x) const { return x ^ RANDOM; }
};

void solve() {				
	int n;
	i64 cnt = 0, pre = 0;
	cin >> n;
	gp_hash_table<i64, int> hash;
	++hash[0];
	for(int i = 0; i < n; ++i) {
		int v;
		cin >> v;
		pre += v;
		auto k = hash.find(pre);
		if(k != hash.end()) cnt += k->second;
		++hash[pre];
	}
	cout << cnt << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}