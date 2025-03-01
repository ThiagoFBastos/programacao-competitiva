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

vector<int> z_function(string& s) {
    int n = (int) s.length();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if(i <= r) z[i] = min (r - i + 1, z[i - l]);
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

const int mod = 1e9 + 7, N = 5e3 + 1;

i64 fat[N], inv[N], invFat[N];

i64 C(int n, int k) {
	return fat[n] * invFat[n - k] % mod * invFat[k] % mod;
}

void solve() {				
	int n, q;
	string s;
	
	cin >> n >> q >> s;
	
	vector<int> ptr(n, 0), pre(n + 2); 
	vector<i64> cnt(n + 1, 0), ans(n + 1, 0);
	
	for(int i = n - 1; i >= 0; --i) {
		
		string pat = s.substr(i) + "$" + s;
		int k = n - i + 1;
		auto z = z_function(pat);
		
		fill(pre.begin(), pre.end(), 0);
		
		for(int j = 0; j < n; ++j) {
			if(ptr[j] <= z[k + j]) {
				--pre[1 + z[k + j]];
				++pre[1 + ptr[j]];
			}
			ptr[j] = max(ptr[j], z[k + j]);
		}
		for(int j = 1; j <= n; ++j) {
			pre[j] += pre[j - 1];
			++cnt[pre[j]];
		}
	}
	
	for(int k = 1; k <= n; ++k) {
		for(int i = k; i <= n; ++i) ans[k] = (ans[k] + C(i, k) * cnt[i]) % mod;
		ans[k] = (ans[k] + mod) % mod;
	}
	
	while(q--) {
		int ki;
		cin >> ki;
		if(ki > n) cout << "0\n";
		else cout << ans[ki] << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	
	for(int k = 0; k < 2; ++k) fat[k] = inv[k] = invFat[k] = 1;
	for(int k = 2; k < N; ++k) {
		fat[k] = k * fat[k - 1] % mod;
		inv[k] = -(mod / k) * inv[mod % k] % mod;
		invFat[k] = inv[k] * invFat[k - 1] % mod;
	}
	
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}