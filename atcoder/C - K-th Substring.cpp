#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	string s;
	int k;
	cin >> s >> k;

	vector<string> A;
	int n = s.size();

	for(int i = 0; i < n; ++i) {
		string pat;
		for(int j = i; j < n && j - i + 1 <= k; ++j) {
			pat += s[j];
			A.push_back(pat);
		}
	}

	sort(A.begin(), A.end());
	A.resize(unique(A.begin(), A.end()) - A.begin());

	cout << A[k-1] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
 
