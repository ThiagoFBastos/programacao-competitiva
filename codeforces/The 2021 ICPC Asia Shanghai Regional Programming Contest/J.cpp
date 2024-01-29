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

const int N = 5e4 + 10;

bitset<N> bs, ans;

void solve() {

	int n;
	string a, b, c;
	bool flag = false;

	ans.reset();

	cin >> n >> a >> b;

	vector<int> pre(n + 1, 0);
	vector<ii> v(n + 1);

	v[0] = {0, 0};

	for(int i = 1; i <= n; ++i) {
		pre[i] = pre[i - 1] + 2 * (a[i - 1] - '0');
		v[i] = {pre[i] - i, -i};
	}
	
	sort(v.begin(), v.end());

	bs.reset();

	for(auto [x, y] : v) {
		y *= -1;
		ans |= bs >> y;
		if(b[y - 1] == '1') bs[y] = 1;
	}
	
	bs.reset();

	sort(v.rbegin(), v.rend());

	for(auto [x, y] : v) {
		y = -y;
		ans |= bs >> y;
		if(b[y - 1] == '0') bs[y] = 1;
	}

	for(int i = 1; i <= n; ++i) {
		flag = flag || (b[i - 1] == '0' && pre[i] > i) || (b[i - 1] == '1' && pre[i] <= i);
		if(flag) c += "0";
		else c += ans[i] ^ '1';
	}

	cout << c << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}

