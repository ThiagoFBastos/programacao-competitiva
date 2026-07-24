#include <bits/stdc++.h>

using namespace std;

inline long long counting_bits(long long n)
{
    long long ones {}, remainder {1}, pow {1};

    for(int i {}; n > 0; ++i)
    {
        ones += (n & 1) * (remainder + (pow >> 1) * i);
        remainder += (n & 1) * pow;
        pow <<= 1;
        n >>= 1;
    }

    return ones;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long lo, hi;

    while(cin >> lo >> hi)
        cout << counting_bits(hi) - counting_bits(lo - 1) << '\n';
        
    return 0;
}