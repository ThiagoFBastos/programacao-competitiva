#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 1e5 + 10;

int frq[N];
string s;

int vowel(char c) {
	char v[] = "aeiou";
	return count(v, v + 5, c) > 0;
}

int rec(int l, int r) {
	if(l == r) return 1;
	if(!vowel(s[l])) return frq[max(l,r)+1] - frq[min(l,r)] == 0;
	else if(vowel(s[r])) return rec(r, l += (l < r ? 1 : -1));
	return rec(l, r + (l < r ? -1 : 1)) + rec(r, l + (l < r ? 1 : -1)); 
}

void solve() {
	cin >> s;
	for(int i = 1; i <= (int)s.size(); ++i) frq[i] = frq[i - 1] + vowel(s[i - 1]);
	cout << rec(0, (int)s.size() - 1) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}