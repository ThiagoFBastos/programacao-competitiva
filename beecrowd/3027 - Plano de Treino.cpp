#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;

    cin >> n >> k;

    auto grams_view = views::iota(0, n) | views::transform([](auto) {
        int grams;
        cin >> grams;
        return grams;
    });

    vector<int> grams, costs;
    priority_queue<int, vector<int>, greater<int>> pq;
    int received;
    long long cost {};

    ranges::copy(grams_view, back_inserter(grams));

    cin >> received;

    auto costs_view = views::iota(0, n) | views::transform([](auto) {
        int cost;
        cin >> cost;
        return cost;
    });

    ranges::copy(costs_view, back_inserter(costs));

    for(int i = 0; i < n; ++i) {
        pq.push(costs[i]);

        while(k < grams[i] && !pq.empty()) {
            int c = pq.top();
            pq.pop();

            k += received;
            cost += c;
        }

        if(k < grams[i]) {
            cout << "-1\n";
            return 0;
        }
    }

    cout << cost << '\n';

    return 0;
}