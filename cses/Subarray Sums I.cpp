#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
 
int main() {
 
	int n, t;
 
	scanf("%d%d", &n, &t);
 
	vi x(n + 1);
 
	for(int k = 0; k < n; ++k)
		scanf("%d", &x[k]);
 
	queue<int> Q;
	ll S = 0;
	int count = 0;
 
	for(int k = 0; k < n; ++k) {
 
		S += x[k];
		Q.push(x[k]);		
 
		while(!Q.empty() && S > t) {
		 
			S -= Q.front();
			Q.pop();
		}
 
		if(S == t) 
			++count;
	}
 
	cout << count << '\n';
 
	return 0;
}
