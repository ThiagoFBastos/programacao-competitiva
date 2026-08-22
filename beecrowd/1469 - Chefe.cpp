#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	int n, m, q;

	auto query = [](const auto& adj, const auto& ages, int target) -> optional<int> {
		constexpr int INF = numeric_limits<int>::max();
		const int n = static_cast<int>(adj.size());

		vector<int> min_age(n, INF);
		queue<int> q;
		int answer = INF;

		q.push(target);

		while(!q.empty()) {
			int u = q.front();

			q.pop();

			answer = min(answer, min_age[u]);

			for(int v : adj[u]) {
				if(min_age[v] == INF) {
					min_age[v] = min(min_age[u], ages[v]);
					q.push(v);
				}
			}
		}

		if(answer == INF)
			return nullopt;

		return make_optional<int>(answer);
	};

	while(cin >> n >> m >> q) {

		vector<int> ages(n), where(n);
		vector<vector<int>> adj(n);

		for(int i = 0; i < n; ++i) {
			cin >> ages[i];
			where[i] = i;
		}

		for(int i = 0; i < m; ++i) {
			int u, v;
			cin >> u >> v;
			adj[v - 1].push_back(u - 1);
		}

		while(q-- > 0) {
			char cmd;

			cin >> cmd;

			if(cmd == 'T') {
				int u, v;
				cin >> u >> v;

				--u, --v;

				swap(ages[where[u]], ages[where[v]]);
				swap(where[u], where[v]);

			} else {
				int target;
				cin >> target;

				if(auto age = query(adj, ages, where[target - 1]))
					cout << *age << '\n';
				else
					cout << "*\n";
			}
		}
	}

	return 0;
}