#include "bits/stdc++.h"

using namespace std;
 
#define INF   1000000000
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

auto max_pairs(int a[], int b[], int& pairs, int p, int q) {
	int A[10], B[10];
	vector<tuple<int, int, int>> couple;
	memcpy(A, a, sizeof(int) * 10);
	memcpy(B, b, sizeof(int) * 10);	
	pairs = 1;
	for(int i = 9; i >= 0; --i) {
		for(int j = 9 - i; j <= 9; ++j) {
			int d = min(A[i], B[j]);
			if(!d) continue;
			A[i] -= d;
			B[j] -= d;
			pairs += d;
			couple.pb({i, j, d});
		}
	}	
	sort(all(couple), [](auto& x, auto& y) {
		return min(get<0>(x),get<1>(x)) < min(get<0>(y),get<1>(y));
	});
	couple.pb({p, q, 1});
	for(int i = 1; i <= 9; ++i) {
		for(int j = 1; j <= 9; ++j) {
			int d = min(A[i], B[j]);
			if(!d) continue;
			couple.pb({i, j, d});
			A[i] -= d, B[j] -= d;
		}
	}
	for(int i = 1; i <= 9; ++i) {
		if(A[i]) couple.insert(couple.begin(), {i, 0, A[i]});
		if(B[i]) couple.insert(couple.begin(), {0, i, B[i]});
	}
	return couple;
}

void solve() {
	string a, b;
	cin >> a >> b;
	int A[10] = {0}, B[10] = {0}, sum = 0, ans = 0;
	vector<tuple<int, int, int>> couple;
	int d = abs((int)a.size() - (int)b.size());
	if(a.size() < b.size()) a = string(d, '0') + a;
	else if(a.size() > b.size()) b = string(d, '0') + b;
	for(char c : a) {
		++A[c - '0'];
		sum += c - '0';
	}
	for(int i = 0; i < (int)b.size(); ++i) {
		++B[b[i] - '0'];
		sum += b[i] - '0';
		couple.pb({a[i]-'0', b[i]-'0', 1});
	}
	ans = sum;
	for(int p = 1; p <= 9; ++p) {
		for(int q = 10 - p; q <= 9; ++q) {
			if(!A[p] || !B[q]) continue;
			--A[p], --B[q];
			int pairs;
			auto c = max_pairs(A, B, pairs, p, q);
			if(sum - 9 * pairs < ans) {
				swap(c, couple);
				ans = sum - 9 * pairs;
			}
			++A[p], ++B[q];
		}
	}
	a = b = "";
	for(auto [p, q, d] : couple) {
		if(p != 0) a += string(d, p + '0');
		if(q != 0) b += string(d, q + '0');
	}
	cout << a << '\n' << b << '\n';
}
	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  //cin >> t;
	while(t--) solve();
	return 0;
}
