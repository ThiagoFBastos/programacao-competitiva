#include "bits/stdc++.h"

using namespace std;

void solve() {
	int n;
	
	cin >> n;
	
	vector<int> pontos(n + 1, 0), gols(n + 1, 0), vice(n + 1, 0), tms(n + 1, -1);
	
	for(int k = 0; ; ++k) {
		int m;
		
		cin >> m;
		
		if(!m) break;
		
		vector<int> id;
		
		for(int i = 0; i < m; ++i) {
			int t[2], p[2];
			for(int j = 0; j < 2; ++j) {
				cin >> t[j] >> p[j];
				if(tms[t[j]] != k) {
					tms[t[j]] = k;
					pontos[t[j]] = gols[t[j]] = 0;
					id.push_back(t[j]);
				}
			}
			
			gols[t[0]] += p[0];
			gols[t[1]] += p[1];
			
			if(p[0] == p[1]) ++pontos[t[0]], ++pontos[t[1]];
			else if(p[0] > p[1]) pontos[t[0]] += 3;
			else pontos[t[1]] += 3;
		}
		
		auto a = make_tuple(-1, -1, -1);
		auto b = make_tuple(-1, -1, -1);
		
		for(int ID : id) {
			auto c = make_tuple(pontos[ID], gols[ID], -ID);
			if(c > a) b = a, a = c;
			else if(c > b) b = c;
		}
		
		++vice[-get<2>(b)];
	}
	
	int max_vice = *max_element(vice.begin(), vice.end());
	
	cout << (vice[1] == max_vice ? "Y\n" : "N\n");
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}