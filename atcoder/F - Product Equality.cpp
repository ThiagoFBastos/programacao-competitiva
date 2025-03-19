#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace Numeric {
    constexpr __int128 MOD = 195604000610178961;

    class BigInt {
        private:

        std::string data;
        __int128 cachedMod = -1;

        public:

        BigInt() = default;
        BigInt(std::string data): data {data} {}

        __int128 value() {
            if(cachedMod != -1)
                return cachedMod;

            __int128 h {};

            for(char digit : data)
                h = (10 * h + digit - '0') % MOD;

            cachedMod = h;
            return h;
        }

        __int128 operator*(BigInt& other) {
            return value() * other.value() % MOD;
        }

        friend std::ostream& operator<<(std::ostream& os, const BigInt& big);
        friend std::istream& operator>>(std::istream& is, BigInt& big);
    };

    std::ostream& operator<<(std::ostream& os, const BigInt& big) {
        os << big.data;
        return os;
    }

    std::istream& operator>>(std::istream& is, BigInt& big) {
        is >> big.data;
        big.cachedMod = -1;
        return is;
    }
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::map<__int128, int> mp;

    int n, triples {};

    std::cin >> n;

    std::vector<Numeric::BigInt> nums(n);

    for(auto& big : nums) {
        std::cin >> big;
        ++mp[big.value()];
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            auto it = mp.find(nums[i] * nums[j]);
            if(it != mp.end())
                triples += it->second;
        }
    }

    std::cout << triples << '\n';

    return 0;
}