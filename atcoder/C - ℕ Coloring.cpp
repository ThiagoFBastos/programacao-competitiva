#include "bits/stdc++.h"
#define endl '\n'

using namespace std;

void solve() {
	int n;
	cin >> n;
	vector<int> a(n + 1, -1);
	a[1] = 1;
	
	for(int k = 1; k <= n; ++k)
	for(int j = 2 * k; j <= n; j += k)
		a[j] = max(a[j], a[k] + 1);
		
	for(int i = 1; i <= n; ++i) cout << a[i] << ' ';
	cout << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}

