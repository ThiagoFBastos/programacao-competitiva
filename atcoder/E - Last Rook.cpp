#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;


int ask(int a, int b, int c, int d) {
	cout << "? " << a << ' ' << b << ' ' << c << ' ' << d << '\n';
	cout.flush();
	int cnt=0;
	cin >> cnt;
	if(cnt < 0) exit(0);
	return cnt;
}

int choose_row(int n) {
	int lo = 1, hi = n;
	while(lo < hi) {
		int mid = (lo + hi) / 2;
		if(ask(lo, mid, 1, n) == mid - lo + 1) lo = mid + 1;
		else hi = mid;
	}
	return hi;
}

int choose_col(int n) {
	int lo = 1, hi = n;
	while(lo < hi) {
		int mid = (lo + hi) / 2;
		if(ask(1, n, lo, mid) == mid - lo + 1) lo = mid + 1;
		else hi = mid;
	}
	return hi;
}

void solve() {
	int n;
	cin >> n;
	int r = choose_row(n);
	int c = choose_col(n);
	cout << "! " << r << ' ' << c << '\n';
	cout.flush();
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
 
