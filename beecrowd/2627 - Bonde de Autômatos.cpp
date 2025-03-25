#include "bits/stdc++.h"
#define endl '\n'

using namespace std;
const int inf = 1e9;

void solve() {
	int n, k;
	string s;
	
	cin >> n >> k >> s;
	
	if(cin.eof()) exit(0);
	
	array<int, 26> dp;
	
	dp.fill(-inf);
	dp[0] = 0;
	
	for(char ch : s) {
		array<int, 26> _;
		_.fill(-inf);
		for(int j = 0; j <= ch - 'a'; ++j) _[ch - 'a'] = max(_[ch - 'a'], dp[j] + 26 - (ch - 'a'));
		for(int j = 0; j < 26; ++j) dp[j] = max(dp[j], _[j]);
	}
	
	cout << (*max_element(dp.begin(), dp.end()) >= k ? "Aceita" : "Rejeita") << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(1) solve();
	return 0;
}