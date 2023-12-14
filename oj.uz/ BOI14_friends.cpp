#include <bits/stdc++.h>
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
 
bool subseq(string& a, string& b) {
	int n = size(a);
 
	vector<bool> pre(n + 1);
	bool suf = true;
 
	pre[0] = true;
	for(int i = 1; i <= n; ++i) pre[i] = pre[i - 1] && a[i - 1] == b[i - 1];
 
	if(pre.back()) return true;
 
	for(int i = n - 1; i >= 0; --i) {
		suf = suf && a[i] == b[i + 1];
		if(pre[i] && suf) return true;
	}
 
	return suf;
}
 
void solve() {
 
	string s;
	int n;
 
	cin >> n >> s;
	
	if(~n & 1) {
		cout << "NOT POSSIBLE\n";	
		return;
	}
 
	string a = s.substr(0, n / 2) + s.substr(0, n / 2);
	string b = s.substr(n / 2 + 1) + s.substr(n / 2 + 1);
 
	if(subseq(a, s)) {
		if(a == b || !subseq(b, s)) cout << s.substr(0, n / 2) << '\n';
		else cout << "NOT UNIQUE\n";
	} else if(subseq(b, s)) cout << s.substr(n / 2 + 1) << '\n';
	else cout << "NOT POSSIBLE\n";
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}
