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
using i128 = __int128;

i64 exp(i64 n, int p, int m) {
	i64 ans = 1;
	n %= m;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = ans * n % m;
		n = n * n % m;
	}
	return ans;
}

template<int m>
struct modInt {
	int val;
	
	modInt() {val = 0;}
	modInt(int val) : val {val} {}
	
	modInt operator^(i64 p) {
		return {int(exp(val, p, m))};
	}
	
	modInt& operator^=(int p) {
		val = exp(val, p, m);
		return *this;
	}

	modInt operator+(modInt x) {
		int ans = val + x.val;
		if(ans >= m) ans -= m;
		return {ans};
	}
	
	modInt operator-(modInt x) {
		int ans = val - x.val;
		if(ans < 0) ans += m;
		return {ans};
	}
	
	modInt& operator+=(modInt x) {
		val += x.val;
		if(val >= m) val -= m;
		return *this;
	}
	
	modInt& operator-=(modInt x) {
		val -= x.val;
		if(val < 0) val += m;
		return *this;
	}
	
	modInt operator*(modInt x) {
		return {int(((i64)val * x.val % m + m) % m)};
	}

	modInt& operator*=(modInt x) {
		val = ((i64)val * x.val % m + m) % m;
		return *this;
	}
	
	modInt operator/(modInt x) {
		return {int((val * exp(x.val, m - 2, m) % m + m) % m)};
	}
	
	modInt& operator/=(modInt x) {
		val = (val * exp(x.val, m - 2, m) % m + m) % m;
		return *this;
	}
	
	modInt operator+(i64 x) {
		x = (x % m + m) % m;
		int ans = val + x;
		if(ans >= m) ans -= m;
		return {ans};
	}
	
	modInt operator-(i64 x) {
		x = (x % m + m) % m;
		int ans = val - x;
		if(ans < 0) ans += m;
		return {ans};
	}
	
	modInt& operator+=(i64 x) {
		x = (x % m + m) % m;
		val += x;
		if(val >= m) val -= m;
		return *this;
	}
	
	modInt& operator-=(i64 x) {
		x = (x % m + m) % m;
		val -= x;
		if(val < 0) val += m;
		return *this;
	}
	
	modInt operator*(i64 x) {
		x = (x % m + m) % m;
		return {int((i64)val * x % m)};
	}
	
	modInt& operator*=(i64 x) {
		x = (x % m + m) % m;
		val = (i64)val * x % m;
		return *this;
	}
	
	modInt operator/(i64 x) {
		return {int(val * exp(x, m - 2, m) % m)};
	}
	
	modInt& operator/=(i64 x) {
		val = val * exp(x, m - 2, m) % m;
		return *this;
	}

	bool operator==(modInt other) {
		return val == other.val;
	}

	bool operator!=(modInt other) {
		return val != other.val;
	}
};

template<int m>
ostream& operator<<(ostream& os, modInt<m> v) {
	os << v.val;
	return os;
}

template<int m>
istream& operator>>(istream& is, modInt<m>& v) {
	is >> v.val;
	return is;
}

const int N = 110, K = 11, MOD = 1e9 + 7;

using modint = modInt<MOD>;

modint dp[2][N][N][K], nck[N][N];

modint countAnagrams(string& s) {
	int n = s.size();
	int frq[10] = {0};

	for(char c : s) ++frq[c - '0'];

	for(int i = 0; i <= n; ++i)
		for(int j = 0; i + j <= n; ++j)
			for(int m = 0; m < 11; ++m)
				dp[0][i][j][m] = 0;

	dp[0][(n+1)/2][n/2][0] = 1;

	for(int d = 0; d <= 9; ++d) {
		if(!frq[d]) continue;

		for(int i = 0; i <= n; ++i) {
			for(int j = 0; i + j <= n; ++j) {
				for(int m = 0; m < 11; ++m) {
					dp[1][i][j][m] = dp[0][i][j][m];
					dp[0][i][j][m] = 0;
				}
			}
		}

		for(int i = 0; i <= n; ++i) {
			for(int j = 0; i + j <= n; ++j) {
				for(int m = 0; m < 11; ++m) {
					for(int ev = 0; ev <= frq[d]; ++ev) {
						int od = frq[d] - ev;
						int ad = (ev - od + 1111) * d;
						if(i < ev || j < od) continue;
						dp[0][i - ev][j - od][(m + ad) % 11] += nck[i][ev] * nck[j][od] * dp[1][i][j][m];
					}
				}
			}
		}
	}

	return dp[0][0][0][0];
}

void solve() {
	string s;

	cin >> s;

	for(int i = 0; i <= (int)s.size(); ++i) {
		nck[i][0] = nck[i][i] = 1;
		for(int j = 1; j < i; ++j)
			nck[i][j] = nck[i - 1][j] + nck[i - 1][j - 1];
	}

	modint ans = countAnagrams(s);
	
	size_t pos = s.find('0');
	
	if(pos != string :: npos) {
		s.erase(pos, 1);
		ans -= countAnagrams(s);
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}