#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

const int N = 2e5 + 100;

int cnt[N], q;
i64 sum[N], S;

void upd(int k, int x) {
	for(++k; k <= q; k += k & -k) {
		++cnt[k];
		sum[k] += x;
	}
}

int kth(int k) {
	int i = 0, n = 0;
	for(int j = 31 - __builtin_clz(q); j >= 0; --j) {
		int to = i | (1 << j);
		if(to > q || n + cnt[to] >= k) continue;
		n += cnt[to];
		i = to;
	}
	return i;
}

i64 query_sum(int k) {
	i64 ans = 0;
	for(++k; k > 0; k -= k & -k) ans += sum[k];
	return ans;
}

i64 query_sum(int l, int r) {
	return query_sum(r) - query_sum(l - 1);
}

int query_cnt(int k) {
	int ans = 0;
	for(++k; k > 0; k -= k & -k) ans += cnt[k];
	return ans;
}

int query_cnt(int l, int r) {
	return query_cnt(r) - query_cnt(l - 1);
}

void solve() {
	cin >> q;
	
	vector<tuple<int, int, int>> query(q);
	vector<int> x;
	int n = 0;

	for(auto& [t, a, b] : query) {
		cin >> t;
		if(t == 1) {
			cin >> a >> b;
			x.push_back(a);
		}
	}

	sort(x.begin(), x.end());
	
	auto f = [&](int k) {
		i64 L = query_cnt(k);
		i64 R = n - L;
		i64 LS = query_sum(k);
		i64 RS = query_sum(k + 1, q - 1);
		return S + RS - LS + x[k] * (L - R);
	};

	for(auto [t, a, b] : query) {
		if(t == 1) {
			int i = lower_bound(x.begin(), x.end(), a) - x.begin();
			S += b;
			upd(i, a);
			++n;
		} else {
			int y = kth((n + 1) / 2);
			if(n & 1) cout << x[y] << ' ' << f(y) << '\n';
			else {
				i64 L = f(y), R = f(y + 1);
				if(L <= R) cout << x[y] << ' ' << L << '\n';
				else cout << x[y + 1] << ' ' << R << '\n';
			}
		}
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
