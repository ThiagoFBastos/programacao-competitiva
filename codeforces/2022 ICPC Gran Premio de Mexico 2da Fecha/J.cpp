#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
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
using i128 = __int128;

const int N = 1e3 + 10;
int n, k, frq[26];
char s[N];

i64 count(int L) {
	if(L == 0) return 1;
	i64 cnt = 0;
	for(int i = 0; i < 26; ++i) {
		if(!frq[i]) continue;
		--frq[i];
		cnt += count(L - 1);
		++frq[i];
	}
	return cnt;
}

void brute(int p, int l) {
	if(p > l) return;
	else if(p == l) {
		if(--k == 0) {
			s[p] = '\0';
			cout << s << '\n';
			exit(0);
		}
	}
	for(int i = 0; i < 26; ++i) {
		if(!frq[i]) continue;
		--frq[i];
		s[p] = i + 'a';
		brute(p + 1, l);
		++frq[i];
	}
}

void solve() {
	
	cin >> n >> k >> s;

	for(int i = 0; i < n; ++i) ++frq[s[i] - 'a'];

	int l = 0;

	while(true) {
		++l;
		i64 m = count(l);
		if(k <= m) break;			
		k -= m;
	}
	
	brute(0, l);
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
s
