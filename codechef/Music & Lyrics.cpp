#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int K = 63;

int alpha(char ch) {
	if(ch >= 'a' && ch <= 'z') return ch - 'a';
	else if(ch >= 'A' && ch <= 'Z') return 26 + ch - 'A';
	else if(ch >= '0' && ch <= '9') return 52 + ch - '0';
	return K - 1;
}

struct Vertex {
	int next[K];
	int go[K];
	int par;
	int link;
	char ch;
	int next_leaf;
	bool is_leaf;
	vector<int> words;
	
	Vertex(int p, char ch = '$') : par {p}, ch {ch}, link {}, is_leaf {}, next_leaf {-1} {
		memset(next, -1, sizeof next);
		memset(go, -1, sizeof go);
	}
};

struct Aho {
	vector<Vertex> st;

	Aho() {}

	Aho(vector<string>& words) {
		st.push_back(Vertex(0));
		st.back().next_leaf = 0;
		for(int i = 0; i < (int)words.size(); ++i) push(words[i], i);
		bfs();
	}

	void push(string& s, int index) {
		int no = 0;
		for(char ch : s) {
			ch = alpha(ch);
			if(st[no].next[ch] == -1) {
				st[no].next[ch] = st.size();
				st.emplace_back(no, ch);
			}		
			no = st[no].next[ch];
		}
		st[no].is_leaf = true;
		st[no].words.push_back(index);
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
				for(int v = st[no.par].link; v >= 0; v = st[v].link) {
					Vertex& n = st[v];
					if(n.next[e] != -1) {
						no.link = n.next[e];
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
		if(v.go[ch] != -1) return v.go[ch];
		return v.go[ch] = v.next[ch] != -1 ? v.next[ch] : go(v.link, ch);
	}

	int get_next_link(int no) {
		Vertex& v = st[no];
		if(v.next_leaf != -1) return v.next_leaf;
		int link = v.link;
		return v.next_leaf = st[link].is_leaf ? link : get_next_link(link);
	}

	int countNodes() {
		return st.size();
	}
};

void solve() {
	int n, q, nodes;

	cin >> q;

	vector<string> word(q);

	for(auto& s : word) cin >> s;

	Aho aho(word);
	
	nodes = aho.countNodes();

	vector<int> frq(q, 0), frqNode(nodes, 0), deg(nodes, 0);
	queue<int> fila;

	cin >> n;

	while(n--) {
		string text;
		int node = 0;
		cin >> text;
		for(char ch : text) {
			node = aho.go(node, alpha(ch));
			++frqNode[node];
		}
	}

	for(int i = 1; i < nodes; ++i) ++deg[aho.st[i].link];
	for(int i = 1; i < nodes; ++i) if(deg[i] == 0) fila.push(i);

	while(!fila.empty()) {
		int no = fila.front();
		fila.pop();
		for(int pos : aho.st[no].words) frq[pos] += frqNode[no];
		int link = aho.st[no].link;
		frqNode[link] += frqNode[no];
		if(--deg[link] == 0) fila.push(link);
	}
	
	for(int ans : frq) cout << ans << '\n';	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}