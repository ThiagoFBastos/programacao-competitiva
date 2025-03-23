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
	int n;

	cin >> n;
	
	using T = tuple<int, int, int>;
	
	vector<T> s(n);

	for(int i = 0; i < n; ++i) {
		string t;
		int par = 0, need = 0, has[26] = {0};
		cin >> t;
		for(char c : t) {
			par ^= 1 << (c - 'a');
			has[c - 'a'] = 1;
		}
		for(int j = 0; j < 26; ++j) need |= (has[j] ^ 1) << j;
		s[i] = {par, (int)t.size(), need};
	}
	
	i64 pairs = 0;

	for(int i = 0; i < 26; ++i) {
		map<int, int> mp;
		for(auto [par, len, need] : s) {
			if((len&1) && ((need>>i)&1)) ++mp[par];
		}
		for(auto [par, len, need] : s) {
			if(((~need>>i)&1)||(len & 1)) continue;
			int mask = ((1<<26)-1)^(1<<i);
			pairs += mp[par^mask];
		}
	}

	cout << pairs << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  //	cin >> t;
	while(t--) solve();
	return 0;
}
