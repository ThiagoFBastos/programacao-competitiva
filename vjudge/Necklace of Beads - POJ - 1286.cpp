#include <iostream>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
/*
using long long = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
*/

int count(string a, string b) {
	set<char> s;
	int n = a.size();
	for(int i = 0; i < n; ++i) {
		char c = b[i];
		for(int j = 0; j < n; ++j) {
			if(a[j] == c) a[j] = a[i];
			if(b[j] == c) b[j] = a[i];	
		}
	}
	for(int i = 0; i < n; ++i) s.insert(a[i]);
	return s.size();	
}

string shift(string s, int k) {
	int n = s.size();
	s += s;
	return s.substr(k, n);
}

long long exp(long long n, int k) {
	long long ans = 1;
	while(k--) ans *= n;
	return ans;
}

void solve() {
	while(true) {
		int n;

		cin >> n;

		if(n < 0) return;

		else if(!n) {
			cout << "0\n";
			continue;
		}

		long long cnt = 0;

		string alpha;

		for(int i = 0; i < n; ++i) alpha += i + 'A';

		string r_alpha(rall(alpha));

		for(int i = 0; i < n; ++i) {
			for(int inv = 0; inv < 2; ++inv) {
				string pat = inv ? r_alpha : alpha;
				cnt += exp(3, count(alpha, shift(pat, i)));
			}
		}

		cout << cnt / (2 * n) << '\n';
	}
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}