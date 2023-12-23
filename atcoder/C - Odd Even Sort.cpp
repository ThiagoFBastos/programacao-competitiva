#include "bits/stdc++.h"
#define endl '\n'

using namespace std;

void solve() {
	int n;
	cin >> n;
	vector<int> a(n), b;
	int inv = 0;
	
	for(int i = 0; i < n; ++i) cin >> a[i];
	
	for(int i = 0; i < n; ++i)
	for(int j = i + 1; j < n; ++j)
		inv += a[i] > a[j];
		
	for(int k = 0; k < n * n && inv > 0; ++k) {
		int pos = -1;
		
		for(int j = n - 2; j >= 0; --j) {
			if((j & 1) == (k & 1) && a[j] > a[j + 1]) {
				pos = j;
				break;
			}
		}
		
		if(pos == -1) {
			++inv;
			pos = k & 1;
		} else --inv;

		swap(a[pos], a[pos + 1]);
		b.push_back(1 + pos);
	}
	
	cout << size(b) << endl;
	for(int v : b) cout << v << ' ';
	cout << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}

