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

const int N = 3010;

int pos[N], n, x;
i64 toleft[N][N], toright[N][N];

void solve() {

	cin >> n >> x;

	vector<tuple<int, int, int>> y;
	
	for(int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		y.pb({x, 1, i});
	}

	for(int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		y.pb({x, 0, i});
	}

	y.pb({x, -1, -1});
	y.pb({0, -1, -1});

	sort(all(y));

	for(int i = 0; i < (int)y.size(); ++i) {
		auto [x, t, k] = y[i];
		if(t != 0) continue;
		pos[k] = i;
	}

	for(int i = 0; i < (int)y.size(); ++i)
		for(int j = 0; j < (int)y.size(); ++j)
			toleft[i][j] = toright[i][j] = -1;
	
	priority_queue<tuple<i64, int, int, int>> pq;

	int k = lower_bound(all(y), make_tuple(0, -1, -1)) - y.begin();

	pq.emplace(0ll, 0, k, k);
	pq.emplace(0ll, 1, k, k);

	auto can_go_to_left = [&](int l, int r) {
		if(l == 0) return false;
		auto [x, t, id] = y[l - 1];
		if(t != 1) return true;
		if(l > r) swap(l, r);
		return pos[id] >= l && pos[id] <= r;
	};

	auto can_go_to_right = [&](int l, int r) {
		if(k == (int)y.size() - 1) return false;
		auto [x, t, id] = y[l + 1];
		if(t != 1) return true;
		if(l > r) swap(l, r);
		return pos[id] >= l && pos[id] <= r;
	};

	while(!pq.empty()) {
		auto [c, t, i, hi] = pq.top(); pq.pop();

		c *= -1;

		if(get<0>(y[i]) == x) {
			cout << c << '\n';
			return;
		}

		if(t == 0) {
			if(toleft[i][hi] != -1) continue;

			toleft[i][hi] = c;

			if(can_go_to_left(i, hi) && toleft[i - 1][hi] < 0)
				pq.emplace(-c - abs(get<0>(y[i])-get<0>(y[i-1])), 0, i - 1, hi);

			if(toright[hi][i] < 0)
				pq.emplace(-c - abs(get<0>(y[i]) - get<0>(y[hi])), 1, hi, i);
		
		} else {
			if(toright[i][hi] != -1) continue;

			toright[i][hi] = c;

			if(can_go_to_right(i, hi) && toright[i + 1][hi] < 0)
				pq.emplace(-c - abs(get<0>(y[i])-get<0>(y[i+1])), 1, i + 1, hi);

			if(toleft[hi][i] < 0)
				pq.emplace(-c - abs(get<0>(y[i]) - get<0>(y[hi])), 0, hi, i);
		}
	}

	cout << "-1\n";
}		

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
