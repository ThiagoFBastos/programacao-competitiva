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
	string r1, r2, r3, r4;
	cin >> r1 >> r2 >> r3 >> r4;
	map<string, int> f;
	f["-F"] = 0;
	f["-Cl"] = -1;
	f["-Br"] = -2;
	f["-I"] = -3;
	f["-CH3"] = -4;
	f["-CH2CH3"] = -5;
	f["-CH2CH2CH3"] = -6;
	f["-H"] = -7;
	if(r1 == r3 || r2 == r4) cout << "None\n";
	else if(r1 == r2 || r3 == r4) cout << "Cis\n";
	else if(r1 == r4 || r2 == r3) cout << "Trans\n";
	else if((f[r1] > f[r3]) == (f[r2] > f[r4])) cout << "Zasamman\n";
	else cout << "Entgegen\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	cin >> t;
	while(t--) solve();
	return 0;
}
 
