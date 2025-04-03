#include "bits/stdc++.h"
#define endl '\n'

using namespace std;

bool is_prime(int x) {
	if(x < 2) return false;
	else if(x == 2) return true;
	else if(x % 2 == 0) return false;
	for(int k = 3; k * k <= x; k += 2) if(x % k == 0) return false;
	return true;
}

void solve() {
	int n;	
	cin >> n;
	if(is_prime(n)) cout << "1" << endl;
	else if(n % 2 == 0 || is_prime(n - 2)) cout << "2" << endl;
	else cout << "3" << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}