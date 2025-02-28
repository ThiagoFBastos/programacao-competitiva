#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int K = 26;

struct Vertex {
	int next[K];
	int go[K];
	int par;
	int link;
	int frq;
	char ch;
	
	Vertex(int p, char ch = '$') : par {p}, ch {ch}, link {}, frq {} {
		memset(next, -1, sizeof next);
		memset(go, -1, sizeof go);
	}
};

char alpha(char ch) {
	return ch - 'a';
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
		++st[no].frq;
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
				no.frq += st[no.link].frq;
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

	int size() {
		return st.size();
	}		
};

const int N = 1e3 + 10;

int dp[N][N], n, m, nodes;
Aho aho;
string text;

int DP(int k, int j) {
	if(dp[k][j] != -1) return dp[k][j];
	else if(text[k] == '?') {
		dp[k][j] = INT_MIN;
		for(char ch = 'a'; ch <= 'z'; ++ch) {
			int i = aho.go(j, alpha(ch));
			dp[k][j] = max(dp[k][j], aho.st[i].frq + DP(k + 1, i));
		}
		return dp[k][j];
	}
	int i = aho.go(j, alpha(text[k]));
	return dp[k][j] = aho.st[i].frq + DP(k + 1, i);	
}

void recover(string& res, int best, int k, int j) {
	if(k == n) {
		res = "";
		return;
	} else if(text[k] == '?') {
		for(char ch = 'a'; ch <= 'z'; ++ch) {
			int i = aho.go(j, alpha(ch));
			if(aho.st[i].frq + DP(k + 1, i) == best) {
				recover(res, best - aho.st[i].frq, k + 1, i);
				res += ch;
				break;
			}
		}
		return;
	}
	int i = aho.go(j, alpha(text[k]));
	recover(res, best - aho.st[i].frq, k + 1, i);
	res += text[k];
}

void solve() {
	cin >> n >> m >> text;

	vector<string> dict(m);
	for(auto& s : dict) cin >> s;

	aho = Aho(dict);
	nodes = aho.size();

	for(int i = 0; i <= n; ++i)
	for(int j = 0; j < nodes; ++j)
		dp[i][j] = -1;

	memset(dp[n], 0, sizeof(int) * nodes);

	int best = DP(0, 0);
	string res;

	recover(res, best, 0, 0);

	cout << best << '\n';
	cout << string(res.rbegin(), res.rend()) << '\n';	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}