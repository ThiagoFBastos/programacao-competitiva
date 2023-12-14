#include <bits/stdc++.h>
 
using namespace std;
 
using ii = pair<int, int>;
 
vector<int> find_subset(int l, int u, vector<int> w) {
	int n = w.size();
 
	vector<ii> a(n);
	vector<int> ans;
	long long L = 0, R = 0;
 
	for(int i = 0; i < n; ++i) a[i] = {w[i], i};
  
	sort(a.begin(), a.end());
	
	for(int i = 1; i <= n; ++i) {
		L += a[i - 1].first;
		R += a[n - i].first;
		if(L <= l && R >= l || l <= L && L <= u) {
			priority_queue<ii, vector<ii>, greater<ii>> A;
			priority_queue<ii> B;
			long long lo = L;
			for(int k = 0; k < i; ++k) A.emplace(a[k]);
			for(int k = i; k < n; ++k) B.emplace(a[k]);
			while(lo < l) {
				auto p = A.top();
				auto q = B.top();
				A.pop();
				B.pop();
				lo += q.first - p.first;
				B.emplace(p);
				A.emplace(q);
			}
			while(!A.empty()) {
				ans.push_back(A.top().second);
				A.pop();
			}
			break;
		}
	}
	
	return ans;	
}
