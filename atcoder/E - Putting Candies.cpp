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
	i64 k, x = 0;

	cin >> n >> k;

	vector<int> a(n);
	for(int& v : a) cin >> v;

	vector<bool> vis(n, false);
	stack<int> st;

	while(!vis[x % n] && k) {
		int y = (x + a[x % n]) % n;
		vis[x % n] = true;
		st.push(x % n);
		--k, x += a[x % n];
		if(vis[y]) {
			vector<int> cycle;
			i64 sum = 0;
			while(st.top() != y) {
				cycle.push_back(st.top());
				st.pop();
			}
			cycle.push_back(st.top());
			reverse(cycle.begin(), cycle.end());
			for(int i : cycle) sum += a[i];
			x += k / (int)cycle.size() * sum;
			k %= cycle.size();
			for(int i : cycle) {
				if(k-- == 0) break;
				x += a[i];
			}
			break;
		}
	}
	cout << x << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

