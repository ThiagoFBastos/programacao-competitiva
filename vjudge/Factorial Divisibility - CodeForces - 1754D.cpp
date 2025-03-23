#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
   	
	int n, x;

	cin >> n >> x;

	vector<int> frq(x + 1, 0);

	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		if(a < x) ++frq[a];
	}

	for(int i = 1; i < x; ++i) {
		frq[i + 1] += frq[i] / (i + 1);
		frq[i] %= (i + 1);
	}

	frq.back() = 0;

	if(accumulate(frq.begin(), frq.end(), 0)) cout << "No\n";
	else cout << "Yes\n";

    return 0;
}

