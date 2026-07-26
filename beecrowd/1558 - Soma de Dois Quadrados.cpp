#include <bits/stdc++.h>

using namespace std;

constexpr int N = 10000 + 5;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

    unordered_set<int> square_sums;

    for(int i = 0; i * i < N; ++i)
        for(int j = 0; i * i + j * j < N; ++j)
            square_sums.insert(i * i + j * j);

    for(int n; cin >> n; )
        cout << (square_sums.count(n) ? "YES\n" : "NO\n");

	return 0;
}
 