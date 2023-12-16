#include "bits/stdc++.h"
using namespace std;
const int maxn = 1e6 + 1, mod = 1e9 + 7;
int t[maxn][26], sz;
bool leaf[maxn];
void trie_init() {
	leaf[0] = false;
	memset(t[0], -1, sizeof t[0]);
	sz = 1;
}
void push(string& s) {
	int no = 0;
	for(int i = 0; i < (int)s.size(); ++i) {
		int nxt = s[i] - 'a';
		if(t[no][nxt] == -1) {
			for(; i < (int)s.size(); ++i) {
				nxt = s[i] - 'a';
				memset(t[sz], -1, sizeof t[sz]);
				leaf[sz] = false;
				no = t[no][nxt] = sz++;
			}
			break;
		}
		no = t[no][nxt];
	}
	leaf[no] = true;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s;
	int n;
	cin >> s >> n;
	trie_init();
	for(int i = 0; i < n; ++i) {
		string p;
		cin >> p;
		push(p);
	}
	vector<int> cnt(s.size() + 1);
	cnt.back() = 1;
	for(int i = (int)s.size() - 1; i >= 0; --i) {
		int no = 0;
		for(int k = i; k < (int)s.size(); ++k) {
			no = t[no][s[k] - 'a'];
			if(no == -1) break;
			else if(leaf[no]) {
				cnt[i] += cnt[k + 1];
				if(cnt[i] >= mod)
					cnt[i] -= mod;
			}
		}
	}
	cout << cnt[0] << '\n';
	return 0;
}
