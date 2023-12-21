#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
 
void read(int& n) {
 
	register int ch = getchar();
 
	while(ch < 48) ch = getchar();
 
	n = 0;
 
	while(ch > 47) {
 
		n = (n << 3) + (n << 1) + ch - 48;
		ch = getchar();
	}
}
 
int main() {
 
	int n;
 
	scanf("%d", &n);
 
	map<int, int> pos;
	vi song(n);
 
	for(int k = 0; k < n; ++k)
		read(song[k]);
 
	int p = 0, mp = 0, j = 0;
 
	for(int k = 1; k <= n; ++k) {
 
		int i = pos[song[k - 1]];
 
		if(i >= j) {
 
			j = i + 1;
			p = k - j + 1;
		}
 
		else
			++p;
 
		mp = max(mp, p);
		pos[song[k - 1]] = k;
	}
 
	printf("%d\n", mp);
 
	return 0;
}
