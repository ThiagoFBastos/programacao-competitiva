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
	map<string, int> out, in;
	while(true) {
		string s, t;
		cin >> s >> t;
		if(cin.eof()) break;
		++in[t], ++out[s];
	}
	cout << "HALL OF MURDERERS\n";
	for(auto& [x, y] : out) {
		auto k = in.find(x);
		if(k != in.end()) continue;
		cout << x << ' ' << y << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
