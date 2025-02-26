#include "bits/stdc++.h"
using namespace std;
const int INF = 1e9;
using ii = pair<int, int>;
struct SegTree {
    vector<ii> st;
    int n;
    SegTree() {}
    SegTree(int n) {
        this->n = n;
        st.assign(2 * n + 1, make_pair(INF, INF));
    }
    void upd(int k, int x) {
        k += n;
        st[k] = {x, k - n};
        for(k /= 2; k; k /= 2) st[k] = min(st[2 * k], st[2 * k + 1]);
    }
    ii query(int l, int r) {
        ii ans = {INF, INF};
        l += n, r += n;
        while(l <= r) {
            if(l & 1) ans = min(ans, st[l++]);
            if(~r & 1) ans = min(ans, st[r--]);
            l /= 2;
            r /= 2;
        }
        return ans;
    }
};

vector<vector<int>> G;
int tms, n, d;
vector<int> L, R, h;
SegTree st;

void dfs(int u, int p = -1) {
    L[u] = R[u] = tms++;
    for(int v : G[u]) {
        if(v == p) continue;
        h[v] = 1 + h[u];
        dfs(v, u);
        R[u] = R[v];
    }
    for(int v : G[u]) {
        if(v == p) continue;
        while(true) {
            auto [xa, xb] = st.query(L[v], R[v]);
            auto [ya, yb] = min(st.query(L[u], L[v] - 1), st.query(R[v] + 1, R[u]));
            if(xa + ya - 2 * h[u] < d) {
                if(xa < ya) st.upd(xb, INF);
                else st.upd(yb, INF);
            } else break;
        }
    }
    if(st.query(L[u], R[u]).first - h[u] >= d) st.upd(L[u], h[u]);
}

void solve() {
    cin >> n >> d;
    G.resize(n);
    L.resize(n);
    R.resize(n);
    h.resize(n);
    for(int i = 1; i < n; ++i) {
        int x;
        cin >> x;
        G[x].push_back(i);
        G[i].push_back(x);
    }
    st = SegTree(n);
    h[0] = 0;
    dfs(0);
    int cnt = 0;
    for(int v = 0; v < n; ++v) cnt += st.query(v, v).first != INF;
    cout << cnt << '\n'; 
}
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}