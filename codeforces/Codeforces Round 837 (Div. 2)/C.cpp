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

bool is_prime(int x) {
	for(int k = 2; k * k <= x; ++k) if(x % k == 0) return false;
	return true;
}

vector<int> primes;

void solve() {
	
	set<int> st;	
	
	int n;
	bool ok = false;

	cin >> n;

	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		if(!ok) {
			for(int p : primes) {
				if(a % p) continue;
				else if(p > a) break;
				ok = ok || st.count(p);
				st.insert(p);
				while(a % p == 0) a /= p;
			}
		}
		if(a != 1 && !ok) {
			ok = ok || st.count(a);
			st.insert(a);
		}
	}

	cout << (ok ? "YES\n" : "NO\n");
}

int main() {
	for(int k = 2; k * k <= 1e9; ++k) if(is_prime(k)) primes.pb(k);
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
