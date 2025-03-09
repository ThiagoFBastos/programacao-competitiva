#pragma GCC target("sse,mmx,sse2")
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

const int maxn = 1e4 * 25 + 1;
int n, q, nos = 1, t[maxn][26], folha[maxn];

void insert(string& s, int flag) {
	int k = 0;
	for(int i = 0; i < (int)s.size(); ++i) {
		int nxt = s[i] - 'a';
		if(t[k][nxt] == -1) {
			for(; i < (int)s.size(); ++i) {
				nxt = s[i] - 'a';
				memset(t[nos], -1, sizeof t[nos]);
				folha[nos] = INT_MAX;
				k = t[k][nxt] = nos++;
			}
			break;
		}
		k = t[k][nxt];
	}
	folha[k] = min(folha[k], flag);
}

bool find(string& s) {
	int k = 0;
	bool ok = true;
	for(char c : s) {
		int nxt = c - 'a';
		if(t[k][nxt] == -1) {
			ok = false;
			break;
		}
		k = t[k][nxt];
	}
	return ok && folha[k] != INT_MAX;
}

int solve(string& s, int k, int node, int wrong) {
	if(node == -1) return INT_MAX;
	else if(k == (int)s.size()) {
		if(wrong) return folha[node];
		int res = folha[node];
		for(int c = 0; c < 26; ++c) res = min(res, solve(s, k, t[node][c], 1));
		return res;
	}
	else if(wrong) return solve(s, k + 1, t[node][s[k] - 'a'], 1);
	int res = INT_MAX;
	if(k < (int)s.size() - 1 && s[k] != s[k + 1]) {
		swap(s[k], s[k + 1]);
		res = min(res, solve(s, k + 1, t[node][s[k] - 'a'], 1));
		swap(s[k], s[k + 1]);
	}
	for(int c = 0; c < 26; ++c)
		res = min(res, min(solve(s, k, t[node][c], 1), solve(s, k + 1, t[node][c], s[k] != c + 'a')));
	res = min(res, solve(s, k + 1, node, 1));
	return res;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	memset(t[0], -1, sizeof t[0]);
	folha[0] = INT_MAX; 
	cin >> q;
	vector<string> w(q);
	for(int i = 0; i < q; ++i) {
		cin >> w[i];
		insert(w[i], i);
	}
	cin >> n;
	while(n--) {
		string s;
		cin >> s;
		if(find(s)) 
			cout << s << " is correct\n";
		else {
			int k = solve(s, 0, 0, 0);
			cout << s << ' ';
			if(k == INT_MAX) cout << "is unknown\n";
			else cout << "is a misspelling of " << w[k] << '\n';
		}
	}
	return 0;
}