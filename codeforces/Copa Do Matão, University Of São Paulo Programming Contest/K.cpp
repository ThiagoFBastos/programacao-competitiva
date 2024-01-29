#include "bits/stdc++.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < n; i++)
 
using ll = long long;
using ii = pair<int, int>;
using ull = unsigned long long;
using vi = vector<int>;

const string ENDL = "\n";

void solve()
{
	int n, k;
    cin >> n >> k;

    vi p(n);
    vi c(n);

    forn(i, n)
        cin >> p[i];
    
    forn(i, n)
    {
        cin >> c[i];
    }

    vi days(n);
    forn(i, n)
    {
        days[i] = (p[i]+c[i]) % k;
    }
    sort(days.begin(), days.end());

    forn(i, n)
    {
        if (days[i] >= n)
        {
            cout << "N\n";
            return;
        }
    }

    forn(i, n-1)
    {
        if (days[i] == days[i+1])
        {
            cout << "N\n";
            return;
        }
    }
    cout << "S\n";
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	// cin >> t;
	while(t--) solve();
 	return 0;
}
