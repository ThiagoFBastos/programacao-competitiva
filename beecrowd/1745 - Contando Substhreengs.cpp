#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

    string str;
    array<long long, 3> cnt {};
    int sum {};
    long long answer {};

    cin >> str;

    cnt[0] = 1;

    for(char digit : str) {
        if(!isdigit(digit)) {
            sum = 0;
            fill(cnt.begin(), cnt.end(), 0);
            cnt[0] = 1;
            continue;
        }

        int d = digit - '0';

        sum = (sum + d) % 3;
        answer += cnt[sum]++;
    }

    cout << answer << '\n';

	return 0;
}
 