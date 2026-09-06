#include <bits/stdc++.h>

using namespace std;

constexpr int N = 5e3 + 5;

int n, m;
int in[N], low[N], scc_id[N];
int timestamp, scc_timestamp;
vector<int> adj[N];
stack<int> st;

void dfs(int u) {
	in[u] = low[u] = timestamp++;
	st.push(u);

	for(const int& v : adj[u]) {
		if(in[v] == -1) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if(scc_id[v] == -1)
			low[u] = min(low[u], low[v]);
	}

	if(in[u] != low[u])
		return;

	while(true) {
		int v = st.top();
		st.pop();
		scc_id[v] = scc_timestamp;

		if(u == v)
			break;
	}

	scc_timestamp++;
}

bool is_sink[N];

vector<int> find_graph_base() {
	memset(in, -1, sizeof(int) * n);
	memset(scc_id, -1, sizeof(int) * n);
	timestamp = scc_timestamp = 0;

	for(int i = 0; i < n; ++i) {
		if(in[i] == -1)
			dfs(i);
	}

	fill(is_sink, is_sink + scc_timestamp, true);

	for(int u = 0; u < n; ++u) {
		for(const int& v : adj[u]) {
			if(scc_id[u] != scc_id[v]) {
				is_sink[scc_id[u]] = false;
				break;
			}
		}
	}

	auto rng = views::iota(0, n) | views::filter([](int u) {
		return is_sink[scc_id[u]];
	});

	vector<int> base_graph;

	ranges::copy(rng, back_inserter(base_graph));

	return base_graph;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	while(cin >> n && n && cin >> m) {

		for(int i = 0; i < n; ++i)
			adj[i].clear();
			
		for(int i = 0; i < m; ++i) {
			int u, v;

			cin >> u >> v;

			adj[u - 1].push_back(v - 1);
		}


		auto base_graph = find_graph_base();

		for(int i = 0; i < (int)base_graph.size() - 1; ++i)
			cout << base_graph[i] + 1 << ' ';

		if(!base_graph.empty())
			cout << base_graph.back() + 1;

		cout << '\n';
	}

	return 0;
}