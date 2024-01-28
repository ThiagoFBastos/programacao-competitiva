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

void solve() {
	int n, m;

	cin >> n >> m;

	map<int, vector<int>> req, enroll;
	set<int> ID;
	int X = 0, Y = 0, Z = 0;

	for(int i = 0; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		ID.insert(a);
		req[a].resize(b);
		for(int& v : req[a]) cin >> v;
	}

	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		ID.insert(a);
		enroll[a].resize(b);
		for(int& v : enroll[a]) cin >> v;
	}

	for(int id : ID) {
		vector<int> corr;
		map<int, int> frq;
		int wrong = 0;

		for(int v : req[id]) ++frq[v];
		for(int v : enroll[id]) --frq[v];
		
		for(auto [a, b] : frq) {
			wrong = wrong || b;
			if(b < 0) Y += abs(b);
			else Z += b;
			for(int i = 0; i < abs(b); ++i) corr.pb(a * b / abs(b));
		}

		if(!wrong) continue;

		sort(all(corr), [](int a, int b) {
			return abs(a) < abs(b);
		});

		cout << id << ' ';
		for(int v : corr) cout << (v > 0 ? "+" : "") << v << ' ';
		cout << '\n';

		++X;
	}

	if(X + Y + Z == 0) {
		cout << "GREAT WORK! NO MISTAKES FOUND!\n";
		return;
	}

	cout << "MISTAKES IN " << X << " STUDENTS: " << Y << " NOT REQUESTED, " << Z << " MISSED\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

