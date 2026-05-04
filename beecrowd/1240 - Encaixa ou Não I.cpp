#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    size_t tc;

    cin >> tc;

    auto endswith = [](const auto& s, const auto& t) {
        const auto n = s.size();
        const auto m = t.size();

        if(n > m)
            return false;

        return s == t.substr(m - n);
    };

    ranges::for_each(views::iota(size_t {}, tc), [endswith](auto) {
        int a, b;

        cin >> a >> b;

        auto s = to_string(a);
        auto t = to_string(b);

        if(endswith(t, s))
            cout << "encaixa\n";
        else
            cout << "nao encaixa\n";
    });

    return 0;
}