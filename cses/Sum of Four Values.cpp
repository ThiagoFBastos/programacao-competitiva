#include <bits/stdc++.h>
 
using namespace std;
 
using ii = pair<int, int>;
using vii = vector<ii>;
 
int main() {
 
	ios_base :: sync_with_stdio(false);
	cin.tie(nullptr);
		
	int n, x;
 
	cin >> n >> x;
 
	vii a(n);
 
	for(int k = 0; k < n; ++k) {
 
		cin >> a[k].first;
		a[k].second = 1 + k;
	}
 
	sort(a.begin(), a.end());
 
	map<int, ii> S;
	int l1 = x - 2, l2 = x >> 1;
 
	for(int k = n - 2; k >= 0; --k) {
		
		for(int j = k + 2; j < n; ++j) {
 
			int y = a[k + 1].first + a[j].first;
 
			if(y > l1)
				break;
 
			S[y] = make_pair(a[k + 1].second, a[j].second);
		}
 
		for(int j = 0; j < k; ++j) {
 
			int y = a[k].first + a[j].first;
 
			if(y > l2)
				break;
 
			auto it = S.find(x - y);
 
			if(it != S.end()) {
							
				ii e = it->second;
	
				cout << a[j].second << ' ' << a[k].second << ' ' << e.first << ' ' << e.second << '\n';
				return 0;
			}
		}	
	}
 
	cout << "IMPOSSIBLE\n";
		
	return 0;
}
