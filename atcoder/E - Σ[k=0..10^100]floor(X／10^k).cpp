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
	
	string X, Y;

	cin >> X;

	int s = 0, carry = 0, n = X.size();

	for(char ch : X) s += ch - '0';
	
	for(int i = n - 1; i >= 0; --i) {
		Y += (s + carry) % 10 + '0';
		carry = (s + carry - (s + carry) % 10) / 10;
		s -= X[i] - '0';	
	}

	if(carry) Y += to_string(carry);

	reverse(Y.begin(), Y.end());

	cout << Y << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
