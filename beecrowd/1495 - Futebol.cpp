#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

    int n, g;

    constexpr int N = 1e2 + 5;

    while(cin >> n >> g) {
        int wins {};
        array<int, N> needed {};

        for(int i = 0; i < n; ++i) {
            int s, r;

            cin >> s >> r;

            if(s > r) ++wins;
            else ++needed[r - s];
        }

        int max_points = 3 * wins;
        int goals = 0;
        
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < needed[i]; ++j) {
                if(goals + i + 1 <= g) {
                    max_points += 3;
                    goals += i + 1;
                } else if(goals + i <= g) {
                    ++max_points;
                    goals += i;
                } else if(i == 0) {
                    ++max_points;
                } else {
                    break;
                }
            }
        }

        cout << max_points << '\n';
    }

	return 0;
}
 