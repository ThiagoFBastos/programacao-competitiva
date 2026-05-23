#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;

    while(cin >> n) {
        auto view = views::iota(0, n) | views::transform([](auto) {
            int deg;
            cin >> deg;
            return deg;
        });

        vector<int> deg;

        ranges::copy(view, back_inserter(deg));

        sort(deg.rbegin(), deg.rend());

        vector<long long> pre(n + 1, 0);
        priority_queue<int> pq;
        long long right_sum = 0, cnt {};

        for(int i = 1; i <= n; ++i)
            pre[i] = pre[i - 1] + deg[i - 1];

        bool possible = pre[n] % 2 == 0;

        for(int i : views::iota(1, n + 1) | views::reverse) {
            while(!pq.empty() && pq.top() >= static_cast<int>(i)) {
                auto val = pq.top();
                pq.pop();
                right_sum -= val;
                ++cnt;
            }

            possible = possible && pre[i] <= i * (i - 1ll) + right_sum + cnt * i;
            
            pq.push(deg[i - 1]);
            right_sum += deg[i - 1];
        }

        cout << (possible ? "possivel\n" : "impossivel\n");
    }

    return 0;
}