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

void solve() {

	int n, m;
	
	cin >> n >> m;
	
	vector<int> p(m);
	vector<bool> x(m, false), y(m, false);
	vector<ii> s(m);
	
	int cnt = 0, j = 0;
	
	for(int i = 0; i < m; ++i) {
		cin >> s[i].first;
		s[i].second = 0;
	}
	
	for(int& x : p) cin >> x;
	
	sort(s.begin(), s.end());
	sort(p.begin(), p.end());
	
	for(int i = 0; i < m; ++i) {
		while(j < m && s[j].first < p[i]) ++j;
		if(j < m && s[j].first == p[i]) x[i] = y[j++] = true;
	}
	
	j = 0;
	
	for(int i = 0; i < m; ++i) {
		if(x[i]) continue;
		while(j < m && y[j]) ++j;
		s[j].second = -1;
		s[j++].first = p[i];
	}
	
	for(int i = 1; i < n; ++i) {
		fill(x.begin(), x.end(), false);
		fill(y.begin(), y.end(), false);
		
		for(int& x : p) cin >> x;
		
		sort(s.begin(), s.end());
		sort(p.begin(), p.end());
		
		j = 0;
		
		for(int k = 0; k < m; ++k) {
			while(j < m && s[j].first < p[k]) ++j;
			if(j < m && s[j].first == p[k]) x[k] = y[j++] = true;
		}
		
		j = 0;
		
		for(int k = 0; k < m; ++k) {
			if(x[k]) continue;
			while(j < m && y[j]) ++j;
			cnt += -s[j].second;
			s[j].second = -1;
			s[j++].first = p[k];
		}
	}
	
	cout << cnt << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	for(int i = 1; i <= t; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}
 	return 0;
}
