#include "bits/stdc++.h"
#define endl '\n'

using namespace std;

using ii = pair<int, int>;

int det(ii a, ii b, ii c) {
	return (b.first * c.second - b.second * c.first) - 
		    a.first * (c.second - b.second) + 
		    a.second * (c.first - b.first);
}

bool cw(ii a, ii b, ii c) {
	return det(a, b, c) < 0;
}

bool ccw(ii a, ii b, ii c) {
	return det(a, b, c) > 0;
}

auto hull(vector<ii>& p, function<bool(ii, ii, ii)> cmp) {
	stack<ii> st;
	vector<ii> a;
	
	st.push(p[0]);
	
	for(int i = 1; i < int(size(p)); ++i) {
		while((int)size(st) >= 2) {
			ii r = st.top(); st.pop();
			if(cmp(p[i], r, st.top())) {
				st.push(r);
				break;
			}
		}
		st.push(p[i]);
	}
	
	while(!st.empty()) {
		a.emplace_back(st.top());
		st.pop();
	}
	
	return a;
}

auto convex_hull(vector<ii>& p) {
	sort(p.begin(), p.end());
	auto a = hull(p, cw);
	auto b = hull(p, ccw);
	reverse(a.begin(), a.end());
	for(auto& x : b) a.emplace_back(x);
	return a;
}

double area(vector<ii>& p) {
	double ans = 0;
	int n = size(p);
	for(int i = 0; i < n; ++i) {
		int j = i + 1;
		if(j >= n) j -= n;
		ans += p[i].first * p[j].second - p[i].second * p[j].first;
	}
	return abs(ans) / 2;
}

void solve() {
	int n;
	
	cin >> n;
	
	if(cin.eof()) exit(0);
	
	vector<ii> p(n);
	
	for(int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		p[i] = {x, y};
	}
	
	auto u = convex_hull(p);
	
	cout << area(u) << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.precision(2);
	cout.setf(ios_base :: fixed);
	int t = 1;
	//cin >> t;
	while(1) solve();
	return 0;
}