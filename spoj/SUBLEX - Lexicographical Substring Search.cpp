#pragma GCC optimize("O3,unroll-loops")
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

vi suffix_array(string& s) {
    s += '$';
    int n = s.size();
    vi p(n), c(n), pt(n), ct(n), cnt(1 + max(128, n), 0);
    for(char ch : s) ++cnt[ch + 1];
    for(int k = 1; k < 128; ++k) cnt[k] += cnt[k - 1];
    for(int k = 0; k < n; ++k) c[k] = cnt[s[k]];
    for(int k = 0; k < n; ++k) p[cnt[s[k]]++] = k;
    for(int k = 0; (1 << k) <= n; ++k) {
        fill(cnt.begin(), cnt.end(), 0);
        for(int i = 0; i < n; ++i) {
            int h = p[i] - (1 << k);
            if(h < 0) h += n;
            ++cnt[c[h] + 1];
        }
        for(int i = 1; i < n; ++i) cnt[i] += cnt[i - 1];
        for(int i = 0; i < n; ++i) {
            int h = p[i] - (1 << k);
            if(h < 0) h += n;
            pt[cnt[c[h]]++] = h;
        }
        copy(pt.begin(), pt.end(), p.begin());
        ct[p[0]] = 0;
        for(int i = 1; i < n; ++i) {
            int A = p[i], B = p[i] + (1 << k), C = p[i - 1], D = p[i - 1] + (1 << k);
            if(B >= n) B -= n;
            if(D >= n) D -= n;
            ct[p[i]] = (c[A] != c[C] or c[B] != c[D]) + ct[p[i - 1]];
        }
        copy(ct.begin(), ct.end(), c.begin());
    }
    p.erase(p.begin());
    s.pop_back();
    return p;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    string s;
    int q, n, lp = 0;
    cin >> s >> q;
    n = s.size();
    vi a = suffix_array(s);
    vi p(n), ps(n);
    vector<ll> cnt(n + 1);
    for(int i = 0; i < n; ++i) 
        ps[a[i]] = i;
    for(int i = 0; i < n; ++i) {
        if(ps[i] == 0) 
            p[ps[i]] = 0;
        else {
            int k = a[ps[i] - 1], j = lp;
            while(j + max(k, i) < n && s[k + j] == s[i + j]) ++j;
            p[ps[i]] = j;
            lp = max(0, j - 1);
        }
    }
    cnt[0] = 0;
    for(int i = 0; i < n; ++i) 
        cnt[i + 1] = n - (a[i] + p[i]) + cnt[i];
    while(q--) {
        int k;
        cin >> k;
        int j = lower_bound(cnt.begin(), cnt.end(), 0LL + k) - cnt.begin();
        cout << s.substr(a[j - 1], p[j - 1] + k - cnt[j - 1]) << '\n';
    }
	return 0;
}
