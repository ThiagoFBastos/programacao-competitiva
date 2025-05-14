#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n, k;
	
	cin >> n >> k;
 
	vector<int> a(n);
	map<int, int> mp;
	set<pair<int, int>> st;
 
	for(int& v : a) cin >> v;
 
	auto add = [&](int v) {
		if(auto it = mp.find(v); it == mp.end()) {
			st.emplace(0, -v);
			mp[v] = 0;
		}
 
		auto it = mp.find(v);
 
		st.erase(make_pair(it->second, -v));
		++it->second;
		st.emplace(it->second, -v);
	};
 
	auto remove = [&](int v) {
		auto it = mp.find(v);
		
		st.erase(make_pair(it->second, -v));
		
		if(--it->second)
			st.emplace(it->second, -v);
		else
			mp.erase(it);
	};
 
	for(int i = 0; i < n; ++i) {
		if(i >= k) remove(a[i - k]);
 
		add(a[i]);
 
		if(i >= k - 1) cout << -st.rbegin()->second << ' ';
	}
 
	cout << '\n';
 
	return 0;
}