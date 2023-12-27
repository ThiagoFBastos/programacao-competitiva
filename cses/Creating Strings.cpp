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
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s;
	vector<string> w;
	cin >> s;
	sort(s.begin(), s.end());
	do {
		w.push_back(s);
	} while(next_permutation(s.begin(), s.end()));
	cout << w.size() << '\n';
	for(string s : w) cout << s << '\n';
	return 0;
} 
