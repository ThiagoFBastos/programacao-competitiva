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
 
template<class T>
struct BIT {
	vector<T> bit;
	
	BIT(){}
	
	BIT(int n) {
		bit.assign(n + 1, 0);
	}
	
	void upd(int k, T x) {
		for(++k; k < int(bit.size()); k += k & -k) bit[k] += x;
	}
	
	T query(int k) {
		T ans {};
		for(++k; k > 0; k -= k & -k) ans += bit[k];
		return ans;
	}
	
	T query(int l, int r) {
		if(l > r) return (T)0;
		return query(r) - query(l - 1);
	}
};
 
using T = tuple<int, int, int>;
 
const int chunk_sz = 500, chunks = 300;
 
BIT<int> ordered_set[chunks];
vector<int> S[chunks];
vector<T> a;
int n, q;
 
bool cmp(T a, T b) {
	return get<0>(a) + get<1>(a) < get<0>(b) + get<1>(b);
}
 
void upd(int x, int y, int z) {
	int i = lower_bound(a.begin(), a.end(), make_tuple(x, y, z)) - a.begin();
	int j = lower_bound(S[i / chunk_sz].begin(), S[i / chunk_sz].end(), y) - S[i / chunk_sz].begin();
	ordered_set[i / chunk_sz].upd(j, 1);
}
 
int query(int x, int y, int z) {
	int k = lower_bound(a.begin(), a.end(), make_tuple(x, -1, -1)) - a.begin();
	int j = k / chunk_sz, ans = 0;
	
	for(int i = k; i < min(n, (j + 1) * chunk_sz); ++i) {
		auto [s, t, _] = a[i];
		if(s + t >= z && t >= y) ++ans;
	}
	
	int c = (n + chunk_sz - 1) / chunk_sz;
	
	for(++j; j < c; ++j) {
		int i = lower_bound(S[j].begin(), S[j].end(), y) - S[j].begin();
		ans += ordered_set[j].query(i, (int)S[j].size() - 1);
	}
	
	return ans;
}
 
void solve() {
 
	cin >> n >> q;
	
	vector<T> b(n);
	vector<int> ans(q);
	vector<tuple<int, int, int, int>> Q(q);
	
	a.resize(n);
	
	for(int i = 0; i < n; ++i) {
		int s, t;
		cin >> s >> t;
		b[i] = a[i] = {s, t, i};
	}
	
	sort(a.begin(), a.end());
	
	for(int i = 0; i < n; ++i) S[i / chunk_sz].push_back(get<1>(a[i]));
	
	for(int i = 0; i < chunks; ++i) {
		ordered_set[i] = BIT<int>(size(S[i]));
		sort(S[i].begin(), S[i].end());
	}
	
	for(int i = 0; i < q; ++i) {
		int x, y, z;
		cin >> x >> y >> z;
		Q[i] = {z, x, y, i};
	}
	
	b.emplace_back(-1, -1, -1);
	sort(b.rbegin(), b.rend(), cmp);
	sort(Q.rbegin(), Q.rend());
	
	int i = 0, j = 0;
	
	while(j < q) {
		auto [s, t, k] = b[i];
		auto [z, x, y, pos] = Q[j];
		if(s + t >= z) {
			upd(s, t, k);
			++i;
		} else {
			ans[pos] = query(x, y, z);
			++j;
		}
	}
	
	for(int x : ans) cout << x << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
