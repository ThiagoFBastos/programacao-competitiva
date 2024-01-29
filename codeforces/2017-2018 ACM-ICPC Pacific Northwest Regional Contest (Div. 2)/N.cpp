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

void solve() {
	string s;
	cin >> s;
	int n = s.size();
	for(int i = 0; i < n; ++i) {
		string p;
		for(int j = i; j < n; ++j) {
			p += s[j];
			string q(p.rbegin(), p.rend());
			if(p == q) {
				int m = j - i + 1;
				if(m % 2 == 0) {
					cout << "Or not.\n";
					return;
				}
			}
		}
	}
	cout << "Odd.\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
