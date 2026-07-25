#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5, K = 4;

int dist[N][K];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t t;
    char store[] = {'C', 'F'};

    cin >> t;

    for(size_t i = 0; i < t; ++i) {
        string avenue;
        queue<pair<int, int>> q;

        cin >> avenue;

        int n = avenue.size();

        for(int i = 0; i < n; ++i)
            for(int j = 0; j < K; ++j)
                dist[i][j] = -1;

        for(int i = 0; i < n; ++i) {
            if(avenue[i] == 'R') {
                dist[i][0] = 0;
                q.emplace(i, 0);
            }
        }

        optional<int> min_dist;

        while(!q.empty()) {
            auto [x, mask] = q.front();

            q.pop();

            if(mask == 3) {
                min_dist = dist[x][mask];
                break;
            }

            for(int delta : {-1, 1}) {
                int dest = x + delta;
                
                if(dest < 0 || dest >= n)
                    continue;

                int new_mask = mask;

                for(int i = 0; i < 2; ++i) {
                    if(avenue[dest] == store[i])
                        new_mask |= 1 << i;
                }

                if(dist[dest][new_mask] != -1)
                    continue;

                dist[dest][new_mask] = 1 + dist[x][mask];
                q.emplace(dest, new_mask);
            }
        }

        assert(static_cast<bool>(min_dist));
        cout << *min_dist << '\n';
    }

    return 0;
}