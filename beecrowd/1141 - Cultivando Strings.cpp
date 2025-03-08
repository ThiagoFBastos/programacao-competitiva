#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int K = 26;
 
struct Vertex {	
	int next[K];
	int par;
	int link;
	int next_leaf;
	char ch;
 	int dp;
	bool is_leaf;

	Vertex(int p, char ch = '$') : par {p}, ch {ch} {
		link = dp = next_leaf = 0;
		is_leaf = false;
		memset(next, -1, sizeof next);
	}
};
 
struct Aho {
	vector<Vertex> st;
 
	Aho() {
		st.push_back(Vertex(0));
	}

	Aho(vector<string>& words) {
		int n = 1;
		for(string& s : words) n += s.size();
		st.reserve(n);
		st.push_back(Vertex(0));
		for(string& s : words) push(s);	
		build();
	}
 
	int charToNum(char ch) {
		return ch - 'a';
	}

	void push(string& s) {
		int no = 0;
		for(char ch : s) {		
			int c = charToNum(ch);
			if(st[no].next[c] < 0) {
				st[no].next[c] = st.size();
				st.emplace_back(no, ch);
			}
			no = st[no].next[c];
		}
		st[no].is_leaf = true;
	}
 
	void build() {
		queue<int> q;
 
		q.push(0);
		for(int i = 0; i < K; ++i) st[0].next[i] = max(0, st[0].next[i]);
 
		while(!q.empty()) {
			int from = q.front();
			q.pop();
			
			Vertex& no = st[from];
			int c = charToNum(no.ch);
 
			if(no.par) {
				for(int v = st[no.par].link; ; v = st[v].link) {
					Vertex& n = st[v];
					if(n.next[c] != -1) {
						no.link = n.next[c];
						no.next_leaf = st[no.link].is_leaf ? no.link : st[no.link].next_leaf; 
						break;
					}
				}
			}
 
			for(int i = 0; i < K; ++i) {
				if(no.next[i] <= 0) continue;
				q.push(no.next[i]);
			}
		}
	}
 /*
	int go(int no, char ch) {
		Vertex& v = st[no];		
		int a = charToNum(ch);
		if(v.go[a] != -1) return v.go[a];
		return v.go[a] = v.next.count(a) ? v.next[a] : go(v.link, a);
	}*/

	int go(int no, char ch) {
		return st[no].next[charToNum(ch)];
	}
 
	int nodes() {
		return st.size();
	}
};
 
void solve() {
	int n;

	cin >> n;

	if(!n) exit(0);

	vector<string> words(n);

	for(auto& s : words) cin >> s;

	sort(words.begin(), words.end(), [](const string& a, const string& b) {
		return a.size() < b.size();
	});

	Aho aho(words);
	int ans = 0;

	for(int i = 0; i < n; ++i) {
		int k = 0, dp = 0;
		for(char ch : words[i]) {
			k = aho.go(k, ch);
			for(int j = k, l = 0; j && l < 2; j = aho.st[j].next_leaf, ++l)
				dp = max(dp, aho.st[j].dp);
		}
		ans = max(ans, dp + 1);
		aho.st[k].dp = dp + 1;
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	//int t = 1;
	//cin >> t;
	while(1) solve();
	return 0;
}