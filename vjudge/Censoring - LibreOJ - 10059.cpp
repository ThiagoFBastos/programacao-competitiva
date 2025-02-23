#include "bits/stdc++.h"

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
	char ch;
	int leaf;

	Vertex(int p, char ch = '$') : par {p}, ch {ch} {
		link = 0;
		leaf = -1;
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
		st[no].leaf = s.size();
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
 
void solve() {
	string t;
	int n;
	Aho aho;

	cin >> t >> n;
	
	for(int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		aho.push(s);
	}

	aho.bfs();

	stack<int> st;
	string ans;

	st.push(0);
	
	for(int i = 0; i < (int)t.size(); ++i) {
		int node = aho.go(st.top(), t[i]);
		int m = aho.st[node].leaf;
		ans += t[i];
		st.push(node);
		for(int j = 0; j < m; ++j) {
			st.pop();
			ans.pop_back();
		}
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
 
