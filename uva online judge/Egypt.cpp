#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	
    int a, b, c;

    while(cin >> a >> b >> c) {

        if(a == 0 && b == 0 && c == 0)
            break;

        vector<int> sides {a, b, c};

        sort(sides.begin(), sides.end());

        if(sides[0] * sides[0] + sides[1] * sides[1] == sides[2] * sides[2])
            cout << "right\n";
        else
            cout << "wrong\n";
    }

	return 0;
}