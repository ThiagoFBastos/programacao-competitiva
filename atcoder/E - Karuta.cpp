#include "bits/stdc++.h"

using namespace std;

#define INF    1000000000
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

const int N = 5e5 + 10;

int t[N][26], frq[N], nd = 1;

void add(string& s) {
	int i = 0;
	for(char c : s) {
		int& j = t[i][c - 'a'];
		if(j < 0) {
			memset(t[nd], -1, sizeof t[nd]);
			j = nd++;
		}
		++frq[i];
		i = j;
	}
	++frq[i];
}

void solve() {
	int n;

	cin >> n;

	vector<string> s(n);
	
	memset(t[0], -1, sizeof t[0]);

	for(auto& w : s) {
		cin >> w;
		add(w);
	}

	for(auto& w : s) {
		int i = 0, lcp = 0, eq = 1;

		for(int k = 0; k < (int)w.size(); ++k) {
			int j = t[i][w[k] - 'a'];
			eq = eq && frq[j] >= 2;
			lcp += eq;
			i = j;
		}
		
		cout << lcp << '\n';
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
