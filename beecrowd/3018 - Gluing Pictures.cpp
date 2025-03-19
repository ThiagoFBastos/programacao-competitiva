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

int mod_sum(int x, int n) {
	return x >= n ? x - n : x;
}

auto suffix_array(string& s) {
	s += "$";
	
	int n = size(s), m, g;
	
	vector<int> p[2], ord[2], cnt(max(n, 128));
	
	for(int i = 0; i < 2; ++i) {
		p[i].resize(n);
		ord[i].resize(n);
	}
	
	fill(cnt.begin(), cnt.begin() + 128, 0);
	
	for(char ch : s) ++cnt[ch];
	for(int i = 1; i < 128; ++i) cnt[i] += cnt[i - 1];
	for(int i = 0; i < n; ++i) p[0][--cnt[s[i]]] = i;

	ord[0][p[0][0]] = 0;
	
	for(int i = 1; i < n; ++i) {
		int pre = p[0][i - 1], cur = p[0][i];
		ord[0][cur] = ord[0][pre] + (s[cur] != s[pre]);
	}
	
	m = ord[0][p[0].back()] + 1;
	
	for(g = 0; (1 << g) < n; ++g) {
		int Old = g & 1, New = ~g & 1;
		
		fill(cnt.begin(), cnt.begin() + m, 0);
		
		for(int i = 0; i < n; ++i) ++cnt[ord[Old][i]];
		for(int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
		
		for(int i = n - 1; i >= 0; --i) {
			int j = mod_sum(p[Old][i] - (1 << g) + n, n);
			p[New][--cnt[ord[Old][j]]] = j;
		}
		
		ord[New][p[New][0]] = 0;
		
		for(int i = 1; i < n; ++i) {
			int pre = p[New][i - 1], cur = p[New][i];
			auto x = make_pair(ord[Old][pre], ord[Old][mod_sum(pre + (1 << g), n)]);
			auto y = make_pair(ord[Old][cur], ord[Old][mod_sum(cur + (1 << g), n)]);
			ord[New][cur] = ord[New][pre] + (x != y);
		}
		
		m = ord[New][p[New].back()] + 1;
	}
	
	g &= 1;
	s.pop_back();
	p[g].erase(p[g].begin());

	return p[g];
}

void solve() {

	string s;
	int q;

	cin >> s >> q;

	auto suf = suffix_array(s);

	int n = s.size();

	int lg = 31 - __builtin_clz(n);

	s += "$";

	while(q--) {
		string w;
		int ans = 0;

		cin >> w;

		int k = 0, m = w.size();

		while(k < m) {
			int i, lo = 0, hi = n - 1;

			++ans;

			for(i = k; i < m; ++i) {
				int L = lo, R = hi;

				for(int j = lg; j >= 0; --j) {
					int _L = L + (1 << j);
					int _R = R - (1 << j);
					if(_L <= R && s[suf[_L] + i - k] < w[i]) L = _L;
					if(_R >= L && s[suf[_R] + i - k] > w[i]) R = _R;
				}

				if(s[suf[L] + i - k] < w[i]) ++L;
				if(s[suf[R] + i - k] > w[i]) --R;

				if(L > R) break;
			
				lo = L, hi = R;
			}

			if(i == k) {
				ans = -1;
				break;
			}

			k = i;
		}

		cout << ans << '\n';
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