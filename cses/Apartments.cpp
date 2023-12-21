#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
 
int main() {
 
	int n, m, k;
 
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
 
	cin >> n >> m >> k;
	
	vi as(n), a(m); 
	
	for(int k = 0; k < n; ++k)
		cin >> as[k];
 
	for(int k = 0; k < m; ++k)
		cin >> a[k];
 
	sort(as.begin(), as.end());
	sort(a.begin(), a.end());
 
	int j = 0, count = 0;
 
	for(int i = 0; i < n && j < m; ++i) {
 
		int h = lower_bound(a.begin() + j, a.end(), as[i] - k) - a.begin();
 
		if(h < m && a[h] >= as[i] - k && a[h] <= as[i] + k) {
 
			++count;
			j = h + 1;
		}
	}
 
	cout << count << '\n';
 
	return 0;
}
