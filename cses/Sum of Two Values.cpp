#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
 
#define fi first
#define sc second
 
int main() {
 
	int n, x;
 
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
 
	cin >> n >> x;
 
	vii a(n);
 
	for(int k = 0; k < n; ++k) {
 
		cin >> a[k].fi;
		a[k].sc = k + 1;
	}
 
	sort(a.begin(), a.end(), [](ii L, ii R) {return L.fi < R.fi;});
 
	int low = 0, high = n - 1;
	
	while(low < high) {
 
		if(a[low].fi + a[high].fi > x)
			--high;
 
		else if(a[low].fi + a[high].fi < x)
			++low;
 
		else
			break;
	}
 
	if(low >= high)
		cout << "IMPOSSIBLE\n";
	else
		cout << a[low].sc << ' ' << a[high].sc << '\n';	
 
	return 0;
}
