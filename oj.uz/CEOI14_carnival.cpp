#include "bits/stdc++.h"
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;
 
void solve() {
	
	int n, conn;
 
	cin >> n;
 
	set<int> S;
	vector<int> id(n, -1);
 
	cout << n;
 
	for(int i = 1; i <= n; ++i) {
		cout << ' ' << i;
		S.insert(i);
	}
 
	cout << endl;
	cin >> conn;
 
	for(int i = 1; i <= n; ++i) {
		if(S.size() == 1) break;
		int ans;
		cout << S.size() - 1;
		for(int f : S) {
			if(f == i) continue;
			cout << ' ' << f;
		}
		cout << endl;
		cin >> ans;
		if(ans == conn) S.erase(i);
	}
 
	vector<int> c(S.begin(), S.end());
 
	function<int(int, int, int)> bb = [&](int lo, int hi, int g) {
		if(lo == hi) return lo;
		int mid = (lo + hi) / 2, ans;
		cout << mid - lo + 2;
		for(int k = lo; k <= mid; ++k) cout << ' ' << c[k];
		cout << ' ' << g << endl;
		cin >> ans;
		return ans == mid - lo + 1 ? bb(lo, mid, g) : bb(mid + 1, hi, g);
	};
 
	for(int i = 0; i < (int)c.size(); ++i) id[c[i] - 1] = i;
 
	for(int i = 1; i <= n; ++i) {
		if(S.count(i)) continue;
		id[i - 1] = bb(0, (int)c.size() - 1, i);	
	}
 
	cout << "0";
	for(int v : id) cout << ' ' << v + 1;
	cout << endl;
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
