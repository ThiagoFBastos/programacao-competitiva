#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using ii = pair<int, int>;
using vii = vector<ii>;
int main() {
	ios_base :: sync_with_stdio(false); 
	cin.tie(0);
	cout.tie(0);
	int n, k, caso = 0;
	string nomes[100];
	while(true) {
		cin >> n >> k;
		if(!(n || k)) break;
		for(int i = 0; i < n; ++i) cin >> nomes[i];
		cout << "Instancia " << ++caso << '\n';
		for(int i = 0; i < n - 1 && k > 0; ++i) {
			int j = i + 1, h = i;
			while(j < n && j - i <= k) {
				if(nomes[j] < nomes[h]) h = j;
				++j;
			}
			if(h > i) {
				string aux = nomes[h];
				k -= h - i;
				for(int j = h - 1; j >= i; --j) nomes[j + 1] = nomes[j];
				nomes[i] = aux;
			}
		}
		for(int i = 0; i < n; ++i) cout << nomes[i] << ' ';
		cout << "\n\n";
	}
	return 0;
}