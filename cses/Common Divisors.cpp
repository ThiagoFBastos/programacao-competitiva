#pragma optimize("O3")
#pragma target("sse,sse2")
#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
#define MAXN 1000000
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	vi gcd(MAXN + 1), ct(MAXN + 1, 0);
	cin >> n;
	int N = 0;
	for(int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		++ct[x];
		N = max(N, x);
	}
	for(int i = 2; i <= N; ++i) {
		gcd[i] = 0;
		for(int k = i; k <= N; k += i)
			gcd[i] += ct[k];
	}
	int ans = N;
	while(ans > 1 && gcd[ans] < 2) --ans;
	cout << ans << '\n';
    return 0;
}
