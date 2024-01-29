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


int period(string& s) {
	
	auto z = z_function(s);
	int n = s.size();

	vector<int> divs;

	for(int k = 1; k * k <= n; ++k) {
		if(n % k) continue;
		divs.push_back(k);
		divs.push_back(n / k);
	}

	sort(divs.begin(), divs.end());

	z[0] = n;

	for(int d : divs) {
		bool ok = true;
		for(int k = 0; k < n; k += d) {
			if(k + z[k] != n) {
				ok = false;
				break;
			}
		}
		if(ok) return d;
	}

	return n;
}

void solve() {
	
	string s;

	cin >> s;

	int periodo = period(s), n = s.size();	
	i64 ans = 0;

	for(int k = 1; k * periodo <= n; ++k) {
		if(n % (k * periodo)) continue;
		if(k * periodo < n) ans += n;
		else ++ans;	
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


