#include "bits/stdc++.h"
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
 
vector<int> kmp(string& s) {
	int n = s.size();
	vector<int> p(n);
	p[0] = 0;
	for(int i = 1; i < n; ++i) {
		int j = p[i - 1];
		while(j && s[i] != s[j]) j = p[j - 1];
		p[i] = j;
		if(s[i] == s[j]) ++p[i];
	}
	return p;
}
 
vector<int> max_prefix(string& s, string& t) {
	string p = s + "#" + t;
	auto k = kmp(p);
	k.erase(k.begin(), k.begin() + s.size() + 1);
	return k;	
}
 
vector<int> max_suffix(string& s, string& t) {
	string p = string(s.rbegin(), s.rend()) + "$" + string(t.rbegin(), t.rend());
	auto k = kmp(p);
	k.erase(k.begin(), k.begin() + s.size() + 1);
	reverse(k.begin(), k.end());
	return k;
}
 
tuple<int, int, int> necklace(string& s, string& t) {
	int n = s.size(), m = t.size();
	auto ans = make_tuple(-1, -1, -1);
 
	for(int i = 0; i < m; ++i) {
		string p;
 
		for(int j = 0; j < m; ++j) {
			int k = i + j;
			if(k >= m) k -= m;
			p += t[k];
		}
 
		auto k = max_prefix(p, s);
		auto z = max_suffix(p, s);
 
		z.push_back(0);
 
		for(int j = 0; j < n; ++j)
			ans = max(ans, make_tuple(min(k[j], m - i) + min(z[j + 1], i), j - k[j] + 1, i - z[j + 1]));
	} 
 
	return ans;
}	
 
void solve() {
	string s, t;
 
	cin >> s >> t;
 
	int m = t.size();
 
	auto ans1 = necklace(s, t);
 
	reverse(t.begin(), t.end());
	
	auto ans2 = necklace(s, t);
 
	get<2>(ans2) = m - get<2>(ans2) - get<0>(ans2);
 
	ans1 = max(ans1, ans2);
 
	cout << get<0>(ans1) << '\n';
	cout << get<1>(ans1) << ' ' << get<2>(ans1) << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
