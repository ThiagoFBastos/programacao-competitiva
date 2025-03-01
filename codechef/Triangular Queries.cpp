#include "bits/stdc++.h"
#define endl '\n'

using namespace std;

using ii = pair<int, int>;

struct BIT {
	vector<int> bit;
	
	BIT(int n) {
		bit.assign(n + 1, 0);
	}
	
	void upd(int k, int x) {
		for(++k; k < int(bit.size()); k += k & -k) bit[k] += x;
	}
	
	int query(int k) {
		int ans {};
		for(++k; k > 0; k -= k & -k) ans += bit[k];
		return ans;
	}
};

struct Event {
	int x, is_cls, L, R, pos;
};

bool operator<(Event e1, Event e2) {
	return e1.x < e2.x || e1.x == e2.x && e1.is_cls < e2.is_cls 
	|| e1.x == e2.x && e1.is_cls == e2.is_cls && (e1.L < e1.R) > (e2.L < e2.R);
}

void solve() {
	int n, q;
	
	cin >> n >> q;
	
	vector<Event> e;
	vector<int> cnt(q, 0);
	
	for(int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		e.push_back({x, 0, y, y, -1});
	}
	
	vector<int> Y(q), Z(q); 
	
	for(int i = 0; i < q; ++i) {
		int x, y, d;
		cin >> x >> y >> d;
		Y[i] = y;
		Z[i] = y + d + x;
		e.push_back({x, 0, y, y + d, i});
		e.push_back({x + d, 1, y, y, i});
	}
	
	sort(Y.begin(), Y.end());
	sort(Z.begin(), Z.end());
	Y.resize(unique(Y.begin(), Y.end()) - Y.begin());
	Z.resize(unique(Z.begin(), Z.end()) - Z.begin());
	sort(e.begin(), e.end());
	
	BIT y(Y.size()), z(Z.size());
	
	for(int i = 0; i < int(e.size()); ++i) {
		int x = e[i].x, is_cls = e[i].is_cls, L = e[i].L, R = e[i].R, pos = e[i].pos;
		
		int k = lower_bound(Z.begin(), Z.end(), R + x) - Z.begin();
		int j = lower_bound(Y.begin(), Y.end(), L) - Y.begin();
			
		if(is_cls) cnt[pos] += z.query(k) - y.query(j);
		else if(L < R) cnt[pos] -= z.query(k) - y.query(j);
		else {
			j += j < int(Y.size()) && Y[j] ==  L;
			z.upd(k, 1);
			y.upd(j, 1);
		}
	}
	
	for(int x : cnt) cout << x << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}



