#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n;
	map<int, int> last_pos;
	long long subarrays = 0;
 
	cin >> n;
 
	for(int i = 1; i <= n; ++i) {
		int v;
 
		cin >> v;
 
		subarrays += (i - last_pos[v] + 0ll) * (n - i + 1);
		last_pos[v] = i;
	}
 
	cout << subarrays << '\n';
 
	return 0;
}
