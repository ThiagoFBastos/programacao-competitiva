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

ii operator-(ii a, ii b) {
	a.fi -= b.fi;
	a.sc -= b.sc;
	return a;
}

ii operator*(ii a, int k) {
	a.fi *= k;
	a.sc *= k;
	return a;
}

i64 cross(ii a, ii b) {
	return (i64)a.fi * b.sc - (i64)a.sc * b.fi;
}

const int N = 100;

bitset<N> line[N][N];

void solve() {
	int n;

	cin >> n;

	vector<ii> pt(n);
	i64 ans = 0;

	for(auto& [x, y] : pt) cin >> x >> y;

	for(int i = 0; i < n; ++i){
		for(int j = i + 1; j < n; ++j) {
			for(int k = 0; k < n; ++k) {
				if(i == k || j == k) continue;
				ii u = pt[i] - pt[j];
				ii v = pt[k] - pt[j];
				i64 x = cross(u, v);
				if(x) line[i][j][k] = 1;
			}
		}
	}

	for(int i = 0; i < n; ++i) {
		for(int j = i + 1; j < n; ++j) {
			for(int k = j + 1; k < n; ++k) {
				if(cross(pt[i]-pt[k],pt[j]-pt[k]))
					ans += (line[i][j] & line[i][k] & line[j][k]).count(); 
			}
		}
	}

	cout << ans / 4 << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

