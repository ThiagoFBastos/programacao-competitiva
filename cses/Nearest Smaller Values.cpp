#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
 
int main() {
 
	int n;
 
	scanf("%d", &n);
 
	vi x(n), pos(n);
 
	for(int k = 0; k < n; ++k)
		scanf("%d", &x[k]);
	
	stack<int> Q;
 
	for(int k = 0; k < n; ++k) {
 
		while(!Q.empty() && x[k] <= x[Q.top()])			
			Q.pop();
		
		if(Q.empty())
			pos[k] = -1;
 
		else
			pos[k] = Q.top();
 
		Q.push(k);
	}
 
	for(int k = 0; k < n - 1; ++k)
		printf("%d ", pos[k] + 1);
 
	printf("%d\n", pos.back() + 1);
 
	return 0;
}
