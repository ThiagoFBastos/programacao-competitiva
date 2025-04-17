#include <bits/stdc++.h>

using namespace std;

#define FOR(k, a, b) for(int k = (a); k <= (b); ++k)
#define REP(k, a, b) for(int k = (a); k >= (b); --k)

#define all(x) x.begin(), x.end()
#define up(x, y) upper_bound(all(x), y)
#define lower(x, y) lower_bound(all(x), y)
#define INF 0x3ffffff
#define fi first
#define sc second

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;

typedef unsigned long long ull;
typedef long long ll;

int main() {

	int n;
	long double EDF = 0;
	
	cin >> n;
	
	while(n--) {
	
		int c, p;
		
		cin >> c >> p;
		
		EDF += c / (long double)p;
	}
	
	if(EDF <= 1.0L)
		puts("OK");
	else
		puts("FAIL");
	
	return 0;
}