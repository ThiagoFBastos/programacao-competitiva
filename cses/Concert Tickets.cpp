#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
 
int main() {
 
	int n, m;
 
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
 
	cin >> n >> m;
 
	map<int, int> prices;
 
	for(int k = 0; k < n; ++k) {
 
		int p;
 
		cin >> p;
 
		++prices[p];
	}
 
	for(int k = 0; k < m; ++k) {
 
		int mp;
 
		cin >> mp;
 
		if(prices.empty())
			cout << -1 << '\n';
 
		else {
 
			auto it = prices.upper_bound(mp);
 
			if(it == prices.begin())
				cout << -1 << '\n';
 
			else {
 
				it = prev(it);
 
				cout << it->first << '\n';
 
				if(--it->second == 0)
					prices.erase(it);
			}
		}
	}	
 
	return 0;
}
