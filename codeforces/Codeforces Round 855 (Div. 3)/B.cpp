#include "bits/stdc++.h"

using namespace std;
 
#define INF   1000000000
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

void solve() {
	int n, k;
	string s;
	cin >> n >> k >> s;
	int up[26] = {0}, low[26] = {0}, pairs = 0;
	for(char c : s) {
		if(islower(c)) ++low[c - 'a'];
		else ++up[c - 'A'];
	}
	for(int i = 0; i < 26; ++i) {
		int d = min(low[i], up[i]);
		pairs += d;
		low[i] -= d, up[i] -= d;
		int l = min(max(up[i], low[i]) / 2, k);
		pairs += l;
		k -= l;
	}
	cout << pairs << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	cin >> t;
	while(t--) solve();
	return 0;
}
