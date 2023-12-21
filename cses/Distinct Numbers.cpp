#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
 
int main() {
 
	int n;
 
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
 
	cin >> n;
	
	vi x(n);
 
	for(int k = 0; k < n; ++k)
		cin >> x[k];
 
	sort(x.begin(), x.end());
 
	int count = 1;
 
	for(int k = 1; k < n; ++k) {
 
		if(x[k] > x[k - 1])
			++count;
	}
 
	cout << count << '\n';
	
	return 0;
}
