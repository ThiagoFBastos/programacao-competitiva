#pragma GCC optimize("O3")
#pragma GCC target("avx", "mmx", "sse", "sse2", "sse3", "sse4")

#include "bits/stdc++.h"
using namespace std;

void solve() {

	int r, c, a;
	cin >> r >> c >> a;

	if(r + c + a == 0) exit(0);
		
	vector<string> s(r);
	
	for(int i = 0; i < r; ++i) cin >> s[i];
	
	
	if(r < c) {
		vector<string> q(c);
		for(int j = 0; j < c; ++j)
		for(int i = 0; i < r; ++i)
			q[j] += s[i][j];
		s = q;
		swap(r, c);
	}
	
	vector<vector<int>> pre(r);
	
	for(int i = 0; i < r; ++i) {
		pre[i].resize(c + 1);
		pre[i][0] = 0;
		for(int j = 1; j <= c; ++j) pre[i][j] = (s[i][j - 1] == '.') + pre[i][j - 1];
	}
	
	int area = r * c + 1;
	
	for(int i = 0; i < c; ++i) {
		for(int L = 1; L + i - 1 < c; ++L) {
			int j = 0, cnt = 0;
			for(int k = 0; k < r; ++k) {
				cnt += pre[k][i + L] - pre[k][i];
				while(cnt - pre[j][i + L] + pre[j][i] >= a) {
					cnt -= pre[j][i + L] - pre[j][i];
					++j;
				}
				if(cnt >= a) area = min(area, (k - j + 1) * L);
			} 
		}
	}
	
	cout << area << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	while(true) solve();
	return 0;
}