#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;

    cin >> n;

    auto to_lowercase = [](const auto& s) {
        string t;
        transform(s.begin(), s.end(), back_inserter(t), [](char c) { return tolower(c);});
        return t;
    };

    vector<pair<string, string>> words(n);

    for(auto& [a, b] : words) {
        cin >> b;
        a = to_lowercase(b);
    }

    sort(words.begin(), words.end());

    for(const auto& [a, b] : words)
        cout << b << '\n';

    return 0;
}