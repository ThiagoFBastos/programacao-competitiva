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

template<int MAXN>
struct Aho {
	map<char, int> next[MAXN];
	int fail[MAXN], depth[MAXN], leaf[MAXN], nd, nw;
	vector<int> pats[MAXN];

	Aho() {
		reset();
	}

	int newnode(int p = -1) {
		depth[nd] = p < 0 ? 0 : 1 + depth[p];
		leaf[nd] = -1;
		pats[nd].clear();
		next[nd].clear();
		fail[nd] = 0;
		return nd++;
	}

	void reset() {
		nd = nw = 0;
		newnode();
	}

	void push(string& s, int id) {
		int i = 0;
		++nw;
		for(char c : s) {
			int& k = next[i][c];
			if(k <= 0) k = newnode(i);
			i = k;
		}
		leaf[i] = id;
		//pats[i].pb(id);
	}
 	
	void build() {
		queue<int> q;
		q.push(0);
		while(!q.empty()) {
			int i = q.front(); q.pop();
			for(auto& j : next[i]) {	
				fail[j.sc] = i ? suffix(fail[i], j.fi) : 0;
				leaf[j.sc] = leaf[j.sc] == -1 ? leaf[fail[j.sc]] : leaf[j.sc];
				//pats[j.sc].insert(pats[j.sc].end(), all(pats[fail[j.sc]]));
				q.push(j.sc);
			}
		}
	}

	vector<int> countMatchings(string& s) {
		vector<int> frq(nw, 0), frqnd(nd, 0);
		vector<vector<int>> lv(nd);
		int i = 0;
		for(int i = 0; i < nd; ++i) lv[depth[i]].pb(i);
		for(char c : s) {
			i = suffix(i, c);
			++frqnd[i];
		}
		for(int h = nd - 1; h >= 0; --h) {
			for(int i : lv[h]) {
				frqnd[fail[i]] += frqnd[i];
				for(int j : pats[i]) frq[j] += frqnd[i];
			}
		}
		return frq;
	}

	vector<int> query(string& s) {
		vector<int> mat;
		int i = 0;
		for(char c : s) {
			i = suffix(i, c);
			for(int j = 0; j < (int)pats[i].size(); ++j)
				mat.pb(pats[i][j]);
		}
		return mat;
	}
 
	int suffix(int k, char c) {
		while(k && !next[k].count(c)) k = fail[k];
		return next[k].count(c) ? next[k][c] : 0;
	}
};

const int N = 1e6 + 10, M = 1e4 + 10;

Aho<N> aho;
int dp[M];

void solve() {
	int n;

	while(true) {
		cin >> n;

		if(!n) break;

		vector<string> a(n);

		for(auto& s : a) cin >> s;

		sort(all(a), [](const string& s, const string& t) {
			return s.size() < t.size();
		});

		aho.reset();
		for(int i = 0; i < n; ++i) {
			dp[i] = 0;
			aho.push(a[i], i);
		}
		aho.build();

		for(int i = 0; i < n; ++i) {	
			int l = 0, j = 0;
			for(char c : a[i]) {
				j = aho.suffix(j, c);
				int k = aho.leaf[j];
				if(k != -1) l = max(l, dp[k]);	
				k = aho.leaf[aho.fail[j]];
				if(k != -1) l = max(l, dp[k]);	
			}
			dp[i] = l + 1;
		}

		cout << *max_element(dp, dp + n) << '\n';
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
