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

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

vector<int> P;

bool is_prime(int x) {
	for(int k = 2; k < x; ++k) if(x % k == 0) return false;
	return true;
}

void solve() {
	
	i64 A, B;

	cin >> A >> B;

	vector<i64> cnt(1 << 20, 0);
	cnt[0] = 1;

	for(; A <= B; ++A) {
		int S = 0;
		for(int i = 0; i < 20; ++i) if(A % P[i] == 0) S |= 1 << i;
		for(int k = (1 << 20) - 1; k >= 0; --k) {
			if(k & S) continue;
			cnt[k | S] += cnt[k];
		}
	}

	cout << accumulate(cnt.begin(), cnt.end(), 0LL) << '\n';
}

int main() {
	for(int k = 2; k < 72; ++k) if(is_prime(k)) P.push_back(k);
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

