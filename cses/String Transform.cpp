#include "bits/stdc++.h"
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s;
	vector<int> a[26];
	int pos = 0, cnt[27];
	cin >> s;
	string p = s, ans((int)s.size() - 1, '#');
	sort(p.begin(), p.end());
	for(int k = 0; k < (int)s.size(); ++k) if(s[k] != '#') a[s[k] - 'a'].push_back(k);
	cnt[0] = 1;
	for(int k = 1; k <= 26; ++k) cnt[k] = cnt[k - 1] + (int)a[k - 1].size();
	for(int k = (int)s.size() - 2; k >= 0; --k) {
		int ch = s[pos] - 'a';
		ans[k] = s[pos];
		pos = cnt[ch] + (lower_bound(a[ch].begin(), a[ch].end(), pos) - a[ch].begin());
	}
	cout << ans << '\n';		  
	return 0;
}
