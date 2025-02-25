#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

template<class coord>
struct Hungarian {

	static const int MAXN = 64;
	coord INF = 1e9;

	bool zero(coord x) {
		return abs(x) < 1e-9;
	}

	int N, matchl[MAXN], matchr[MAXN];
	coord cst[MAXN][MAXN];

	Hungarian(int n, int m) {
		N = max(n, m);

		for(int i = 0; i < N; ++i)
		for(int j = 0; j < N; ++j)
			cst[i][j] = i < n && j < m ? INF : 0;
	}		

	void add(int x, int y, coord c) {
		cst[x][y] = c;
	}

	coord matching() {
		int mat = 0, dad[MAXN], vis[MAXN];
		coord ds[MAXN], y[MAXN], z[MAXN];

		for(int i = 0; i < N; ++i)
			y[i] = *min_element(cst[i], cst[i] + N);

		for(int j = 0; j < N; ++j) {
			z[j] = cst[0][j] - y[0];
			for(int i = 1; i < N; ++i)
				z[j] = min(z[j], cst[i][j] - y[i]);
		}

		memset(matchl, -1, sizeof matchl);
		memset(matchr, -1, sizeof matchr);

		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				if(matchr[j] == -1 && zero(cst[i][j] - y[i] - z[j])) {
					matchl[i] = j;
					matchr[j] = i;
					++mat;
					break;
				}
			}
		}

		while(mat < N) {
			int s = 0, j = 0, i;

			while(matchl[s] != -1) ++s;

			memset(dad, -1, sizeof dad);
			memset(vis, 0, sizeof vis);

	    	for(int k = 0; k < N; ++k)
	    		ds[k] = cst[s][k] - y[s] - z[k];
	    
	    	while(true) {
	        	j = -1;

	        	for(int k = 0; k < N; ++k)
	        		if(!vis[k] && (j == -1 || ds[k] < ds[j]))
	        			j = k;
	        
	        	vis[j] = 1; 
	       		i = matchr[j];

	        	if(i == -1) 
	        		break;

	        	for(int k = 0; k < N; ++k)
		        	if(!vis[k]) {
				        auto new_ds = ds[j] + cst[i][k] - y[i] - z[k];
				        if(ds[k] > new_ds) {
				        	ds[k] = new_ds;
				        	dad[k] = j;
				        }
		        	}
	    	}

	   		for(int k = 0; k < N; ++k)
		    	if(k != j && vis[k]) {
					auto w = ds[k] - ds[j];
					z[k] += w;
					y[matchr[k]] -= w;
		    	}
	  
	  		y[s] += ds[j];
	  
	   	 	while(dad[j] >= 0) {
				int d = dad[j]; 
				matchr[j] = matchr[d]; 
				matchl[matchr[j]] = j; 
				j = d;
	    	}

			matchr[j] = s; 
			matchl[s] = j;
			mat++;
		}
	
		coord value = 0;
		for(int i = 0; i < N; ++i)
			value += cst[i][matchl[i]];

		return value;
	}
};

void solve() {
	
	int n;

	cin >> n;
	
	if(!n) exit(0);

	vector<int> c1(n), c2(n);
	Hungarian<int> h(n, n);

	for(int& v : c1) cin >> v;
	for(int& v : c2) cin >> v;

	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			h.add(i, j, abs(i - j) + abs(c1[i] - c2[j]));

	cout << h.matching() << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	//int t = 1;
	//cin >> t;
	while(1) solve();
	return 0;
}
