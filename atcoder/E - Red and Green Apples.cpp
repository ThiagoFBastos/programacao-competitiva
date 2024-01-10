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
	int x, y, a, b, c;
	cin >> x >> y >> a >> b >> c;

	vector<int> A(a), B(b), C(c);
	vector<i64> D(1, 0);

	for(int& v : A) cin >> v;
	for(int& v : B) cin >> v;
	for(int& v : C) cin >> v;

	sort(A.rbegin(), A.rend());
	sort(B.rbegin(), B.rend());
	sort(C.rbegin(), C.rend());

	for(int i = 0; i < x; ++i) D.push_back(A[i]);
	for(int i = 0; i < y; ++i) D.push_back(B[i]);

	sort(D.begin(), D.end());
	reverse(D.begin() + 1, D.end());

	for(int i = 1; i < (int)D.size(); ++i) D[i] += D[i - 1];

	i64 s = 0, ans = D.back();

	for(int i = 1; i <= min(c, x + y); ++i) {
		s += C[i - 1];
		ans = max(ans, D[x + y - i] + s); 
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
