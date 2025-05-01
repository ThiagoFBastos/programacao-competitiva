#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 1;
int bit[N];

void upd(int k, int x) {
	for(; k < int(size(bit)); k += k & -k) bit[k] += x;
}

int query(int k) {
	int ans {};
	for(; k > 0; k -= k & -k) ans += bit[k];
	return ans;
}

void solve() {
	int n;
	cin >> n;
	if(!n) exit(0);

	int cnt {};
	
	memset(bit, 0, (n + 1) * sizeof(int));
	
	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		cnt += i - query(a);
		cnt &= 1;
		upd(a, 1);
	}
	
	cout << (cnt ? "Marcelo\n" : "Carlos\n");
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(1) solve();
	return 0;
}