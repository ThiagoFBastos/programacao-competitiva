#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base :: sync_with_stdio(false); 
    cin.tie(0);
    cout.tie(0);
    long long n;
    while(cin >> n) {
        long long l = 2, r = 9;
        int t = 1;
        while(r < n) {
            l = r + 1;
            r *= t ? 2 : 9;
            t ^= 1;
        }
        cout << (t ? "Stan" : "Ollie") << " wins.\n";
    }
    return 0;
}