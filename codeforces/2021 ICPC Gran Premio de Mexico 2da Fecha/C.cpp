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

	s += s;

	vector<int> pre(2 * n + 1, 0);

	pre[0] = 0;
	for(int i = 1; i <= (int)s.size(); ++i) {
		pre[i] = pre[i - 1];
		if(s[i - 1] == 'B') --pre[i];
		else ++pre[i];
	}

	stack<ii> st;

	int ans = INT_MAX;

	for(int i = 2 * n; i >= 0; --i) {
		while(!st.empty() && st.top().first <= pre[i]) st.pop();
		if(st.empty() || !st.empty() && i < n && st.top().second - i > n) ans = i;
		st.emplace(pre[i], i);	
	}

	if(ans == INT_MAX) cout << "-1\n";
	else cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}

