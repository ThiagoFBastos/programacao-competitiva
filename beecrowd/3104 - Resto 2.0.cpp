#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string a;
    int b;

    cin >> a >> b;

    long long mod {};

    for(char c : a) {
        mod = 10 * mod + c - '0';
        mod %= b;
    }

    cout << mod << '\n';

    return 0;
}