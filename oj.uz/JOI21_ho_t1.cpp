#include "bits/stdc++.h"
 
using namespace std;
 
#define INF   1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;
 
i64 increasing(vector<int>& a) {
	i64 ans = 0;
	for(int v : a) {
		if(v > 0) continue;
		ans += -v + 1;
	}
	return ans;
}
 
i64 decreasing(vector<int>& a) {
	i64 ans = 0;
	for(int v : a) {
		if(v < 0) continue;
		ans += v + 1;
	}
	return ans;
}
 
i64 climb(vector<int>& a) {
	i64 x = 0, y = 0, ans = INFLL;
	for(int v : a) if(v >= 0) x += v + 1;
	for(int v : a) {
		if(v >= 0) x -= v + 1;
		if(v <= 0) y += -v + 1;
		ans = min(ans, max(x, y));
	}
	return ans;
}
 
int main(int argc, char* argv[]) {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
 
	int n;
 
	cin >> n;
 
	vector<int> a(n);
 
	for(int& v : a) cin >> v;
 
	for(int i = n - 1; i >= 0; --i) a[i] -= a[i - 1];
 
	a.erase(a.begin());
 
	cout << min({increasing(a), decreasing(a), climb(a)}) << '\n';
 
	return 0;
}
