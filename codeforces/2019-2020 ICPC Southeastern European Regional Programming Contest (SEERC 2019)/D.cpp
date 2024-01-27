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
	string s;
	cin >> s;

	int n = s.size() / 2;
	int frq[26] = {0};
	for(char c : s) ++frq[c - 'a'];

	vector<ii> p;

	for(int i = 0; i < 26; ++i) if(frq[i]) p.pb({frq[i], i});

	sort(all(p));

	if(p.back().fi <= n) {
		cout << "YES\n";
		sort(all(s));
		cout << s << '\n';
	} else if(p.back().fi >= 2 * n - 1) cout << "NO\n";
	else if(p.back().fi == 2 * n - 2 && p[0].fi == 2) cout << "NO\n";
	else {
		cout << "YES\n";
		string t = string(n, p.back().sc + 'a');
		t += p[0].sc + 'a';
		t += string(p.back().fi - n, p.back().sc + 'a');
		--p[0].fi;
		for(int i = 0; i < (int)p.size() - 1; ++i)
			t += string(p[i].fi, 'a' + p[i].sc);
		cout << t << '\n';
	}
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
