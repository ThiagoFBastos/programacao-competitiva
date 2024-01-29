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

using T = tuple<int, int, int, int>;

void solve() {
	
	int n;

	cin >> n;

	vector<T> a(n);
	vector<string> p(n);

	for(int i = 0; i < n; ++i) {
		int g, s, b;
		cin >> g >> s >> b;
		cin.ignore();
		getline(cin, p[i]);
		a[i] = {g, s, b, i};
	}

	sort(a.rbegin(), a.rend());

	cout << p[get<3>(a[0])] << '\n';
}

int main() {
	int t = 1;
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	// cin >> t;
	while(t--) solve();
}

