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

i64 exp(i64 n, int p, int m) {
	i64 ans = 1;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = ans * n % m;
		n = n * n % m;
	}
	return ans;
}

template<int m>
struct modInt {
	int val;
	
	modInt() {val = 0;}
	modInt(int val) : val {val} {}
	
	modInt operator^(int p) {
		return modInt(exp(val, p, m));
	}
	
	modInt& operator^=(int p) {
		val = exp(val, p, m);
		return *this;
	}

	modInt operator+(modInt x) {
		int ans = val + x.val;
		if(ans >= m) ans -= m;
		return {ans};
	}
	
	modInt operator-(modInt x) {
		int ans = val - x.val;
		if(ans < 0) ans += m;
		return {ans};
	}
	
	modInt& operator+=(modInt x) {
		val += x.val;
		if(val >= m) val -= m;
		return *this;
	}
	
	modInt& operator-=(modInt x) {
		val -= x.val;
		if(val < 0) val += m;
		return *this;
	}
	
	modInt operator*(modInt x) {
		return modInt((i64)val * x.val % m);
	}

	modInt& operator*=(modInt x) {
		val = (i64)val * x.val % m;
		return *this;
	}
	
	modInt operator/(modInt x) {
		return modInt(val * exp(x.val, m - 2, m) % m);
	}
	
	modInt& operator/=(modInt x) {
		val = val * exp(x.val, m - 2, m) % m;
		return *this;
	}
	
	modInt operator+(int x) {
		int ans = val + x;
		if(ans >= m) ans -= m;
		if(ans < 0) ans += m;
		return {ans};
	}
	
	modInt operator-(int x) {
		int ans = val - x;
		if(ans < 0) ans += m;
		if(ans >= m) ans -= m;
		return {ans};
	}
	
	modInt& operator+=(int x) {
		val += x;
		if(val >= m) val -= m;
		if(val < 0) val += m;
		return *this;
	}
	
	modInt& operator-=(int x) {
		val -= x;
		if(val < 0) val += m;
		if(val >= m) val -= m;
		return *this;
	}
	
	modInt operator*(int x) {
		i64 ans = (i64)val * x % m;
		if(ans < 0) ans += m;
		return modInt(ans);
	}
	
	modInt& operator*=(int x) {
		val = (i64)val * x % m;
		if(val < 0) val += m;
		return *this;
	}
	
	modInt operator/(int x) {
		return modInt(val * exp(x, m - 2, m) % m);
	}
	
	modInt& operator/=(int x) {
		val = val * exp(x, m - 2, m) % m;
		return *this;
	}
};

template<int m>
ostream& operator<<(ostream& os, modInt<m> v) {
	os << v.val;
	return os;
}

template<int m>
istream& operator>>(istream& is, modInt<m>& v) {
	is >> v.val;
	return is;
}

const int K = 26;
 
struct Vertex {
	int next[K];
	int go[K];
	int par;
	int link;
	char ch;
	bool leaf;

	Vertex(int p, char ch = '$') : par {p}, ch {ch} {
		link = 0;
		leaf = false;
		memset(next, -1, sizeof next);
		memset(go, -1, sizeof go);
	}
};
 
struct Aho {
	vector<Vertex> st;
 
	Aho() {
		st.push_back(Vertex(0));
	}

	int charIndex(char ch) {
		return ch - 'a';
	}
 
	void push(string& s) {
		int no = 0;
		for(char ch : s) {
			int c = charIndex(ch);
			if(st[no].next[c] == -1) {
				st[no].next[c] = st.size();
				st.emplace_back(no, ch);
			}
			no = st[no].next[c];
		}
		st[no].leaf = true;
	}
 
	void bfs() {
		queue<int> q;
 
		q.push(0);
		for(int i = 0; i < K; ++i) st[0].next[i] = max(0, st[0].next[i]);
 
		while(!q.empty()) {
			int from = q.front();
			q.pop();
			
			Vertex& no = st[from];
			int c = charIndex(no.ch);
			int par = no.par;
 
			if(par) {	
				for(int v = st[no.par].link; v >= 0; v = st[v].link) {
					Vertex& n = st[v];
					if(n.next[c] != -1) {
						no.link = n.next[c];
						break;
					}
				}
			}
 
			for(int i = 0; i < K; ++i) {
				int next = no.next[i];
				if(next <= 0) continue;
				q.push(next);
			}
		}
	}
 
	int go(int no, char ch) {
		Vertex& v = st[no];
		int c = charIndex(ch);
		if(v.go[c] != -1) return v.go[c];
		return v.go[c] = v.next[c] != -1 ? v.next[c] : go(v.link, ch);
	}
 
	int nodes() {
		return st.size();
	}
};

const int N = 64, MOD = 1e9 + 7;

vector<vector<int>> seq[10];

void solve() {
	int n, a, b, c;

	cin >> n >> a >> b >> c;

	for(int i = 1; i <= 7; ++i) {
		seq[i].pb({i});
		for(int j = 1; j < i; ++j) {
			if(seq[i - j].empty()) continue;
			for(auto& S : seq[i - j]) {
				seq[i].pb(S);
				seq[i].back().pb(j);
			}
		}
	}

	Aho aho;

	for(auto& A : seq[a]) {
		for(auto& B : seq[b]) {
			for(auto& C : seq[c]) {
				string s;

				if((int)A.size() + (int)B.size() + (int)C.size() > n) continue;

				for(int x : A) s += 'a' + x - 1;
				for(int x : B) s += 'a' + x - 1;
				for(int x : C) s += 'a' + x - 1;

				aho.push(s);
			}
		}
	}

	aho.bfs();

	int m = aho.nodes();

	vector<modInt<MOD>> dp(m, 0);

	dp[0] = 1;

	for(int i = 0; i < n; ++i) {
		vector<modInt<MOD>> cp(m, 0);

		for(int j = 0; j < m; ++j) {
			for(char c = 'a'; c <= 'j'; ++c) {
				int k = aho.go(j, c);
				if(aho.st[k].leaf) continue;
				cp[k] += dp[j];
			}
		}

		swap(cp, dp);
	}
	
	modInt<MOD> cnt = exp(10, n, MOD);
	for(auto x : dp) cnt -= x;

	cout << cnt << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
