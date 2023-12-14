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
 
const int N = 2e5 + 10, B = 448;
const i64 LINF = 200'000'000'000'010ll;
 
i64 sumc[B], sum[N], mx[B];
int n, m, q;
vector<i64> coords;
 
inline i64 hilbertOrder(int x, int y, int pow, int rotate = 0) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	i64 subSquareSize = 1ll << (2*pow - 2);
	i64 ans = seg * subSquareSize;
	i64 add = hilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}
 
void add(int k) {
	sum[k] += coords[k];
	sumc[k/B] += coords[k];	
}
 
void rem(int k) {
	sum[k] -= coords[k];
	sumc[k/B] -= coords[k];	
}
 
int main(int argc, char* argv[]) {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
 
	cin >> n >> q;
 
	vector<i64> a(n);
 
	for(i64& v : a) cin >> v;
 
	coords = a;
	coords.pb(LINF);
	coords.pb(1);
	sort(all(coords));
	coords.resize(unique(all(coords)) - coords.begin());
 
	m = coords.size();
 
	for(int i = 0; i < m; ++i) mx[i/B] = max(mx[i/B],coords[i]);
 
	for(i64& v : a) v = lower_bound(all(coords), v) - coords.begin();
	
	int lo = 0, hi = -1;
	vector<tuple<i64, int, int, int>> queries(q);
	vector<i64> ans(q);
 
	for(int i = 0; i < q; ++i) {
		int l, r;
		cin >> l >> r;
		--l, --r;
		queries[i] = {hilbertOrder(l, r, 18), l, r, i};
	}
 
	sort(all(queries));
 
	for(auto [_, l, r, id] : queries) {
		if(lo <= l) {
			while(hi < r) add(a[++hi]);
			while(hi > r) rem(a[hi--]);
			while(lo < l) rem(a[lo++]);
			while(lo > l) add(a[--lo]);
		} else {
			while(lo > l) add(a[--lo]);
			while(lo < l) rem(a[lo++]);
			while(hi > r) rem(a[hi--]);
			while(hi < r) add(a[++hi]);
		}
 
		i64 cur = 0;
 
		for(int i = 0; i * B < m; ++i) {
			if(cur >= mx[i] || cur >= INF) cur += sumc[i];
			else {
				bool found = false;
				for(int j = 0; j < B && i*B+j < m; ++j) {
					if(cur + 1 < coords[i*B+j]) {
						ans[id] = cur + 1;
						found = true;
						break;
					}
					cur += sum[i*B+j];
				}
				if(found) break;
			}
		}
		
		if(cur >= INF) ans[id] = cur + 1;
	}
 
	for(i64 v : ans) cout << v << '\n';
 
	return 0;
}
