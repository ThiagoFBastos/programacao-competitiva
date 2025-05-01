#include "bits/stdc++.h"
using namespace std;
void solve() {
	int n;
	string a, b;
	cin >> n >> a >> b;
	n &= 1;
	for(int i = 0; i < size(a); ++i) a[i] ^= n;
	cout << (a == b ? "Deletion succeeded\n" : "Deletion failed\n");
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}