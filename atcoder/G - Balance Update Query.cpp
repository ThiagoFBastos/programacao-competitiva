#include "bits/stdc++.h"

using namespace std;

#define INF    1000000000
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

const int N = 4e5 + 10;

i64 quota[N], score[N], total;
int n, q;
vector<int> coords;

void upd(int x, int y, int z) {
	int k = lower_bound(all(coords), x) - coords.begin();
	k = (int)coords.size() - k;
	total += y * z;
	for(int i = k; i <= (int)coords.size(); i += i & -i) {
		quota[i] += y * z;
		score[i] += (i64)y * x * z;
	}
}

i64 get(i64 x) {
	if(total < x) return -1;
	i64 sum = 0;
	int i = 0, n = coords.size();
	for(int k = 31 - __builtin_clz(n); k >= 0; --k) {
		int j = i | (1 << k);
		if(j > n) continue;
		else if(quota[j] < x) {
			sum += score[j];
			x -= quota[j];
			i = j;
		}
	}
	i = n - i - 1;
	return sum + (i64)x * coords[i];
}

void solve() {

	cin >> n;

	vector<int> a(n), b(n);

	for(int i = 0; i < n; ++i) {
		cin >> a[i] >> b[i];	
		coords.pb(a[i]);
	}
	
	cin >> q;

	vector<tuple<int,int,int>> query(q);

	for(auto& [t, x, y] : query) {
		cin >> t >> x;
		if(t != 3) cin >> y;
		if(t == 1) coords.pb(y);
	}

	sort(all(coords));

	for(int i = 0; i < n; ++i) upd(a[i], b[i], 1);
	
	for(auto [t, x, y] : query) {
		if(t == 1) {
			upd(a[x-1],b[x-1], -1);
			a[x-1]=y;
			upd(a[x-1], b[x-1], 1);
		} else if(t == 2) {
			upd(a[x-1],b[x-1], -1);
			b[x-1]=y;
			upd(a[x-1], b[x-1], 1);
		} else 
			cout << get(x) << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}
