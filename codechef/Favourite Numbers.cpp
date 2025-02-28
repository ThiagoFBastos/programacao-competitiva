#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 20;
const int M = 62 * N;
const int K = 10;

struct Vertex {
	int next[K];
	int go[K];
	int par;
	int link;
	bool has_leaf;
	char ch;
	
	Vertex(int p, char ch = '$') : par {p}, ch {ch}, link {}, has_leaf {} {
		memset(next, -1, sizeof next);
		memset(go, -1, sizeof go);
	}
};

int alpha(char ch) {
	return ch - '0';
}

struct Aho {
	vector<Vertex> st;

	Aho() {}

	Aho(vector<string>& words) {
		st.push_back(Vertex(0));
		for(auto& s : words) push(s);
		bfs();
	}

	void push(string& s) {
		int no = 0;
		for(char ch : s) {
			ch = alpha(ch);
			if(st[no].next[ch] == -1) {
				st[no].next[ch] = st.size();
				st.emplace_back(no, ch);
			}		
			no = st[no].next[ch];
		}
		st[no].has_leaf = true;
	}

	void bfs() {
		queue<int> q;

		q.push(0);
		for(int i = 0; i < K; ++i) st[0].next[i] = max(0, st[0].next[i]);

		while(!q.empty()) {
			int from = q.front();
			q.pop();
			
			Vertex& no = st[from];
			char e = no.ch;
			int par = no.par;

			if(par) {	
				for(int v = st[par].link; v >= 0; v = st[v].link) {
					Vertex& n = st[v];
					if(n.next[e] != -1) {
						no.link = n.next[e];
						break;
					}
				}
				no.has_leaf |= st[no.link].has_leaf;
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
		if(v.go[ch] != -1) return v.go[ch];
		return v.go[ch] = v.next[ch] != -1 ? v.next[ch] : go(v.link, ch);
	}

	int size() const {
		return st.size();
	}
};

i64 dp[2][N][M];

vector<string> words;
Aho aho;

i64 count(i64 r) {
	string R = to_string(r);
	int n = R.size(), m = aho.size();

	for(int i = 0; i < 2; ++i)
	for(int k = 0; k < n; ++k)
	for(int j = 0; j < m; ++j)
		dp[i][k][j] = 0;

	for(int i = 0; i <= R[0] - '0'; ++i) {
		int no = aho.go(0, alpha(i + '0'));
		++dp[aho.st[no].has_leaf][0][no];
	}

	int j = aho.go(0, alpha(R[0]));
	bool good = aho.st[j].has_leaf;

	for(int i = 1; i < n; ++i) {
		
		// 0

		for(int k = 0; k < m; ++k) { 
			for(char c = '0'; c <= '9'; ++c) {
				int l = aho.go(k, alpha(c));
				dp[aho.st[l].has_leaf][i][l] += dp[0][i - 1][k];
			}
		}

		// 1

		for(int k = 0; k < m; ++k) { 
			for(int c = '0'; c <= '9'; ++c) {
				int l = aho.go(k, alpha(c));
				dp[1][i][l] += dp[1][i - 1][k];
			}
		}

		for(char c = R[i] + 1; c <= '9'; ++c) {
			int l = aho.go(j, alpha(c));
			if(aho.st[l].has_leaf && !good) --dp[good ^ 1][i][l];
			else --dp[good][i][l];
		}

		j = aho.go(j, alpha(R[i]));
		good |= aho.st[j].has_leaf;
	}

	i64 ans = 0;
	for(int i = 0; i < m; ++i) ans += dp[1][n - 1][i];
	return ans;
}

void solve() {
	
	i64 l, r, k;
	int n;

	cin >> l >> r >> k >> n;

	words.resize(n);

	for(int i = 0; i < n; ++i) {
		i64 w;
		cin >> w;
		words[i] = to_string(w);
	}

	aho = Aho(words);

	i64 RC = count(r);
	i64 LC = count(l - 1);

	if(RC - LC < k) {
		cout << "no such number\n";
		return;
	}

	while(l < r) {
		i64 mid = (l + r) / 2;
		if(count(mid) - LC >= k) r = mid;
		else l = mid + 1;
	}

	cout << r << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}