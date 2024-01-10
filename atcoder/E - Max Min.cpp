#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	int n, x, y;
	
	cin >> n >> x >> y;

	vector<int> loMAX(n + 1), hiMAX(n + 1);
	vector<int> loMIN(n + 1), hiMIN(n + 1);
	vector<int> a(n);
	i64 ans = 0;

	for(int& v : a) cin >> v;

	loMAX.back() = -1;
	hiMAX.back() = n - 1;
	loMIN.back() = -1;
	hiMIN.back() = n - 1;

	for(int i = n - 1; i >= 0; --i) {
		loMAX[i] = loMAX[i + 1];
		hiMAX[i] = hiMAX[i + 1];
		loMIN[i] = loMIN[i + 1];
		hiMIN[i] = hiMIN[i + 1];

		if(a[i] == x) loMAX[i] = i;
		else if(a[i] > x) loMAX[i] = -1, hiMAX[i] = i - 1;
	
		if(a[i] == y) loMIN[i] = i;
		else if(a[i] < y) loMIN[i] = -1, hiMIN[i] = i - 1;

		if(loMAX[i] != -1 && loMIN[i] != -1) {
			int l = max(loMAX[i], loMIN[i]);
			int r = min(hiMAX[i], hiMIN[i]);
			if(l > r) continue;
			ans += r - l + 1;
		}
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
