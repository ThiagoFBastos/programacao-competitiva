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

void solve() {
	int p;
	string s;

	cin >> s;
	
	int n = s.size();

	auto z1 = z_function(s);

	reverse(all(s));
	
	auto z2 = z_function(s);

	for(p = 1; p < n; ++p) {
		if(n % p) continue;
		if(z1[p] == n - p) break;
	}

	if(p == n) {
		cout << "1\n1\n";
		return;
	} else if(p == 1) {
		cout << n << "\n1\n";
		return;
	}

	cout << "2\n";

	int cnt = 0;

	vector<bool> ps(n + 1, true), ss(n + 1, true);

	for(int p = 1; p < n; ++p) {
		for(int i = 2 * p; i <= n; i += p) {
			ps[i] = ps[i] && z1[p] < i - p;
			ss[i] = ss[i] && z2[p] < i - p;
		}
	}

	for(int i = 1; i < n; ++i) if(ps[i] && ss[n - i]) ++cnt;
	
	cout << cnt << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
