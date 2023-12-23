#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
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

void solve() {
	string s;
	int cnt = 0;

	cin >> s;

	for(char c : s) cnt += c != s.front() || c != s.back();

	if(cnt == 0) {
		cout << "Second\n";
		return;
	} if(cnt == 1) {
		for(int i = 1; i < (int)s.size() - 1; ++i) {
			if(s[i] != s.front() && s[i] != s.back() && s[i - 1] != s[i + 1]) {
				cout << "First\n";
				return;
			}
		}
	}

	if(s.front() == s.back()) cout << (((int)s.size() - 3) % 2 ? "First\n" : "Second\n");
	else cout << (((int)s.size() - 2) % 2 ? "First\n" : "Second\n");
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
