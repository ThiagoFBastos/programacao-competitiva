#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;
const int maxn = 100000, maxm = 10000;
string mus[maxn], t[maxm];
int n, m;
unordered_map<string, int> notas {
	{"A", 1},
	{"A#", 2},
	{"Ab", 12},
	{"B", 3},
	{"B#", 4},
	{"Bb", 2},
	{"C", 4},
	{"C#", 5},
	{"Cb", 3},
	{"D", 6},
	{"D#", 7},
	{"Db", 5},
	{"E", 8},
	{"E#", 9},
	{"Eb", 7},
	{"F", 9},
	{"F#", 10},
	{"Fb", 8},
	{"G", 11},
	{"G#", 12},
	{"Gb", 10}
};
vi F(vi& a) {
	vi p(a.size());
	p[0] = 0;
	for(int i = 1; i < (int)a.size(); ++i) {
		int j = p[i - 1];
		while(j && a[i] != a[j]) j = p[j - 1];
		p[i] = j;
		if(a[i] == a[j]) ++p[i];
	}
	return p;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while(true) {
		cin >> n >> m;
		if(!(n || m)) break;
		for(int i = 0; i < n; ++i) cin >> mus[i];
		for(int i = 0; i < m; ++i) cin >> t[i];
		bool plagio = false;
		if(m == 1) {
			for(int i = 0; i < n; ++i) {
				if(mus[i] == t[0]) {
					plagio = true;
					break;
				}
			}
		}
		else {
			vi a;
			a.reserve(m + n - 1);
			for(int i = 0; i < m - 1; ++i) {
				int x = notas[t[i + 1]] - notas[t[i]];
				a.push_back(x < 0 ? x + 12 : x);
			}
			a.push_back(INT_MAX);
			for(int i = 0; i < n - 1; ++i) {
				int x = notas[mus[i + 1]] - notas[mus[i]];
				a.push_back(x < 0 ? x + 12 : x);
			}
			vi p = F(a);
			for(int i = m; i < (int)p.size(); ++i) {
				if(p[i] == m - 1) {
					plagio = true;
					break;
				}
			}
		}
		cout << (plagio ? "S\n" : "N\n");
	}
	return 0;
}