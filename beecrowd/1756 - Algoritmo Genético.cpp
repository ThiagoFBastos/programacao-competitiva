#include <bits/stdc++.h>

using namespace std;

using ld = long double;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;

    cin >> t;

    auto p_different = [](const string& a, const string& b, ld p) {
        ld  result = 0.0L;
        const auto n = a.size();

        for(size_t i = 0; i < (1 << n) - 1; ++i) {
            ld probability = 1.0L;

            for(size_t j = 0; j < n; ++j) {
                if((i >> j) & 1) probability *= a[j] == b[j] ? 1 - p : p;
                else probability *= a[j] == b[j] ? p : 1 - p;
            }

            result += probability;
        }

        return result;
    };

    while(t-- > 0) {
        int bits, corte;
        ld p;
        string indv1, indv2, indv3;

        cin >> bits >> corte >> p;
        cin >> indv1 >> indv2 >> indv3;

        auto comb_indv1 = indv1.substr(0, corte) + indv2.substr(corte);
        auto comb_indv2 = indv2.substr(0, corte) + indv1.substr(corte);

        auto comb_indv1_diff = p_different(comb_indv1, indv3, p);
        auto comb_indv2_diff = p_different(comb_indv2, indv3, p);

        auto resposta = 1.0L - comb_indv1_diff * comb_indv2_diff;

        cout << fixed << setprecision(7) << resposta << '\n';
    }

    return 0;
}