#include <bits/stdc++.h>
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
 
using cd = complex<double>;
const double PI = acos(-1);
 
int lg(int x) {
	return x ? 31 - __builtin_clz(x) : 0;
}
 
void fft(vector<cd>& a, bool invert) { 	
	int n = a.size();
 
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
 
void multiply(vector<int>& result, vector<int>& a, vector<int>& b) {
 
	vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    
    int n = 2 << lg(a.size() + b.size());
 
	fa.resize(n);
	fb.resize(n);
 
    fft(fa, false);
	fft(fb, false);
 
    for(int i = 0; i < n; ++i) fa[i] *= fb[i];
 
    fft(fa, true);
 
	result.resize(n);
    for(int i = 0; i < n; ++i) result[i] = (int)round(fa[i].real());
}
 
void solve() {
	int n, m;
	cin >> n >> m;
	vector<int> P(n), Q(m), R;
	for(int& v : P) cin >> v;
	for(int& v : Q) cin >> v;
	reverse(Q.begin(), Q.end());
	multiply(R, P, Q);
	for(int i = 0; i < n + m - 1; ++i) cout << R[i] << ' ';
	cout << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
