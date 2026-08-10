#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;


int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
 
	int a, b;
	vi op(20001, -1);
	queue<int> Q;

	cin >> a >> b;

	op[a] = 0;
	Q.push(a);

	while(!Q.empty()) {

		a = Q.front();

		if(a == b) 
			break;

		Q.pop();

		if(a > 1 && op[a - 1] == -1) {

			op[a - 1] = 1 + op[a];
			Q.push(a - 1);
		}

		if(a < b && op[2 * a] == -1) {

			op[2 * a] = 1 + op[a];
			Q.push(2 * a);
		}
	}
	
	cout << op[b] << '\n';

	return 0;
}
