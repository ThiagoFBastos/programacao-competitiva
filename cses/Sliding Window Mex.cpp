#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n, k;
 
	cin >> n >> k;
 
	vector<int> a(n), frq(n + 1, 0);
	set<int> st;
 
	for(int& v : a) cin >> v;
 
	for(int i = 0; i <= n; ++i) st.insert(i);
 
	auto insert = [&](int x) {
		if(x > n) return;
 
		st.erase(x);
		++frq[x];
	};
 
	auto remove = [&](int x) {
		if(x > n) return;
 
		if(--frq[x] == 0)
			st.insert(x);
	};
 
	for(int i = 0; i < n; ++i) {
		if(i >= k) remove(a[i - k]);
 
		insert(a[i]);
		
		if(i >= k - 1) cout << *st.begin() << ' ';
	}
 
	cout << '\n';
 
	return 0;
}
