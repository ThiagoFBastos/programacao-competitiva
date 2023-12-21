#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
 
	int n, t;
 
	ios_base :: sync_with_stdio(false);
	cin.tie(nullptr);
 
	cin >> n >> t;
 
	vector<int> h(n);
	long long low = 1, high = LLONG_MAX;
 
	for(int k = 0; k < n; ++k) {
 
		cin >> h[k];
		high = min(high, 0LL + h[k]);
	}
 
	high *= t;
	
	while(low < high) {
 
		long long mid, prod = 0;
 
		mid = (low + high) >> 1;
	
		for(int H : h)
			prod += mid / H;
 
		if(prod >= t)
			high = mid;
 
		else
			low = mid + 1;
	}
 
	cout << high << '\n';
 
	return 0;
}
