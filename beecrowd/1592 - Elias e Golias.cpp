#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1e3 + 5;

using edge = pair<int, int>;
using pq_type = tuple<int, int, int>;

vector<edge> adj[N];
optional<int> cost[N][N];

struct cmp {

	bool operator()(const pq_type& lhs, const pq_type& rhs) const {
		return get<2>(lhs) > get<2>(rhs);
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;

	cin >> t;

	while(t-- > 0) {
		int n, m, k;

		cin >> n >> m >> k;

		for(int i = 0; i < n; ++i) {
			adj[i].clear();

			for(int j = 1; j <= k; ++j)
				cost[i][j] = {};
		}

		for(int i = 0; i < m; ++i) {
			int a, b, c;

			cin >> a >> b >> c;

			adj[a].emplace_back(b, c);
		}

		priority_queue<pq_type, vector<pq_type>, cmp> pq;
		optional<int> answer;

		pq.emplace(0, 1, 0);

		while(!pq.empty()) {
			auto [u, cities, cst] = pq.top();

			pq.pop();

			if(cost[u][cities])
				continue;

			cost[u][cities] = cst;

			if(u == n - 1) {
				answer = cst;
				break;
			} else if(cities == k)
				continue;

			for(const auto& [v, w] : adj[u]) {
				if(!cost[v][cities + 1])
					pq.emplace(v, cities + 1, cst + w);
			}
		}

		if(answer)
			cout << *answer << '\n';
		else
			cout << "-1\n";
	}

	return 0;
}