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

const int N = 2e5 + 1;

bool win[N][7];

void solve() {
	int n;

	string s, x;

	cin >> n >> s >> x;

	x += "T";

	win[n][0] = true;

	for(int i = n - 1; i >= 0; --i) {
		for(int k = 0; k < 7; ++k) {
			for(int ch : {0, s[i] - '0'}) {
				int v = (10 * k + ch) % 7;
				if(x[i + 1] == x[i]) win[i][k] |= win[i + 1][v];
				else win[i][k] |= !win[i + 1][v];
			}
		}
	}

	if(x[0] == 'A') cout << (win[0][0] ? "Aoki\n" : "Takahashi\n");
	else cout << (win[0][0] ? "Takahashi\n" : "Aoki\n");
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

