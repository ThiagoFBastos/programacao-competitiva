#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse,sse2,sse3,sse4,avx,avx2")
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	ll s;
	cin >> n;
	s = n * (n + 1LL) / 2;
	if(s & 1)
		cout << "NO\n";
	else {
		vector<bool> marked(n + 1, true);
		int count = 0;
		cout << "YES\n";
		s >>= 1;
		for(int k = n; k > 0 && s; --k) {
			if(s >= k) {
				s -= k;
				marked[k] = false;
				++count;
			}
		}
		cout << count << '\n';
		for(int k = 1; k <= n; ++k)
			if(!marked[k]) cout << k << ' ';
		cout << '\n' << n - count << '\n';
		for(int k = 1; k <= n; ++k)
			if(marked[k]) cout << k << ' ';
		cout << '\n'; 
	}
	return 0;
}
