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
using i128 = __int128;

struct regional {
	string s;
	int pt;
	int pu;
	int rt;
	int ru;
	int f;
};

double score(regional& r) {
	return r.ru * 0.56 + r.pu * 0.14 + 
	r.rt * 0.24 + r.pt * 0.06 + r.f * 0.3;
}

bool cmp(regional a, regional b) {
	return score(a) > score(b);
}

void solve() {
	int n;

	cin >> n;

	vector<regional> r(6);

	for(int i = 0; i < 6; ++i) {
		cin >> r[i].s;
		cin >> r[i].pt;
		cin >> r[i].pu;
		cin >> r[i].rt;
		cin >> r[i].ru;
		cin >> r[i].f;
	}

	sort(all(r), cmp);

	for(int i = 0; i < 6; ++i) {
		int slots = n / 6 + (n % 6 > i);
		if(r[i].s == "Taiwan") cout << slots << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

