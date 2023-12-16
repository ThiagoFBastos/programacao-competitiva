#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s, t, p;
	cin >> s >> t;
	p = t + '.' + s;
	vector<int> K(p.size());
	K[0] = 0;
	for(int i = 1; i < p.size(); ++i) {
		int k = K[i - 1];
		while(k > 0 && p[k] != p[i]) k = K[k - 1];
		if(p[k] == p[i]) ++k;
		K[i] = k;
	}
	int cnt = 0;
	for(int i = t.size() + 1; i < p.size(); ++i) {
		if(K[i] == (int)t.size())
			++cnt;
	}
	cout << cnt << '\n';
	return 0;
}
