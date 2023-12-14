#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2,mmx")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;
 
template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;
 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
 
using vi = vector<int>;
using ii = pair<int, int>;
using li = pair<ll, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;
struct Line {
	int x1, x2, y1, y2, endpoint;
};
bool operator<(Line L1, Line L2) {
	return L1.x1 < L2.x1 || (L1.x1 == L2.x1 && L1.endpoint < L2.endpoint);
}
struct BIT {
	vi bit;
	BIT(int n) {
		bit.assign(n + 1, 0);
	}
	void upd(int k, int x) {
		while(k < (int)bit.size()) {
			bit[k] += x;
			k += k & -k;
		}
	}
	int query(int k) {
		int ans = 0;
		while(k > 0) {
			ans += bit[k];
			k -= k & -k;
		}
		return ans;
	}
	int query(int L, int R) {
		return query(R) - query(L - 1);
	}
};
int n;
vector<Line> H, V;
vi y;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	y.reserve(2 * n);
	for(int i = 0; i < n; ++i) {
		Line L;
		cin >> L.x1 >> L.y1 >> L.x2 >> L.y2;
		L.endpoint = 0;
		if(L.x1 == L.x2) V.push_back(L);
		else {
			H.push_back(L);
			L.x1 = L.x2, L.y1 = L.y2, L.endpoint = 1;
			H.push_back(L);
		}
		y.push_back(L.y1);
		y.push_back(L.y2);
	}
	sort(y.begin(), y.end());
	y.resize(unique(y.begin(), y.end()) - y.begin());
	sort(V.begin(), V.end());
	sort(H.begin(), H.end());
	ll cnt = 0;
	BIT bit(y.size());
	int k = 0;
	for(Line& L : V) {
		int y1, y2;
		while(k < (int)H.size() && H[k].x1 < L.x1) {
			y1 = 1 + lower_bound(y.begin(), y.end(), H[k].y1) - y.begin();
			H[k].endpoint ? bit.upd(y1, -1) : bit.upd(y1, 1);
			++k;
		}
		while(k < (int)H.size() && H[k].x1 == L.x1 && !H[k].endpoint) {
			y1 = 1 + lower_bound(y.begin(), y.end(), H[k].y1) - y.begin();
			bit.upd(y1, 1);
			++k;
		}
		y1 = 1 + lower_bound(y.begin(), y.end(), L.y1) - y.begin();
		y2 = 1 + lower_bound(y.begin(), y.end(), L.y2) - y.begin();
		cnt += bit.query(y1, y2);
	}
	cout << cnt << '\n';
	return 0;
}
