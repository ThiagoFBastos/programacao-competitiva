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

const int N = 5e4 * 50;
 
int out[N], frq[N], nd = 1;
map<char, int> t[N];

void add(string& s) {
	int i = 0;
	for(char c : s) {
		int& j = t[i][c];
		if(!j) j = nd++;
		i = j;
		++frq[i];
	}
}

void rem(string& s) {
	int i = 0;
	for(char c : s) {
		int& j = t[i][c];
		i = j;
		--frq[i], ++out[i];
	}
}


void solve() {
	int n;

	cin >> n;

	vector<int> ans(n, 0);
	vector<string> s(n);

	for(int i = 0; i < n; ++i) {
		cin >> s[i];
		add(s[i]);
	}

	ans.back() = t[0].size();

	auto push = [&](auto& self, int k, int& v)->void {
		if(!frq[k]) return;
		if(!out[k]) {
			++v;
			return;
		}
		for(auto [c, u] : t[k])
			self(self, u, v);
	};

	for(int i = n - 1; i; --i) {
		int j = 0;
		
		ans[i - 1] = ans[i];
		
		rem(s[i]);

		for(char c : s[i]) {
			j = t[j][c];
			if(out[j] == 1) {
				--ans[i - 1];
				push(push, j, ans[i - 1]);
				break;
			}
		}
	}	

	for(int v : ans) cout << v << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  //cin >> t;
	while(t--) solve();
	return 0;
}
 
