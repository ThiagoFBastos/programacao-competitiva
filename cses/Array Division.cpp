#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
 
 
bool can_divide(vi& x, ll maxsum, int K) {
 
	int k = 0; 
	ll sum = 0;
 
	for(int v : x) {
 
		if(sum + v <= maxsum)
			sum += v;
 
		else {
 
			++k;
			sum = v;
		}
	}
 
	return k + 1 <= K;
}
 
int main() {
 
	ios_base :: sync_with_stdio(false);
	cin.tie(nullptr);
		
	int n, k;
 
	cin >> n >> k;
 
	vi x(n);
	ll low = 1, high = 0;
 
	for(int k = 0; k < n; ++k) {
 
		cin >> x[k];
		high += x[k];
		low = max(0LL + x[k], low);
	}
 
	while(low < high) {
 
		ll mid = low + high >> 1;
 
		if(can_divide(x, mid, k))
			high = mid;
		else
			low = mid + 1;
	}
 
	if(low > high)
		swap(low, high);
 
	ll answer;
 
	if(can_divide(x, low, k))
		answer = low;
	else
		answer = high;
 
	cout << answer << '\n';
	
	return 0;
}
