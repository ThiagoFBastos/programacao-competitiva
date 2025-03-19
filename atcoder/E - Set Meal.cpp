#include "bits/stdc++.h"
 
using namespace std;
	
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	
	int n, m, l;
	
	cin >> n >> m >> l;
	
	vector<int> dishA(n), dishB(m);
	multiset<int> S;
	vector<vector<int>> pairs(n);
	
	for(int i = 0; i < n; ++i) {
		cin >> dishA[i];
		pairs[i] = {};
	}
	
	for(int& val : dishB) {
		cin >> val;
		S.insert(val);
	}

	for(int i = 0; i < l; ++i) {
		int a, b;
		cin >> a >> b;
		pairs[a - 1].push_back(dishB[b - 1]);
	}
	
	int ans = 0;
	
	for(int i = 0; i < n; ++i) {
		for(int b : pairs[i])
			S.erase(S.find(b));
		
		if(!S.empty())
			ans = max(ans, dishA[i] + *S.rbegin());
		
		for(int b : pairs[i])
			S.insert(b);
	}
	
	cout << ans << '\n';
	
	return 0;
}