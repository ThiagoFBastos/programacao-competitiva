#include <bits/stdc++.h>
 
using namespace std;
 
inline auto f(int x) {
	return x * (x + 1ll) / 2;
}
 
bool triangle(long long x) {
	int n = sqrt(2 * x + 0.0L);
	return f(n) == x;
}
 
bool triangle2(long long x) {
	for(int i = 0; f(i) <= x; ++i) {
		if(triangle(x - f(i)))
			return true;
	}
	return false;
}
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int t;
	
	cin >> t;
 
	while(t--) {
		long long n;
 
		cin >> n;
 
		if(triangle(n)) cout << "1\n";
		else if(triangle2(n)) cout << "2\n";
		else cout << "3\n";
	}
 
	return 0;
}
