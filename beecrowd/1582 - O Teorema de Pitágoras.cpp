#include <bits/stdc++.h>

using namespace std;

string tripleType(int a, int b, int c) {
    vector<int> sides {a, b, c};

    sort(sides.begin(), sides.end());

    if(sides[0] * sides[0] + sides[1] * sides[1] == sides[2] * sides[2]) {
        int g = gcd(sides[0], gcd(sides[1], sides[2]));
        return g == 1 ? "tripla pitagorica primitiva" : "tripla pitagorica";
    }

    return "tripla";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    for(int a, b, c; cin >> a >> b >> c; )
        cout << tripleType(a, b, c) << '\n';   

    return 0;
}