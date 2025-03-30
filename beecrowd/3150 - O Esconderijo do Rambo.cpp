#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

int n, m;
vector<int> deg;

void solve() {
	cin >> n >> m;
	deg.assign(n,0);
	for(int i=0;i<m;++i){
		int u,v;
		cin>>u>>v;
		++deg[u]; ++deg[v];
	}
	for(int i=0;i<n;++i){
		if(deg[i]%2){
			cout<<"Rambo esta perdido\n";
			return;
		}
	}
	cout<<"Rambo esta salvo\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}