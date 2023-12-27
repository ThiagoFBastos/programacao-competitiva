#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse,sse2,sse3,sse4,avx,avx2")
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define MAXN 26
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s;
	int count[MAXN] = {0}, c = 0;
	cin >> s;
	for(char c : s) ++count[c - 'A'];
	for(int i = 0; i < 26; ++i) if(count[i] & 1) ++c;
	string ans = s;
	int lo = 0, hi = (int)s.size() - 1;
	if(s.size() & 1) {
		if(c == 1) {
			for(int i = 0; i < 26; ++i) {
				int n = count[i] / 2;
				for(int j = 0; j < n; ++j) ans[hi--] = ans[lo++] = i + 'A';
			}
			for(int i = 0; i < 26; ++i) if(count[i] & 1) {ans[lo] = i + 'A'; break;}
			cout << ans << '\n';
		}
		else cout << "NO SOLUTION\n";
	} else if (c) cout << "NO SOLUTION\n";
	else {
		for(int i = 0; i < 26; ++i) {
			int n = count[i] / 2;
			for(int j = 0; j < n; ++j) ans[hi--] = ans[lo++] = i + 'A';
		}
		cout << ans << '\n';
	}
	return 0;
} 
