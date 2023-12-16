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
 
vector<int> z_function(string& s) {
    int n = (int) s.length();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if(i <= r) z[i] = min (r - i + 1, z[i - l]);
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}
 
void solve() {
	
	string s;
 
	cin >> s;
 
	for(int v : z_function(s)) cout << v << ' ';
	cout << '\n';	
	for(int v : kmp(s)) cout << v << ' ';
	cout << '\n';
}	
 
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
