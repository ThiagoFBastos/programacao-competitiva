#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 2e5 + 10;
const int K = 18;

template<int MAXN>
struct SuffixArray {

	int sa[MAXN], tmpSA[MAXN], ord[MAXN], tmpOrd[MAXN], lcp[MAXN], table[MAXN], cnt[MAXN];

	int mod_sum(int x, int n) {
		return x >= n ? x - n : x;
	}

	void suffix_array(string& s) {
		s += "$";
		
		int n = s.size();
		
		memset(cnt, 0, 128 * sizeof(int));
		for(char ch : s) ++cnt[ch];
		for(int i = 1; i < 128; ++i) cnt[i] += cnt[i - 1];
		for(int i = 0; i < n; ++i) sa[--cnt[s[i]]] = i;

		ord[sa[0]] = 0;
		
		for(int i = 1; i < n; ++i) {
			int pre = sa[i - 1], cur = sa[i];
			ord[cur] = ord[pre] + (s[cur] != s[pre]);
		}
		
		int m = ord[sa[n - 1]] + 1;
		
		for(int l = 0; (1 << l) < n; ++l) {
			memset(cnt, 0, sizeof(int) * m);
			
			for(int i = 0; i < n; ++i) ++cnt[ord[i]];
			for(int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
			
			for(int i = n - 1; i >= 0; --i) {
				int j = mod_sum(sa[i] - (1 << l) + n, n);
				tmpSA[--cnt[ord[j]]] = j;
			}
			
			tmpOrd[tmpSA[0]] = 0;
			
			for(int i = 1; i < n; ++i) {
				int pre = tmpSA[i - 1], cur = tmpSA[i];
				auto x = make_pair(ord[pre], ord[mod_sum(pre + (1 << l), n)]);
				auto y = make_pair(ord[cur], ord[mod_sum(cur + (1 << l), n)]);
				tmpOrd[cur] = tmpOrd[pre] + (x != y);
			}

			for(int i = 0; i < n; ++i) {
				swap(sa[i], tmpSA[i]);
				swap(ord[i], tmpOrd[i]);
			}

			m = ord[sa[n - 1]] + 1;
		}
		
		s.pop_back();
		
		for(int i = 1; i < n; ++i) sa[i - 1] = sa[i];
	}

	void LCP(string& s) {
		int n = s.size(), match = 0;

		suffix_array(s);

		for(int i = 0; i < n; ++i) table[sa[i]] = i;
		
		for(int i = 0; i < n; ++i) {
			if(table[i]) {
				int k = i + match, j = sa[table[i] - 1] + match;
				while(k < n && j < n && s[k] == s[j]) ++k, ++j;
				match = k - i;
			}
			lcp[table[i]] = match;
			match = max(0, match - 1);
		}
	}
};

SuffixArray<N> sa;
i64 F[N];

int sp[K][N], n, q;
string s;

int query(int l, int r) {
	int k = 31 - __builtin_clz(r - l + 1);
	return min(sp[k][l], sp[k][r - (1 << k) + 1]);
}

int lcp(int l, int r) {
	return l == r ? n - sa.sa[l] : query(l + 1, r);
}

void rec(int k, int l, int r) {
	if(l > r) return;
	else if(l == r) F[1] += n - sa.sa[l] - k;
	else {
		int L = lcp(l, r);
		F[r - l + 1] += (L - k) * (r - l + 1ll);
		while(l <= r) {
			int lo = l + 1, hi = r + 1;
			while(lo < hi) {
				int mid = (lo + hi) / 2;
				if(lcp(l, mid) == L) hi = mid;
				else lo = mid + 1;
			}
			rec(L, l, hi - 1);
			l = hi;
		}
	}
}

void solve() {

	cin >> s >> q;

	n = s.size();
	
	sa.LCP(s);

	for(int i = 0; i < n; ++i) sp[0][i] = sa.lcp[i];

	for(int i = 1; (1 << i) <= n; ++i)
	for(int j = 0; j + (1 << i) <= n; ++j)
		sp[i][j] = min(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]);

	memset(F, 0, (n + 1) * sizeof(i64));
	rec(0, 0, n - 1);
	
	for(int i = n - 1; i; --i) F[i] += F[i + 1];
	
	while(q--) {
		int f;
		cin >> f;
		cout << (f > n ? 0 : F[f]) << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}