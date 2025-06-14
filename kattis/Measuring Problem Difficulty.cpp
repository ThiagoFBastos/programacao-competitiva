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

int n, sz;
ordered_set<int> st[1 << 19];

void upd(int, int);
int query(int, int, int);

void upd(int k, int x) {
    for(k += sz; k > 0; k >>= 1) st[k].insert(x);
}

int query(int l, int r, int x) {
    int ans = 0;
    for(l += sz, r += sz; l <= r; l >>= 1, r >>= 1) {
        if(l & 1) ans += st[l++].order_of_key(x);
        if(!(r & 1)) ans += st[r--].order_of_key(x);
    }
    return ans;
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while(true) {
        cin >> n;
        if(n == 0) break;
        vector<tuple<int, int, int>> S(n);
        vi a(n), b(n);
        ll ans = 0;
        for(int i = 0; i < n; ++i) {
            int p;
            cin >> p;
            a[p - 1] = i;
        }
        for(int i = 0; i < n; ++i) {
            int p;
            cin >> p;
            b[p - 1] = i;
        }
        for(int i = 0; i < n; ++i) {
            int p;
            cin >> p;
            S[p - 1] = {a[p - 1], b[p - 1], i};
        }
        sort(S.begin(), S.end());
        sz = 1 << (32 - __builtin_clz(n));
        for(int k = 0; k < n; ++k) {
            ans += query(0, get<1>(S[k]), get<2>(S[k]));
            upd(get<1>(S[k]), get<2>(S[k]));
        }
        cout << ans << '\n';
        for(int k = 0; k < (sz << 1); ++k) st[k].clear();
    }
    return 0;
}
