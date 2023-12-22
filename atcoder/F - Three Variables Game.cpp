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

	int n, a, b, c;
	string t;

	cin >> n >> a >> b >> c;

	vector<string> s(n);

	for(string& w : s) cin >> w;

	for(int i = 0; i < n; ++i) {
		if(s[i] == "AB") {
			if(a + b == 0) {
				cout << "No\n";
				return;
			} else if(a && b && i < n - 1) {
				if(s[i + 1][0] == 'A') ++a, --b, t += 'A';
				else ++b, --a, t += 'B';
			} else if(a < b) ++a, --b, t += 'A';
			else ++b, --a, t += 'B';
		} else if(s[i] == "AC") {
			if(a + c == 0) {
				cout << "No\n";
				return;
			} else if(a && c && i < n - 1) {
				if(s[i + 1][0] == 'A') ++a, --c, t += 'A';
				else ++c, --a, t += 'C';
			} else if(a < c) ++a, --c, t += 'A';
			else ++c, --a, t += 'C';
		} else {
			if(b + c == 0) {
				cout << "No\n";
				return;
			} else if(b && c && i < n - 1) {
				if(s[i + 1][0] == 'B' || s[i + 1][1] == 'B') ++b, --c, t += 'B';
				else ++c, --b, t += 'C';
			} else if(b < c) ++b, --c, t += 'B';
			else ++c, --b, t += 'C';
		}
	}

	cout << "Yes\n";
	for(char ch : t) cout << ch << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

