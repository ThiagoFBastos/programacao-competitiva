#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
//#pragma GCC target ("sse,sse2,sse3,sse4,avx,avx2")
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define MAXN 8
char t[MAXN][MAXN + 1];
bitset<MAXN> l;
bitset<15> dr, dl;
int ct = 0;
void backtrack(int y) {
	if(y == 8)
		++ct;
	else {
		for(int x = 0; x < 8; ++x) {
			if(t[x][y] == '.' && l[x] == 0 && dl[x + y] == 0 && dr[7 - y + x] == 0) {
				l[x] = dl[x + y] = dr[7 - y + x] = 1;
				backtrack(y + 1);
				l[x] = dl[x + y] = dr[7 - y + x] = 0;	
			}
		}
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	for(int i = 0; i < 8; ++i) cin >> t[i];
	backtrack(0);
	cout << ct << '\n';
	return 0;
} 
