#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

    using prescription = pair<string, int>;
    using pq_type = pair<int, int>;

    int t;

    cin >> t;

    while(t-- > 0) {
        int n, k;

        cin >> n >> k;

        vector<prescription> prescriptions(n);
        priority_queue<pq_type, vector<pq_type>, greater<pq_type>> pq;

        for(int i = 0; i < n; ++i) {
            string medicine;
            int frequency;

            cin >> medicine >> frequency;
            prescriptions[i] = {medicine, frequency};

            pq.emplace(frequency, i);
        }

        for(int i = 0; i < k; ++i) {
            int timestamp, priority;

            tie(timestamp, priority) = pq.top();

            pq.pop();

            cout << timestamp << ' ' << prescriptions[priority].first << '\n';

            pq.emplace(timestamp + prescriptions[priority].second, priority);
        }
    }

	return 0;
}
 