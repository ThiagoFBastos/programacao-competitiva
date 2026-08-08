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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N = 1001;

ii ans[N];
bool usou[N];

void solve() {
	int n;
	cin >> n;
	auto [x, y] = ans[n];
	for(int i = 0; i < x; ++i) cout << "7 ";
	for(int i = 0; i < y; ++i) cout << "11 ";
	cout << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	
	for(int i = 0; i <= 1000; ++i) {
		for(int j = 0; j <= 1000; ++j) {
			int d = i * log10(7) + j * log10(11);
			if(++d > 1000 || i + j != d || usou[d]) continue;
			ans[d] = {i, j};
			usou[d] = true;
		}
	}
	
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}
