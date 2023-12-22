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

const int inf = 1e9;

auto get(string& s, int n, int m) {
	vector<int> dp(n + 1, inf);
	set<ii> S;
	dp[0] = 0;
	S.insert(make_pair(0, 0));
	for(int i = 1; i <= n; ++i) {
		if(s[i] == '0') dp[i] = S.begin()->first + 1;
		S.insert(make_pair(dp[i], i));
		if(i - m >= 0) S.erase(make_pair(dp[i - m], i - m));
	}
	return dp;
}

void solve() {
	int n, m;
	string s;
	cin >> n >> m >> s;
	
	auto L = get(s, n, m);
	
	if(L.back() > n) {
		cout << "-1\n";
		return;
	}
	
	reverse(s.begin(), s.end());
	
	auto R = get(s, n, m);
	reverse(R.begin(), R.end());
	reverse(s.begin(), s.end());
	
	vector<int> moves;
	int last = 0, jumps = 0;
	
	for(int i = 0; i <= n; ++i) {
		if(s[i] == '1') continue;
		if(L[i] + R[i] == L.back() && L[i] == jumps && R[i] == L.back() - jumps) {
			moves.push_back(i - last);
			++jumps;
			last = i;
		}
	}

	for(int i = 1; i < (int)moves.size(); ++i) cout << moves[i] << ' ';
	cout << '\n';
}
 
int main() {
    ios_base :: sync_with_stdio(false);
   	cin.tie(0);
    int t = 1;
  //cin >> t;
    while(t--) solve();
    return 0;
}
