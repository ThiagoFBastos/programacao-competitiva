#include <bits/stdc++.h>

using namespace std;

constexpr int N = 2e4 + 5;

int in[N], low[N], scc[N], time_in, scc_id;
int n, m, source;
bool is_source[N];
vector<int> adj[N];
stack<int> st;

void dfs(int u) {
    in[u] = low[u] = time_in++;
    st.push(u);

    for(const auto& v : adj[u]) {
        if(in[v] == -1) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if(scc[v] == -1)
            low[u] = min(low[u], low[v]);
    }

    if(in[u] != low[u])
        return;

    int v = -1;

    do
    {
        v = st.top();
        st.pop();
        scc[v] = scc_id;
    } while (u != v);

    ++scc_id;
}

void decompSCC() {
    memset(in, -1, sizeof(int) * n);
    memset(scc, -1, sizeof(int) * n);
    fill(is_source, is_source + n, true);

    ranges::for_each(views::iota(0, n), [&](auto u) {
        if(in[u] == -1)
            dfs(u);
    });

    ranges::for_each(views::iota(0, n), [&](auto u) {
        for(const auto& v : adj[u]) {
            if(scc[u] == scc[v])
                continue;

            is_source[scc[v]] = false;
        }
    });
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> source;

    --source;

    for(int i = 0; i < m; ++i) {
        int from, to;
        cin >> from >> to;
        adj[from - 1].push_back(to - 1);
    }

    decompSCC();

    int cnt = count(is_source, is_source + scc_id, true);

    if(is_source[scc[source]])
        --cnt;

    cout << cnt << '\n';

    return 0;
}