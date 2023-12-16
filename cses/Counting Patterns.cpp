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
 
template<int MAXN, int ALPHA>
struct Aho {
	int next[MAXN][ALPHA], fail[MAXN], depth[MAXN], nd, nw;
	vector<int> pats[MAXN];
 
	Aho() {
		reset();
	}
 
	int newnode(int p = -1) {
		depth[nd] = p < 0 ? 0 : 1 + depth[p];
		pats[nd].clear();
		memset(next[nd], -1, sizeof next[nd]);
		fail[nd] = 0;
		return nd++;
	}
 
	void reset() {
		nd = nw = 0;
		newnode();
	}
 
	int h(char c) {
		return c - 'a';
	}
 
	void push(string& s, int id) {
		int i = 0;
		++nw;
		for(char c : s) {
			int& k = next[i][h(c)];
			if(k < 0) k = newnode(i);
			i = k;
		}
		pats[i].pb(id);	
	}
 	
	void build() {
		queue<int> q;
		q.push(0);
		while(!q.empty()) {
			int i = q.front(); q.pop();
			for(int c = 0; c < ALPHA; ++c) {
				int j = next[i][c];
				if(j < 0) continue;	
				fail[j] = i ? suffix(fail[i], c) : 0;	
				//pats[j].insert(pats[j].end(), all(pats[fail[j]]));
				q.push(j);
			}
		}
	}
 
	vector<int> countMatchings(string& s) {
		vector<int> frq(nw, 0), frqnd(nd, 0);
		vector<vector<int>> lv(nd);
		int i = 0;
		for(int i = 0; i < nd; ++i) lv[depth[i]].pb(i);
		for(char c : s) {
			i = suffix(i, h(c));
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
			i = suffix(i, h(c));
			for(int j = 0; j < (int)pats[i].size(); ++j)
				mat.pb(pats[i][j]);
		}
		return mat;
	}
 
	int suffix(int k, int c) {
		while(k && next[k][c] < 0) k = fail[k];
		return next[k][c] < 0 ? 0 : next[k][c];
	}
};
 
const int N = 5e5 + 10;
 
Aho<N, 26> aho;
 
void solve() {
	string s;
	int q;
	cin >> s >> q;		
	for(int i = 0; i < q; ++i) {
		string pat;
		cin >> pat;
		aho.push(pat, i);
	}
	aho.build();
	for(int x : aho.countMatchings(s)) cout << x << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}
