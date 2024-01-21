#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int seg[4 * N], v[N], ans[N], p[N], n;
vector<int> adj[N];

int query(int l, int r, int lo, int hi, int p = 1) {
    if(l > r || r < lo || l > hi) return 0;
    else if(lo >= l && hi <= r) return seg[p];
    int mid = (lo + hi) / 2;
    int a = query(l, r, lo, mid, 2 * p);
    int b = query(l, r, mid + 1, hi, 2 * p + 1);
    return max(a, b);
}

void upd(int k, int x, int lo, int hi, int p = 1) {
    if(lo == hi) {seg[p] = x; return;}
    int mid = (lo + hi) / 2;
    if(k <= mid) upd(k, x, lo, mid, 2 * p);
    else upd(k, x, mid + 1, hi, 2 * p + 1);
    seg[p] = max(seg[2 * p], seg[2 * p + 1]);
}

void dfs(int u, int most = 1) {
    ans[u] = 1 + query(0, v[u] - 1, 0, n - 1);
    int last = query(v[u], v[u], 0, n - 1);
    upd(v[u], max(ans[u], last), 0, n - 1);
    ans[u] = max(ans[u], most);
    for(int v : adj[u]) dfs(v, max(most, ans[u]));
    upd(v[u], last, 0, n - 1);
}

void solve(int test) {
    
    cin >> n;

    for(int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        --p;
        adj[p].push_back(i);
    }

    for(int i = 0; i < n; ++i) {
        cin >> v[i];
        p[i] = v[i];   
    }

    sort(p, p + n);

    for(int i = 0; i < n; ++i) v[i] = lower_bound(p, p + n, v[i]) - p;

    dfs(0);

    for(int i = 1; i < n; ++i) cout << ans[i] << ' ';
    cout << '\n';
}

int main() {
    int t = 1;
    //cin >> t;
    for(int i = 1; i <= t; ++i) solve(i);
    return 0;
}


