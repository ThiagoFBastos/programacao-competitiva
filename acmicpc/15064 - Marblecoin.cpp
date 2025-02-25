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

const int N = 5e5 + 500, MOD = 1e9 + 7;

int tsa[N], c[N], tc[N], head[N], sa[N], str[N], lo[N], inv[N];

void bucket(int sa[], int n, int L) {
	memset(head, 0, sizeof head);

	for(int i = 0; i < n; ++i) ++head[c[i]];

	int maxi = n + 301, k = 0;

	for(int i = 0; i < maxi; ++i) {
		swap(k, head[i]);
		k += head[i];
	}

	for(int i = 0; i < n; ++i) {
		int j = (sa[i] - L + n) % n;
		tsa[head[c[j]]++] = j;
	}

	memcpy(sa, tsa, n * sizeof(int));
}

void suffixArray(int s[], int n, int sa[]) {
	
	for(int i = 0; i < n; ++i) {
		sa[i] = i;
		c[i] = s[i];
	}

	bucket(sa, n, 0);

	for(int L = 1; L < n; L <<= 1) {
		bucket(sa, n, L);
		for(int i = 0, cc = -1; i < n; ++i)
			tc[sa[i]] = !i || c[sa[i]] != c[sa[i - 1]] || c[(sa[i] + L) % n] != c[(sa[i - 1] + L) % n] ? ++cc : cc;
		memcpy(c, tc, n * sizeof(int));
	}
}

void solve() {

	int n, j = 0, ans = 0;
	priority_queue<ii> pq;

	cin >> n;

	for(int i = 0; i < n; ++i) {
		int m;
		cin >> m;
		lo[i] = j;
		while(m--) {
			int v;
			cin >> v;
			str[j++] = v;
		}
		str[j++] = 301 + i;
	}

	suffixArray(str, j, sa);

	for(int i = 0; i < j; ++i) inv[sa[i]] = i;

	for(int i = 0; i < n; ++i) pq.emplace(-inv[lo[i]], i);

	while(!pq.empty()) {
		auto [_, i] = pq.top(); pq.pop();
		ans = (ans + str[lo[i]]) * 365ll % MOD;
		if(str[++lo[i]] <= 300) pq.emplace(-inv[lo[i]], i);
	}

	cout << ans << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
 	//cin >> t;
    while(t--) solve();
    return 0;
}

