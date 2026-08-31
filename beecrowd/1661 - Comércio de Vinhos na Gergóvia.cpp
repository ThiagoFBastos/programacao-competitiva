#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    
    while(cin >> n && n != 0) {

        vector<int> quantity(n);

        for(int& value : quantity)
            cin >> value;

        stack<int> buy, sell;
        int64_t steps {}, to_buy_quantity {}, to_sell_quantity {};

        ranges::for_each(quantity, [&](int q) {
            steps += to_buy_quantity + to_sell_quantity;

            if(q > 0) {
                while(!sell.empty()) {
                    int cnt = sell.top();
                    int remainder = cnt - q;
                    
                    sell.pop();

                    to_sell_quantity -= cnt;
                    q -= cnt;

                    if(remainder > 0) {
                        sell.push(remainder);
                        to_sell_quantity += remainder;
                        break;
                    }
                }

                if(q > 0) {
                    buy.push(q);
                    to_buy_quantity += q;
                }
            } else if(q < 0) {
                q *= -1;

                while(!buy.empty()) {
                    int cnt = buy.top();
                    int remainder = cnt - q;

                    buy.pop();

                    to_buy_quantity -= cnt;
                    q -= cnt;

                    if(remainder > 0) {
                        buy.push(remainder);
                        to_buy_quantity += remainder;
                        break;
                    }
                }

                if(q > 0) {
                    sell.push(q);
                    to_sell_quantity += q;
                }
            }
        });

        cout << steps << '\n';
    }

    return 0;
}