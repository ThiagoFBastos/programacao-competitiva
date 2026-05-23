#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

using cd = complex<double>;
const double PI = acos(-1);

inline int lg(int x) {
	return x ? 31 - __builtin_clz(x) : 0;
}

inline void fft(vector<cd>& a, bool invert) { 	
	const int n = static_cast<int>(a.size());

	for(int i = 1, j = 0; i < n; ++i) {
		int bit = n >> 1;	
		for(; j & bit; bit >>= 1) j -= bit;
		j += bit;
		if(i < j) swap(a[i], a[j]);
	}

    for(int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
		int mid = len >> 1;
        for(int i = 0; i < n; i += len) {
            cd w(1);
            for(int j = 0; j < mid; ++j) {
                cd u = a[i + j], v = a[i + j + mid] * w;
                a[i + j] = u + v;
                a[i + j + mid] = u - v;
                w *= wlen;
            }
        }
    }

    if(invert) for(int i = 0; i < n; ++i) a[i] /= n;
}

inline vector<i64> multiply2(vector<int>& a) {

	vector<cd> fa(a.begin(), a.end());
    
    int n = 2 << lg(2 * a.size());

	fa.resize(n);

    fft(fa, false);

    for(int i = 0; i < n; ++i) fa[i] *= fa[i];

    fft(fa, true);

	vector<i64> result(n);
    for(int i = 0; i < n; ++i) result[i] = round(fa[i].real());

	return result;
}

void solve() {
	int n;

	cin >> n;

	vector<int> P(n, 0), R(n, 0);

	for(int i = 1; i < n; ++i) {
		int X = (i64)i * i % n;
		++P[X];
		++R[2 * X % n];
	}
	
	auto Q = multiply2(P);
	i64 A = 0, B = 0;

	for(int i = 1; i < n; ++i) {
		int X = (i64)i * i % n;
		A += Q[X] + Q[X + n];
		B += R[X];
	}

	cout << (A - B) / 2 + B << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}