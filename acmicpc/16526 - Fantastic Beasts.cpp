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

const int N = 10, M = 1e2 + 10;

int nxtzoo[N][M], beast, zoo, t_to_cycle[N], zoo_pos[N][M];
vector<int> cycle[N];

pair<int, int> try_reach() {
	int at[N];
	for(int i = 0; i < beast; ++i) at[i] = nxtzoo[i][0];
	for(int i = 0; i <= zoo; ++i) {
		if(count(at, at + beast, at[0]) == beast) return {i, at[0]};
		for(int j = 0; j < beast; ++j) at[j] = nxtzoo[j][at[j]];
	}
	return {-1, -1};
}

void go_to_cycle(int k) {
	vector<int> t(zoo+1, -1), st;
	int T = 0;
	for(int z = nxtzoo[k][0]; ; z = nxtzoo[k][z]) {
		if(t[z] != -1) {
			t_to_cycle[k] = t[z];
			while(true) {
				cycle[k].pb(st.back());
				if(st.back() == z) break;
				st.pop_back();
			}
			reverse(all(cycle[k]));
			break;
		}
		t[z] = T++;
		st.pb(z);
	}
}

i128 euclides_ext(i128 a, i128 b, i128& x, i128& y) {
	if(!b) {
		x = 1;
		y = 0;
		return a;
	}
	i128 _x, _y;
	i128 g = euclides_ext(b, a % b, _x, _y);
	y = _x - (a / b) * _y;
	x = _y;	
	return g;
}

i128 _gcd(i128 a, i128 b) {
	if(b == 0) return a;
	return _gcd(b, a % b);
}

i128 _lcm(i128 a, i128 b) {
	return b / _gcd(a, b) * a;
}

bool findsolution(pair<i128, i128> a, pair<i128, i128> b, i128& ans) {
	auto [r1, m1] = a;
	auto [r2, m2] = b;
	i128 p, q, g = _gcd(m1, m2), l = _lcm(m1, m2);
	if((r1 - r2) % g) return false;
	m1 /= g, m2 /= g;
	(void)euclides_ext(m1, m2, p, q);
	ans = (l + (r1 * m2 % l * q + r2 * m1 % l * p) % l) % l;
	return true;
}

bool crt(vector<int>& m, vector<int>& r, i128& ans) {
	auto x0 = make_pair<i128, i128>(r[0], m[0]);
	for(int i = 1; i < (int)m.size(); ++i) {
		i128 t;
		if(!findsolution(x0, make_pair<i128, i128>(r[i], m[i]), t)) return false;
		x0 = make_pair(t, _lcm(x0.sc, m[i]));
	}
	ans = x0.fi;
	return true;
}

void solve() {
	cin >> beast >> zoo;
	
	for(int i = 0; i < beast; ++i)
	for(int j = 0; j <= zoo; ++j)
		cin >> nxtzoo[i][j];
		
	auto [tp, zp] = try_reach();
	
	if(tp != -1) {
		cout << zp << ' ' << tp << '\n';
		return;
	}
	
	vector<int> m(beast), r(beast);
	i128 ans = LLONG_MAX;
	int z = -1, max_tc = 0;
		
	for(int i = 0; i < beast; ++i) {
		go_to_cycle(i);
		max_tc = max(max_tc, t_to_cycle[i]);
	}

	for(int i = 0; i < beast; ++i) {
		int m = cycle[i].size();
		int f = (max_tc - t_to_cycle[i]) % m;
		vector<int> new_cycle;
		memset(zoo_pos[i], -1, sizeof zoo_pos[i]);
		for(int j = 0; j < m; ++j) {
			int u = cycle[i][(j+f)%m];
			new_cycle.pb(u);
			zoo_pos[i][u] = j;
		}
		swap(cycle[i], new_cycle);
	}
	
	for(int i = 0; i < beast; ++i) m[i] = cycle[i].size();
	
	for(int j = 1; j <= zoo; ++j) {
		bool ok = true;
		for(int i = 0; i < beast; ++i) {
			ok = ok && zoo_pos[i][j] != -1;
			r[i] = zoo_pos[i][j];
		}
		if(!ok) continue;
		i128 t;
		if(crt(m, r, t) && ans > t) ans = t, z = j; 
	}
	
	if(z < 0) {
		cout << "*\n";
		return;
	}
	
	cout << z << ' ' << i64(ans + max_tc) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}