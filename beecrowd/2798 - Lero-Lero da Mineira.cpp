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

const int maxn = 5e6 + 1;
static char out[maxn];
static int n, _, m = 0, I[26][2];
static string s[26], T;
static vi G[26];
static bool atcycle[26], path[26][26], vis[26];

static void dfs(int v);
static void getI(int v);

void dfs(int v) {
	vis[v] = true;
	for(int u : G[v]) {
		if(!vis[u]) dfs(u);
		if(atcycle[u])
			atcycle[v] = true;
	}
}

void getI(int v) {
	if(vis[v]) {
		for(int i = I[v][0]; i <= I[v][1]; ++i)
			out[m++] = out[i];
	}
	else if(G[v].empty()) {
		vis[v] = true;
		I[v][0] = I[v][1] = m;
		out[m++] = v + 'a';
	}
	else {
		int L = m, R = 0;
		vis[v] = true;
		for(int u : G[v]) {
			getI(u);
			R += I[u][1] - I[u][0] + 1;
		}
		I[v][0] = L;
		I[v][1] = R + L - 1;
	}
}

bool sol() {
	memset(&path[0][0], 0, sizeof path);
	memset(atcycle, 0, sizeof atcycle);
	memset(vis, 0, sizeof vis);
	for(int k = 0; k < 26; ++k) {
		for(char ch : s[k]) {
			if(ch == k + 'a') 
				atcycle[k] = s[k].size() > 1;
			else
				G[k].push_back(ch - 'a');
		}
		if(s[k].size() == 1 && s[k][0] == k + 'a') {
			s[k].clear();
			G[k].clear();
		}
	}
	for(int k = 0; k < 26; ++k) {
		if(s[k].empty()) continue;
		queue<int> S;
		S.push(k);
		path[k][k] = true;
		while(!S.empty()) {
			int u = S.front();
			S.pop();
			for(int v : G[u]) {
				if(!path[k][v]) {
					path[k][v] = true;
					S.push(v);
				}
			}
		}
	}
	for(int v = 0; v < 26; ++v) {
		for(int u = v + 1; u < 26; ++u) {
			if(path[u][v] && path[v][u])
				atcycle[v] = atcycle[u] = true;
		}
	}
	for(int v = 0; v < 26; ++v) {
		if(!vis[v]) 
			dfs(v);
	}
	bool solved = true;
	for(char ch : T) {
		if(atcycle[ch - 'a']) {
			solved = false;
			break;
		}
	}
	return solved;	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 0; i < n; ++i) {
		char ch;
		cin >> ch;
		cin >> s[ch - 'a'];		
	}
	cin >> _ >> T;
	if(sol()) {
		memset(vis, 0, sizeof vis);
		for(char ch : T)
			getI(ch - 'a');
		out[m] = '\0';
		cout << out << '\n';
	}
	else 
		cout << "-1\n";	
	return 0;
}