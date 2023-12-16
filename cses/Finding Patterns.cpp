#include "bits/stdc++.h"
 
using namespace std;
 
template<int N>
struct SuffixArray {
	int tsa[N], c[N], tc[N], head[N], inv[N], sa[N], lcp[N], length;
	char str[N];
 
	void bucket(int n, int L) {
		memset(head, 0, sizeof head);
 
		for(int i = 0; i < n; ++i) ++head[c[i]];
 
		int maxi = max(300, n), k = 0;
 
		for(int i = 0; i < maxi; ++i) {
			swap(k, head[i]);
			k += head[i];
		}
 
		for(int i = 0; i < n; ++i) {
			int j = (sa[i] - L + n) % n;
			tsa[head[c[j]]++] = j;
		}
 
		memcpy(sa, tsa, n * sizeof(int));
	}
 
	void suffixarray() {
		int n = length + 1;
		for(int i = 0; i < n; ++i) {
			sa[i] = i;
			c[i] = str[i];
		}
		bucket(n, 0);
		for(int L = 1; L < n; L <<= 1) {
			bucket(n, L);
			for(int i = 0, cc = -1; i < n; ++i)
				tc[sa[i]] = !i || c[sa[i]] != c[sa[i - 1]] || c[(sa[i] + L) % n] != c[(sa[i - 1] + L) % n] ? ++cc : cc;
			memcpy(c, tc, n * sizeof(int));
		}
		for(int i = 0; i < n - 1; ++i) sa[i] = sa[i + 1];
	}
 
	void computeLCP() {
		int k = 0;
		for(int i = 0; i < length; ++i) inv[sa[i]] = i;
		for(int j = 0; j < length; ++j) {
			int i = inv[j];
			while(i > 0 && str[sa[i] + k] == str[sa[i - 1] + k]) ++k;
			lcp[i] = k;
			k = max(k - 1, 0);
		}
	}
 
	int lower_bound(const char* target) {
		int n = strlen(target), l = 0, r = length - 1;
		while(l < r) {
			int m = (l + r) / 2, i = sa[m], j = 0;
			while(i < length && j < n && str[i] == target[j]) ++i, ++j;
			if(str[i] >= target[j]) r = m;
			else l = m + 1;
		}
		return sa[r];
	}
 
    bool contains(const char* target) {
        int k = lower_bound(target), i = 0;
        while(str[k] && target[i] && str[k] == target[i]) ++k, ++i;
        return !target[i];
    }
 
	SuffixArray() {}
 
	SuffixArray(const char* _str) {
		build(_str);
	}
 
	void build(const char* _str) {
		length = strlen(_str);
		strcpy(str, _str);
		suffixarray();
	}
};
 
const int N = 1e5 + 10;
 
SuffixArray<N> sa;
 
void solve(int test) {  
    int q;
    string str;
 
    cin >> str >> q;
 
    sa = SuffixArray<N>(str.c_str());
 
    while(q--) {
        string s;
        cin >> s;
        cout << (sa.contains(s.c_str()) ? "YES\n" : "NO\n");
    }
}
 
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
 
    int t = 1;
 
    //cin >> t;
 
    for(int i = 1; i <= t; ++i) solve(i);
 
    return 0;
}
