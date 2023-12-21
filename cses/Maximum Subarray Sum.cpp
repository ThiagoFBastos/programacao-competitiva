#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
 
#define fi first
#define sc second
 
int main() {
 
	int n;
 
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
 
	cin >> n;
 
	ll max_sum = INT_MIN, sum = 0;
 
	for(int k = 0; k < n; ++k) {
 
		int a;
 
		cin >> a;
 
		sum += a;
		max_sum = max(max_sum, sum);
 
		if(sum < 0)
			 sum = 0;
	}
 
	cout << max_sum << '\n';
 
	return 0;
}
