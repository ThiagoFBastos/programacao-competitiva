#include "bits/stdc++.h"

using namespace std;

string t = "AEIOU";

bool vowel(char k) {
	for(char ch : t) if(ch == k) return true;
	return false;
}

void solve() {
	string s;
	int cnt[26] = {0}, ans = INT_MAX;
	
	cin >> s;
	
	for(char ch : s) ++cnt[ch - 'A'];
	
	for(int c = 0; c < 26; ++c) {
		int swaps = 0;
		if(vowel(c + 'A')) {
			for(int k = 0; k < 26; ++k) {
				if(c == k) continue;
				else if(vowel(k + 'A')) swaps += 2 * cnt[k];
				else swaps += cnt[k];
			}
		} else {
			for(int k = 0; k < 26; ++k) {
				if(c == k) continue;
				else if(vowel(k + 'A')) swaps += cnt[k];
				else swaps += 2 * cnt[k];
			}
		}
		ans = min(ans, swaps);
	}
	
	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	for(int k = 1; k <= t; ++k) {
		cout << "Case #" << k << ": ";
		solve();
	}
 	return 0;
}
