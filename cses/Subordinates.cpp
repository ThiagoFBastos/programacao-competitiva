#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
#define f first
#define s second
 
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
 
vector<vi> D;
vi sub;
 
void dfs(int v) {
 
	sub[v] = 1;
 
	for(int w : D[v]) {
 
		if(sub[w] == -1)
			dfs(w);
 
		sub[v] += sub[w];
	}
}
 
int main() {
 
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
 
	int n;
 
	cin >> n;
 
	D.resize(n);
	sub.assign(n, -1);
 
	for(int k = 1; k < n; ++k) {
 
		int boss;
 
		cin >> boss;
 
		D[boss - 1].push_back(k);		
	}
 
	for(int v = 0; v < n; ++v) {
 
		if(sub[v] == -1)
			dfs(v);
	}
 
	for(int count : sub)
		cout << count - 1 << ' ';
 
	cout << '\n';
 
	return 0;
}
