#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	long long **f, A, B;
	string S;
	vector<int> b;
	cin >> A >> B >> S;	
	n = S.size();
	for(int i = 0; i < n; ++i)
		if(S[i] == 'B')
			b.push_back(i);
	int m = b.size();
	if(m == 0 || m == n) {
		cout << "0\n";
		return 0;
	}
	f = new long long*[m];
	for(int i = 0; i < m; ++i) {
		f[i] = new long long[m];
		for(int k = 0; k < m; ++k)
			f[i][k] = 5e9;
	}
	f[0][m - 1] = 0;
	for(int k = m - 1, j = 0; k > 0; --k, ++j) {
		for(int i = 0; i <= m - k; ++i) {
			if(i + k < m) f[i][i + k - 1] = min(f[i][i + k - 1] , f[i][i + k] + A);
			if(i && b[i - 1] >= j) f[i][i + k - 1] = min(f[i][i + k - 1], f[i - 1][i + k - 1] + min((b[i - 1] - j) * (A - B), A));
		}
	}
	long long res = LLONG_MAX;
	for(int i = 0; i < m; ++i)
		if(b[i] >= m - 1)
			res = min(res, f[i][i] + min((b[i] - m + 1) * (A - B), A));
	cout << res << '\n';
	return 0;
}