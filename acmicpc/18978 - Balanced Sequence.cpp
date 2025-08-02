#include "bits/stdc++.h"

using namespace std;
 
#define INF 1000000000
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

string normalize(string& s) {
	string t;
	for(char ch : s) {
		if(ch == ')') {
			if(!t.empty() && t.back() == '(') t.pop_back();
			else t += ')';
		} else
			t += '(';
	}
	return t;
}

int balance(string& s) {
	int g = 0;
	for(char c : s) if(c == '(') ++g; else --g;
	return g;
}

int negativity(string& s) {
	int i = 0;
	while(s[i] && s[i] == ')') ++i;
	return i;
}

void solve() {

	int ans = 0, n;
	
	cin >> n;

	vector<string> par(n);
	string t;
	int g = 0;

	for(auto& s : par) {
		cin >> s;
		string t = normalize(s);
		ans += s.size() - t.size();
		s = t;
	}

	for(auto& s : par) if(!s.empty() && s.front() == '(') t += s;

	vector<ii> good, bad;

	for(int i = 0; i < n; ++i) {
		string& s = par[i];
		if(s.front() == ')' && s.back() == '(') {
			int b = balance(s);
			int n = negativity(s);
			int p = (int)s.size() - n;
			if(b >= 0) good.pb({n, i});
			else bad.pb({p, i});
		}
	}

	sort(all(good));	
	sort(rall(bad));
 
	for(auto& v : good) t += par[v.sc];	
	for(auto& v : bad) t += par[v.sc];

	for(auto& s : par) if(!s.empty() && s.front() == ')' && s.back() == ')') t += s;

	for(char c : t) {
		if(c == '(') ++g;
		else if(g) {
			ans += 2;
			--g;
		}
	}

	cout << ans << '\n';
}	
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}