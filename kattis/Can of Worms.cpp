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
using T = tuple<int, int, int>;

const int inf = 1e9;

struct SegTree {
    vector<int> st;
    int n;
    SegTree() {}
    SegTree(int n) : n {n} {
        st.assign(2 * n + 1, inf);
    }
    void upd(int k, int x) {
        k += n;
        st[k] = x;
        for(k >>= 1; k; k >>= 1) st[k] = min(st[k << 1], st[(k << 1) | 1]);
    }
    int query(int l, int r) {
        int ans = inf;
        for(l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if(l & 1) ans = min(ans, st[l++]);
            if(~r & 1) ans = min(ans, st[r--]);
        }
        return ans;
    }
};

vector<T> c;
vector<ii> rng;
vector<int> t, low, scc;
int n, tms, id;
set<int> S;
stack<int> q;
SegTree lo;

void dfs(int u) {
    int l = rng[u].first, r = rng[u].second;
    low[u] = t[u] = tms++;
    lo.upd(u, t[u]);
    S.erase(u);
    q.push(u);
    low[u] = min(low[u], lo.query(l, r));
    lo.upd(u, low[u]);
    while(l <= r) {
        auto it = S.lower_bound(l);
        if(*it > r) break;
        dfs(*it);
        low[u] = min(low[u], lo.query(rng[u].first, r));
        lo.upd(u, low[u]);
        l = *it + 1;
    }
    if(t[u] == low[u]) {
        while(true) {
            int v = q.top();
            q.pop();
            scc[v] = id;
            lo.upd(v, inf);
            if(u == v) break;
        }
        ++id;
    }
}

vector<int> L, R;

void get_range() {
    vector<vector<int>> S(n);
    SegTree l(n), r(n);

    L.resize(n);
    R.resize(n);

    for(int i = 0; i < n; ++i) {
        S[scc[i]].push_back(i);
        L[i] = rng[i].first;
        R[i] = rng[i].second;
    }

    for(int i = 0; i < n; ++i) {
        auto& v = S[i];
        int lo = n, hi = 0;

        for(int u : v) {
            lo = min(lo, L[u]);
            hi = max(hi, R[u]);
        }

        lo = min(lo, l.query(lo, hi));
        hi = max(hi, -r.query(lo, hi));
        
        for(int u : v) {
            l.upd(u, lo);
            r.upd(u, -hi);
            L[u] = lo, R[u] = hi;
        }
    }
}
    
void solve() {
    cin >> n;

    c.resize(n);
    rng.resize(n);
    t.assign(n, -1);
    low.resize(n);
    scc.assign(n, -1);
    lo = SegTree(n);

    for(int i = 0; i < n; ++i) {
        int x, r;
        cin >> x >> r;
        c[i] = {x, r, i};
        S.insert(i);
    }

    S.insert(n);
    sort(c.begin(), c.end());

    for(int i = 0; i < n; ++i) {
        auto [x, r, k] = c[i];
        int lo = lower_bound(c.begin(), c.end(), T(x - r, -1, -1)) - c.begin();
        int hi = upper_bound(c.begin(), c.end(), T(x + r, inf, inf)) - c.begin() - 1;
        rng[i] = {lo, hi};
    }

    for(int i = 0; i < n; ++i) if(t[i] < 0) dfs(i);

    get_range();
    vector<int> ans(n);
    for(int i = 0; i < n; ++i) ans[get<2>(c[i])] = R[i] - L[i] + 1;
    for(int i = 0; i < n; ++i) cout << ans[i] << ' ';
    cout << '\n';
}

int main() {
    int t = 1;
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    //cin >> t;
    while(t--) solve();
}