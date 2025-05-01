#include "bits/stdc++.h"
using namespace std;
void solve() {
	int x;
	string s;
	cin >> x >> s;
	if(x == 0) {
		cout << "0\n";
		return;
	}
	int a = 0, b = 0;
	stack<char> fila;
	for(int i = size(s) - 1; i >= 0; --i) fila.push(s[i]);
	while(!fila.empty() && abs(a - b) <= x) {
		char u, v;	
		if(size(fila) >= 2) {
			u = fila.top(); fila.pop();
			v = fila.top(); fila.pop();
			if(u != v) {
				if(a == b) ++a, ++b;
				else if(a < b) ++a, fila.push('M');
				else ++b, fila.push('W');
			} 
			else if(u == 'W') ++a, fila.push('W');
			else ++b, fila.push('M');
		} 
		else if(fila.top() == 'W') ++a, fila.pop();
		else ++b, fila.pop();
	}
	if(abs(a - b) > x) --a;
	cout << a + b << '\n';
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}