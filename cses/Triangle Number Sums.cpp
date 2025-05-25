#include <bits/stdc++.h>
 
using namespace std;
 
inline auto f(int x) {
	return x * (x + 1ll) / 2;
}
 
bool triangle(long long x) {
	int n = sqrt(2 * x + 0.0L);
	return f(n) == x;
}
 
vector<long long> T;
 
void preComputeTriangles() {
	constexpr long long MAXN = 1e12L;
 
	for(int i = 0; f(i) <= MAXN; ++i)
		T.push_back(f(i));
}
 
bool triangle2(long long x) {
	int lo = 0, hi = T.size() - 1;
 
	if(x % 2 == 0 && binary_search(T.begin(), T.end(), x / 2))
		return true;
		
	while(lo < hi) {
		auto sum = T[lo] + T[hi];
		
		if(sum > x) --hi;
		else if(sum < x) ++lo;
		else return true;
	}
 
	return false;
}
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	preComputeTriangles();
 
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