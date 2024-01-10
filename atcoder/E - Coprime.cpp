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

const int N = 1e6 + 100;

int f[N];
bool is_prime[N];

void solve() {
	
	int n, g = 0;

	cin >> n;

	while(n--) {
		int v;
		cin >> v;
		g = gcd(v, g);
		++f[v];
	}

	if(g == 1) {
		bool pairwise = true;
		for(int k = 2; k < N; ++k) {
			if(is_prime[k]) continue;
			int cnt = 0;
			for(int j = k; j < N; j += k) {
				cnt += f[j];
				is_prime[j] = true;
			}
			pairwise = pairwise && cnt <= 1;
		}
		cout << (pairwise ? "pairwise coprime\n" : "setwise coprime\n");
	} else cout << "not coprime\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
