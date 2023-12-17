#include "bits/stdc++.h"
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

const int N = 25000 * 20, inf = 1e9;

int t[N][26], folhas[N], nos = 1, down_up[N], down[N], cnt[N];

void push(string& s) {
	int i = 0;
	for(char ch : s) {
		int& no = t[i][ch - 'a'];
		if(no < 0) {
			memset(t[nos], -1, sizeof t[nos]);
			no = nos++;
		}
		i = no;
	}
	++folhas[i];
}

void dfs(int u) {
	for(int v = 0; v < 26; ++v) {
		int z = t[u][v];
		if(z < 0) continue;
		dfs(z);
		cnt[u] += !!cnt[z];	
		down_up[u] += down_up[z];
	}
	down_up[u] += 2 * cnt[u];
	down[u] = inf;
	for(int v = 0; v < 26; ++v) {
		int z = t[u][v];
		if(z < 0 || !cnt[z]) continue;
		down[u] = min(down[u], down_up[u] - down_up[z] - 1 + down[z]);
	}
	if(folhas[u] && !cnt[u]) down[u] = 0;
	cnt[u] += folhas[u];
}

void answer(int u, int type) {

	if(folhas[u]) cout << "P\n";
	
	if(type) {
		int w = -1;
		
		for(int v = 0; v < 26; ++v) {
			int z = t[u][v];
			if(z < 0 || !cnt[z]) continue;
			int x = down_up[u] - down_up[z] - 1 + down[z];
			if(x == down[u]) w = v;
		}
		
		for(int v = 0; v < 26; ++v) {
			int z = t[u][v];
			if(z < 0 || !cnt[z]) continue;
			else if(v != w) {
				cout << char(v + 'a') << '\n';
				answer(z, 0);
				cout << "-\n";
			}
		}
		
		for(int v = 0; v < 26; ++v) {
			int z = t[u][v];
			if(z < 0 || !cnt[z]) continue;
			else if(v == w) {
				cout << char(v + 'a') << '\n';
				answer(z, 1);
			}
		}
		
	} else {
		for(int v = 0; v < 26; ++v) {
			int z = t[u][v];
			if(z < 0 || !cnt[z]) continue;
			cout << char(v + 'a') << '\n';
			answer(z, 0);
			cout << "-\n";
		}
	}
}

void solve() {
	int n;
	cin >> n;
	
	memset(t[0], -1, sizeof t[0]);
	
	for(int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		push(s);
	}
	
	dfs(0);
	cout << down[0] + n << '\n';
	answer(0, 1);
}
 
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--) solve();
    return 0;
}
