#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
#define f first
#define s second
#define EPS 1e-9
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned ui;
using vi = vector<int>;
using vvi = vector<vi>;
using ii = pair<int, int>;
using vii = vector<ii>;
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	int n, d;
	while(true) {
		cin >> n >> d;
		if(!(n || d)) break;
		deque<char> S;
		string num, ans;
		cin >> num;
		for(int k = 0; k <= d; ++k) {
			while(!S.empty() && S.back() < num[k]) S.pop_back();
			S.push_back(num[k]);
		}
		for(int k = d + 1; k < n; ++k) {
			ans += S[0];
			S.pop_front();
			while(!S.empty() && S.back() < num[k]) S.pop_back();
			S.push_back(num[k]);
		}
		ans += S[0];
		cout << ans << '\n';
	}
    return 0;
}