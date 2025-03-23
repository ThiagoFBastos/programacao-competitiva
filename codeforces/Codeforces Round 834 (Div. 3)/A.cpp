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

	cin >> s;

	for(char& c : s) {
		if(c == 'Y') c = '0';
		else if(c == 'e') c = '1';
		else if(c == 's') c = '2';
		else {
			cout << "NO\n";
			return;
		}
	}

	bool flag = true;
	for(int i = 1; i < (int)s.size(); ++i) flag = flag && (s[i] - s[i - 1] + 3) % 3 == 1;
	cout << (flag ? "YES\n" : "NO\n");	
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
 	cin >> t;
    while(t--) solve();
    return 0;
}


