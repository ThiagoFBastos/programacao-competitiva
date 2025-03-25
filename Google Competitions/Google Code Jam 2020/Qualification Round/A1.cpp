#include <bits/stdc++.h>
using namespace std;
int main() {
    int a[100][100], t;
    bitset<101> rows, cols;
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> t;
    for(int i = 1; i <= t; ++i) {
        int n, trace {}, r = 0, c = 0;
        cin >> n;
        for(int k = 0; k < n; ++k)
            for(int i = 0; i < n; ++i)
                cin >> a[k][i];
        for(int k = 0; k < n; ++k) trace += a[k][k];
        for(int k = 0; k < n; ++k) {
            rows.reset();
            for(int i = 0; i < n; ++i) {
                if(rows[a[k][i]]) {
                    ++r;
                    break;
                }
                rows[a[k][i]] = 1;
            }
        }
        for(int k = 0; k < n; ++k) {
            cols.reset();
            for(int i = 0; i < n; ++i) {
                if(cols[a[i][k]]) {
                    ++c;
                    break;
                }
                cols[a[i][k]] = 1;
            }
        }
        cout << "Case #" << i << ": " << trace << ' ' << r << ' ' << c << '\n';
    }
    return 0;
}