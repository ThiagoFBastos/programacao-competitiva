#include <bits/stdc++.h>

using namespace std;

bool erdos_gallai(std::vector<int> degrees)
{
    const auto n = degrees.size();

    std::sort(degrees.rbegin(), degrees.rend());

    std::stack<int> st;
    long long left_sum = accumulate(degrees.begin(), degrees.end(), 0ll);
    long long right_sum {}, cnt {};

    bool is_possible = left_sum % 2 == 0;

    for(std::size_t i = n; i > 0; --i)
    {
        if(!is_possible)
            break;

        while(!st.empty() && st.top() >= static_cast<int>(i))
        {
            auto val = st.top();
            st.pop();
            right_sum -= val;
            ++cnt;
        }

        is_possible = is_possible && left_sum <= static_cast<long long>(i) * static_cast<long long>(i - 1) + right_sum + cnt * static_cast<long long>(i);
        
        st.push(degrees[i - 1]);
        left_sum -= degrees[i - 1];
        right_sum += degrees[i - 1];
    }

    return is_possible;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;

    while(cin >> n) {
        vector<int> degrees;

        auto input = views::iota(size_t {}, n) | views::transform([](auto) { int deg; cin >> deg; return deg; });

        ranges::copy(input, back_inserter(degrees));

        if(erdos_gallai(move(degrees)))
            cout << "possivel\n";
        else
            cout << "impossivel\n";
    }

    return 0;
}