#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 1e3 + 10;

double P[N];
int tcase;

void solve() {
	int a, b, n;

	cin >> a; cin.ignore(); cin >> b;
	cin >> n;

	for(int i = 0; i <= n; ++i) P[i] = 0;

	P[0] = 1;

	double p = 1;

	for(int i = 1; i <= n; ++i) {
		for(int j = n - 1; j >= 0; --j) {
			P[j + 1] += (1.0 * a / b) * P[j];
			P[j] *= (b - a + 0.0) / b;
		}
		for(int j = 0; j <= n; ++j) if(j * b > i * a) P[j] = 0;
	}

	for(int i = 0; i <= n; ++i) p -= P[i];
		
	cout << "Case #" << ++tcase << ": " << (int)floor(1 / (1 - p)) << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
 	cin >> t;
    while(t--) solve();
    return 0;
}

