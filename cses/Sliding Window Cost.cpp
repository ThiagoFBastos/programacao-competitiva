#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
#define f first
#define s second
#define ri register int
typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
#define MAXN 200000
template<class T>
class Fenwick {
	T ft[MAXN + 1];
	int n;
	public:
		Fenwick(int n) {
			this->n = n;
			memset(ft, 0, sizeof(T) * (n + 1));
		}
		T query(int r) {
			T ans {};
			while(r > 0) {
				ans += ft[r];
				r -= r & -r;
			}
			return ans;
		}
		void update(int k, T v) {
			while(k <= n) {
				ft[k] += v;
				k += k & -k;
			}
		}
};
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, k, a[MAXN], h[MAXN], pos[MAXN], m;
	cin >> n >> k;
	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		h[i] = a[i];
	}
	sort(h, h + n);
	m = unique(h, h + n) - h;
	for(int i = 0; i < n; ++i) pos[i] = lower_bound(h, h + m, a[i]) - h;
	Fenwick<int> f1(m);
	Fenwick<ll> f2(m);
	for(int i = 0; i < k - 1; ++i) {
		f1.update(pos[i] + 1, 1);
		f2.update(pos[i] + 1, a[i]);
	}
	int middle = (k + 1) / 2;
	for(int i = k - 1; i < n; ++i) {
		int low = 1, high = m;
		f1.update(pos[i] + 1, 1);
		f2.update(pos[i] + 1, a[i]);
		while(low < high) {
			int mid = (low + high) >> 1;
			if(f1.query(mid) >= middle) high = mid;
			else low = mid + 1;
		}
		int n1 = f1.query(high - 1);
		int n2 = f1.query(m) - n1;
		cout << 1LL * (n1 - n2) * h[high - 1] - 2LL * f2.query(high - 1) + 1LL * f2.query(m) << ' ';
		f1.update(pos[i - k + 1] + 1, -1);
		f2.update(pos[i - k + 1] + 1, -a[i - k + 1]);
	}
	cout << '\n';
	return 0;
}
