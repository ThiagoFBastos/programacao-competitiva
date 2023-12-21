#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
 
int main() {
 
	int n, w;
 
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
 
	cin >> n >> w;
 
	vi weight(n);
 
	for(int k = 0; k < n; ++k)
		cin >> weight[k];
 
	sort(weight.begin(), weight.end());
 
	int count = 0, lo = 0, hi = n - 1;
 
	while(lo <= hi) {
 
		if(weight[lo] + weight[hi] > w)
			--hi;
 
		else
			++lo, --hi;
 
		++count;
	}
 
	cout << count << '\n';
 
	return 0;
}
