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

const int maxn = 5e5, inf = 1e9;

int pos[27], nxt[maxn][26], m, last[27];
int pre[2 * maxn + 1], x[2 * maxn + 1];
bool pode[maxn][26];
vi p[27], t[27], l[27];

void solve(vi&, vi&, vi&, int);

void solve(vi& a, vi& b, vi& c, int k) {
	if(a.empty()) {
		for(int j : c)
			pode[j][k] = true;
	} else {
		int N = a.size(), M = b.size();
		for(int i = 0; i < N; ++i) x[i] = a[i];
		x[N] = -1;
		for(int i = 0; i < M; ++i) x[i + N + 1] = b[i];
		pre[0] = 0;
		for(int i = 1; i <= N + M; ++i) {
			int j = pre[i - 1];
			while(j && x[i] != x[j]) 
				j = pre[j - 1];
			pre[i] = j;
			if(x[i] == x[j]) 
				++pre[i];
		}
		for(int i = N - 1; i < M; ++i) {
			if(pre[i + N + 1] == N)
				pode[c[i - N + 1]][k] = true;
		}
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s;
	int n, ans = 0;
	cin >> s >> n;
	memset(pos, -1, sizeof pos);
	for(int i = 0; i < n; ++i) {
		int k;
		cin >> k;
		if(pos[k] == -1)
			pos[k] = m++;
		else
			p[pos[k]].push_back(i - last[k]);
		last[k] = i;
	}
	for(int i = 0; i < (int)s.size(); ++i)
		l[s[i] - 'a'].push_back(i);
	for(int i = 0; i < 26; ++i)
		for(int j = 1; j < (int)l[i].size(); ++j)
			t[i].push_back(l[i][j] - l[i][j - 1]);
	for(int i = 0; i < 26; ++i) {
		if(l[i].empty())
			continue;
		for(int k = 0; k < m; ++k) {
			if(t[i].size() < p[k].size()) 
				continue;
			solve(p[k], t[i], l[i], k);
		}
	}
	for(int i = (int)s.size() - 1; i >= 0; --i) {
		if(i < (int)s.size() - 1) {
			bool ok = true;
			memcpy(nxt[i], nxt[i + 1], 26 * sizeof(int));
			for(int k = 0; k < 26; ++k) {
				int j = nxt[i][k];
				if(j == inf)
					break;
				else if(s[i] == s[j]) {
					ok = false;
					for(; k > 0; --k)
						nxt[i][k] = nxt[i][k - 1];
					nxt[i][0] = i;
					break;
				}
			}
			if(ok) {
				for(int k = 24; k >= 0; --k)
					nxt[i][k + 1] = nxt[i][k];
				nxt[i][0] = i;
			}
		} else {
			fill(nxt[i], nxt[i] + 26, inf);
			nxt[i][0] = i;
		}
	}
	for(int i = 0; i < (int)s.size(); ++i) {
		int cnt = 0;
		for(int j = 0; j < m; ++j) {
			int k = nxt[i][j];
			if(k > i + n - 1 || !pode[k][j])
				break;
			++cnt;
		}
		if(cnt == m)
			++ans;
	}
	cout << ans << '\n';;
	return 0;
}