#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
typedef long long ll;
typedef long double ld;
using namespace std;
using vi = vector<int>;
bool sub(string& a, string& b, int k) {
	int i = 0, j = 0, ct = 0, n = a.size(), m = b.size();
	while(i < n && j < m) {
		if(a[i] == b[j]) {
			++ct;
			if(ct == k) ct = 0, ++j;
		}
		++i;
	}
	return j == m;
}
int main() {
	ios_base :: sync_with_stdio(false); 
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		string a, b;
		int low, high;
		cin >> a >> b;
		low = 0;
		high = a.size() + 1;
		while(low < high) {
			int mid = (low + high) >> 1;
			if(sub(a, b, mid)) low = mid + 1;
			else high = mid;
		}
		cout << max(low - 1, 0) << '\n';
	}
	return 0;
}