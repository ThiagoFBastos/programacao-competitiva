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

bool latin(vector<string>& g) {
	int n = g.size();
	for(int i = 0; i < n; ++i) {
		set<char> S;
		for(int j = 0; j < n; ++j) S.insert(g[i][j]);
		if((int)S.size() != n) return false;
	}
	for(int j = 0; j < n; ++j) {
		set<char> S;
		for(int i = 0; i < n; ++i) S.insert(g[i][j]);
		if((int)S.size() != n) return false;
	}
	return true;
}

void solve() {
	int n;
	cin >> n;
	if(cin.eof()) exit(0);
	vector<string> g(n);
	for(auto& s : g) cin >> s;
	if(!latin(g)) {
		cout << "No\n";
		return;
	}
	string a = g[0], b;
	for(int i = 0; i < n; ++i) b += g[i][0];
	if(!is_sorted(a.begin(), a.end()) || !is_sorted(b.begin(), b.end())) {
		cout << "Not Reduced\n";
		return;
	}
	cout << "Reduced\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(1) solve();
	return 0;
}
