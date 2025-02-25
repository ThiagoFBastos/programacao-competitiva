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
using i128 = __int128;

template<int N>
struct SuffixArray {
	int tsa[N], c[N], tc[N], head[N], inv[N], sa[N], lcp[N], length;
	char str[N];

	void bucket(int n, int L) {
		memset(head, 0, sizeof head);

		for(int i = 0; i < n; ++i) ++head[c[i]];

		int maxi = max(300, n), k = 0;

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

	void suffixarray() {
		int n = length + 1;
		for(int i = 0; i < n; ++i) {
			sa[i] = i;
			c[i] = str[i];
		}
		bucket(n, 0);
		for(int L = 1; L < n; L <<= 1) {
			bucket(n, L);
			for(int i = 0, cc = -1; i < n; ++i)
				tc[sa[i]] = !i || c[sa[i]] != c[sa[i - 1]] || c[(sa[i] + L) % n] != c[(sa[i - 1] + L) % n] ? ++cc : cc;
			memcpy(c, tc, n * sizeof(int));
		}
		for(int i = 0; i < n - 1; ++i) sa[i] = sa[i + 1];
	}

	void computeLCP() {
		int k = 0;
		for(int i = 0; i < length; ++i) inv[sa[i]] = i;
		for(int j = 0; j < length; ++j) {
			int i = inv[j];
			while(i > 0 && str[sa[i] + k] == str[sa[i - 1] + k]) ++k;
			lcp[i] = k;
			k = max(k - 1, 0);
		}
	}

	int lower_bound(const char* target) {
		int n = strlen(target), l = 0, r = length - 1;
		while(l < r) {
			int m = (l + r) / 2, i = sa[m], j = 0;
			while(i < length && j < n && str[i] == target[j]) ++i, ++j;
			if(str[i] >= target[j]) r = m;
			else l = m + 1;
		}
		return r;
	}

	SuffixArray() {}

	SuffixArray(const char* _str) {
		build(_str);
	}

	void build(const char* _str) {
		length = strlen(_str);
		strcpy(str, _str);
		suffixarray();
	}
};

struct op {
	i64 operator()(i64 a, i64 b) {
		return a | b;
	}
};

template<class T, class op>
struct SegTree {
	vector<T> st;
	const T neutral = 0;

	SegTree() {}
	
	SegTree(int n) {
		st.assign(2 * n, neutral);
	}
	
	SegTree(vector<T>& a) {
		int n = a.size();
		st.resize(2 * n);
		for(int k = n; k < 2 * n; ++k) st[k] = a[k - n];
		for(int k = n - 1; k > 0; --k) st[k] = op()(st[2 * k], st[2 * k + 1]);
	}
	
	void upd(int k, T x) {
		k += st.size() / 2;
		st[k] = x;
		for(k /= 2; k > 0; k /= 2) st[k] = op()(st[2 * k], st[2 * k + 1]);
	}
	
	T query(int l, int r) {
		T ans = neutral;	
		int n = st.size() / 2;
		for(l += n, r += n; l <= r; l /= 2, r /= 2) {
			if(l & 1) ans = op()(ans, st[l++]);
			if(~r & 1) ans = op()(ans, st[r--]);
		}
		return ans;
	}
};

const int N = 6e5 + 100;

char str[N];
int cur = 0, suf[N], lo[N], hi[N], who[N];
SuffixArray<N> sa;

void solve() {
	int n;

	while(true) {
		cin >> n;

		if(!n) break;

		vector<i64> st;
	
		cur = 0;

		for(int i = 0; i < n; ++i) {
			string s;
			cin >> s;
			int l = s.size();
			for(char c : s) {
				suf[cur] = l--;	
				who[cur] = i;
				str[cur++] = c;
			}
			who[cur] = n;
			suf[cur] = 0;
			str[cur++] = 32 + i;	
		}

		SegTree<i64, op> seg(cur);

		str[cur] = '\0';
	
		sa.build(str);
		sa.computeLCP();

		deque<ii> dq;

		for(int i = 0; i < cur; ++i) {
			ii x(sa.lcp[i], i);
			while(!dq.empty() && dq.back().fi >= x.fi) dq.pop_back();
			lo[i] = dq.empty() ? 0 : dq.back().sc;
			dq.pb(x);
			seg.upd(i, 1ll<<who[sa.sa[i]]);
		}

		dq.clear();

		for(int i = cur - 1; i >= 0; --i) {
			ii x(sa.lcp[i], i);
			while(!dq.empty() && dq.back().fi >= x.fi) dq.pop_back();
			hi[i] = dq.empty() ? cur - 1 : dq.back().sc - 1;
			dq.pb(x);
		}

		for(int i = 0; i < cur; ++i) {
			int k = sa.sa[i];
			if(sa.lcp[i]) st.pb(seg.query(lo[i], hi[i]));
			if(sa.lcp[i] < suf[k] && (i + 1 == cur || sa.lcp[i + 1] < suf[k])) st.pb(1ll << who[k]);
		}

		sort(all(st));
		st.resize(unique(all(st)) - st.begin());
		cout << st.size() << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
