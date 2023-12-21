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
 
	// 2 3 -4 5 -8 -9
 
	cin >> n;
 
	n <<= 1;
 
	vi h(n);
 
	for(int k = 0; k < n; ++k) {
 
		cin >> h[k];
 
		if(k & 1)
			h[k] = -h[k];
	}
	
	sort(h.begin(), h.end(), [](int x, int y) {return abs(x) < abs(y);});
 
	int person {}, maxperson = 0;
 
	for(int H : h) {
 
		if(H > 0)
			maxperson = max(maxperson, ++person);
 
		else
			--person;
	}
 
	cout << maxperson << '\n';
 
	return 0;
}
