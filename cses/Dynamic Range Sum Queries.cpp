#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
using vi = vector<int>;
using vll = vector<ll>;
 
class Fenwick {
 
	vll ft;
	int n;
 
	public:
 
	Fenwick(int n) {
 
		ft.assign(n + 1, 0);
		this->n = n;
	}
 
	long long query(int r) {
 
		long long ans {};
 
		while(r > 0) {
 
			ans += ft[r];
			r -= r & -r;
		}
 
		return ans;
	}
 
	void update(int k, int x) {
 
		while(k <= n) {
 
			ft[k] += x;
			k += k & -k;
		}
	}
};
 
int main() {
 
	int n, q;
 
	ios_base :: sync_with_stdio(false);
	cin.tie(nullptr);
 
	cin >> n >> q;
 
	vi x(n);
	Fenwick ft(n);
 
	for(int k = 0; k < n; ++k) {
 
		cin >> x[k];
		ft.update(k + 1, x[k]);		
	}
 
	while(q--) {
 
		int type, a, b;
 
		cin >> type >> a >> b;
 
		if(type == 1) {
 
			--a;
			ft.update(a + 1, b - x[a]);
			x[a] = b; 
		}
 
		else
			cout << ft.query(b) - ft.query(a - 1) << '\n';
	}
 
	return 0;
}
