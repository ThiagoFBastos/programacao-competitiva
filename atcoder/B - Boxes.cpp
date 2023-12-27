#include "bits/stdc++.h"

using namespace std;
 
#define INF   1000000000
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
using i128 = __int128;

void solve() {
	int n;
	
	cin >> n;
		
	vector<int> a(n);
	i64 sum = 0;

	for(int& v : a) {
		cin >> v;
		sum += v;
	}

	i64 m = n * (n + 1ll) / 2;

	if(sum % m) {
		cout << "NO\n";
		return;
	}
	
	i64 x = sum / m;

	vector<i128> A(n + 1, 0), B(n + 1, 0);

	for(int i = 0; i < n; ++i) {
		i64 delta = x - a[i] + a[(i - 1 + n) % n];
		if(delta % n || delta < 0) {
			cout << "NO\n";
			return;
		}
		delta /= n;
		A[i + 1] += delta;
		A[1] += (n - i + 1) * delta;
		B[1] += delta;
		A[i + 1] -= (n + 1) * delta;	
	}
	
	for(int i = 1; i <= n; ++i) {
		if(A[i] != a[i - 1]) {
			cout << "NO\n";
			return;
		}
		A[i + 1] += A[i] + B[i];
		B[i + 1] += B[i];
	}

	cout << "YES\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
