#include "bits/stdc++.h"

using namespace std;

#define INF    1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;

bool match(char a, char b) {
	return a == '?' || b == '?' || a == b;
}

void solve() {
	string s, t;

	cin >> s >> t;

	int pre = 0, suf = 0;

	for(int i = 0; i < (int)t.size(); ++i) {
		if(!match(s[i], t[i])) break;
		++pre;
	}

	reverse(all(s));
	reverse(all(t));

	for(int i = 0; i < (int)t.size(); ++i) {
		if(!match(s[i], t[i])) break;
		++suf;
	}

	for(int x = 0; x <= (int)t.size(); ++x)
		cout << (min(pre, x) + min(suf, (int)t.size() - x) == (int)t.size() ? "Yes\n" : "No\n");
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}