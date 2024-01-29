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

const int N = 1e6 + 10;

bitset<N> is_prime;

void solve() {
	i64 a, b;

	cin >> a >> b;

	int n = b - a + 1;

	vector<i64> fat(n), sum(n, 1);

	for(int i = 0; i < n; ++i) fat[i] = a + i;

	is_prime.set();

	for(int i = 2; i * i < N; ++i) {
		if(!is_prime[i]) continue;
		for(int k = i * i; k < N; k += i) is_prime[k] = 0;
	}

	for(int i = 2; i < N; ++i) {
		if(!is_prime[i]) continue;
		for(i64 k = a + (i - a % i) % i; k <= b; k += i) {
			i64 p = 1, s = 1, x = k;
			while(fat[k - a] % i == 0) {
				p *= i;
				s += p;
				fat[k - a] /= i;
			}
			sum[k - a] *= s;
		}
	}

	i64 ans = 0;

	for(int i = 0; i < n; ++i) {
		if(fat[i] > 1) sum[i] *= (1 + fat[i]);
		ans += sum[i];
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
