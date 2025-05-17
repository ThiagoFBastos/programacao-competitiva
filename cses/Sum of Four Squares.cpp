#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int N = 1e7 + 5;
 
int squares[N][2];
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	for(int i = 0; i < N; ++i)
		squares[i][0] = squares[i][1] = -1;
 
	for(int a = 0; a * a < N; ++a) {
		for(int b = 0; a * a + b * b < N; ++b) {
			squares[a*a+b*b][0] = a;
			squares[a*a+b*b][1] = b;
		}
}
 
	int t;
 
	cin >> t;
 
	while(t--) {
		int x;
 
		cin >> x;
 
		for(int i = 0; i <= x; ++i) {
			auto X = squares[x - i];
			auto Y = squares[i];
 
			if(X[0] < 0 || Y[0] < 0) continue;
 
			for(int j = 0; j < 2; ++j) cout << X[j] << ' ';
			for(int j = 0; j < 2; ++j) cout << Y[j] << ' ';
			cout << '\n';
 
			break;
		}
	}
 
	return 0;
}
