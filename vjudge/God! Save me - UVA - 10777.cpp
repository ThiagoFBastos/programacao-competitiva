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

int tcase = 1;

void solve() {
	int n;

	cin >> n;
	
	double k = 0, s = 0;

	vector<double> t(n), p(n);
	bool out = false;

	for(int i = 0; i < n; ++i) {
		cin >> t[i] >> p[i];
		if(t[i] > 0) {
			k += p[i];
			s += p[i] * t[i];
			out = true;
		} else
			s -= t[i] * p[i];
	}

	cout.precision(2);
	cout.setf(ios_base :: fixed);
	cout << "Case " << tcase++ << ": ";

	if(!out) {
		cout << "God! Save me\n";
		return;
	}

	cout << s / k << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
 	cin >> t;
    while(t--) solve();
    return 0;
}

