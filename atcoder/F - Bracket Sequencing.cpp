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
	
	int n;

	cin >> n;

	vector<ii> A, B;
	int prefix = 0, P = 0, Q = 0;

	for(int i = 0; i < n; ++i) {
		int p = 0, mp = INT_MAX;
		string s;

		cin >> s;

		for(char ch : s) {
			if(ch == '(') ++p;
			else --p;
			mp = min(mp, p);
		}

		prefix += p;
		
		if(mp >= 0) P += p;
		else if(p >= 0) A.emplace_back(-mp, p);
		else if(-mp > -p) {
			mp *= -1, p *= -1;
			B.emplace_back(mp - p, mp);
			Q += p;
		}
	}

	if(prefix) {
		cout << "No\n";
		return;
	}

	sort(A.begin(), A.end());
	sort(B.begin(), B.end());

	for(auto [x, y] : A) {
		if(P < x) {
			cout << "No\n";
			return;
		}
		P += y;
	}

	
	for(auto [x, y] : B) {
		if(P - Q < x) {
			cout << "No\n";
			return;
		}
		Q += x - y;
	}

	cout << "Yes\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
