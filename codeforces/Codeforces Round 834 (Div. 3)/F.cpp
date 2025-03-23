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

vector<int> add(vector<int> x, int y, int p) {	
	int n = x.size();
	x.back() += y;
	for(int i = n - 1; i && x[i] >= p; --i) {
		x[i - 1] += x[i] / p;
		x[i] %= p;
	}
	if(x[0] >= p) {
		x.insert(x.begin(), x[0] / p);
		x[1] %= p;
	}
	return x;
}

bool test(vector<ii>& a, int p) {
	sort(all(a));
	auto [l, r] = a[0];
	for(int j = 1; j < (int)a.size(); ++j) {
		if(a[j].fi <= r + 1) r = max(r, a[j].sc);
		else return false;
	}
	return l == 0 && r == p - 1;
}

void solve() {
	int n, p;

	cin >> n >> p;

	vector<int> x(n);
	
	for(int& v : x) cin >> v;

	int l = 0, r = p - x.back();

	while(l < r) {
		int m = (l + r) / 2;
		vector<ii> digits;
		for(int d : x) digits.pb({d, d});
		digits.pb({x.back(), x.back() + m});
		if(test(digits, p)) r = m;
		else l = m + 1;
	}

	if(r < p - x.back()) {
		cout << r << '\n';
		return;
	}

	int ans = p - x.back();
	vector<ii> others;

	others.pb({x.back(), p - 1});
	for(int d : x) others.pb({d, d});
	
	x = add(x, p - x.back(), p);

	l = 0, r = p - 1;

	while(l < r) {
		int m = (l + r) / 2;
		vector<ii> digits = others;
		for(int d : x) digits.pb({d, d});
		digits.pb({x.back(), x.back() + m});
		if(test(digits, p)) r = m;
		else l = m + 1;
	}

	ans += l;
	cout << ans << '\n';
}
 
int main() {
    ios_base :: sync_with_stdio(false);
   	cin.tie(0);
    int t = 1;
 	cin >> t;
    while(t--) solve();
    return 0;
}
