#include <bits/stdc++.h>
 
using namespace std;
 
using vi = vector<int>;
 
using query = tuple<char, int, int>;
 
class Fenwick {
 
	vi ft;
	int n;
 
	public:
 
	Fenwick(int n) {
 
		ft.assign(n + 1, 0);
		this->n = n;
	}
 
	int query(int r) {
 
		int ans {};
 
		while(r > 0) {
 
			ans += ft[r];
			r -= r & -r;
		}
 
		return ans;
	}
 
	void update(int k, int v) {
 
		while(k <= n) {
 
			ft[k] += v;
			k += k & -k;
		}
	}
};
 
int main() {
 
	int n, q;
 
	scanf("%d%d", &n, &q);
	
	vi salary(n), numbers, pos(n);
	
	for(int k = 0; k < n; ++k) {
 
		scanf("%d", &salary[k]);
		numbers.push_back(salary[k]);
	}
 
	vector<query> queries(q);
 
	for(int k = 0; k < q; ++k) {
 
		scanf(" %c%d%d", &get<0>(queries[k]), &get<1>(queries[k]), &get<2>(queries[k]));
 
		if(get<0>(queries[k]) == '!')
			numbers.push_back(get<2>(queries[k]));	
	}
 
	sort(numbers.begin(), numbers.end());
	vector<int> :: iterator it = unique(numbers.begin(), numbers.end());
	numbers.resize(distance(numbers.begin(), it));
	
	Fenwick ft(numbers.size());
 
	for(int k = 0; k < n; ++k) {
	
		pos[k] = 1 + lower_bound(numbers.begin(), numbers.end(), salary[k]) - numbers.begin();
		ft.update(pos[k], 1);
	}
	
	for(auto [type, k, x] : queries) {
 
		if(type == '!') {
 
			--k;
 
			ft.update(pos[k], -1);
			pos[k] = 1 + lower_bound(numbers.begin(), numbers.end(), x) - numbers.begin();
			ft.update(pos[k], 1);
		}
 
		else {
 
			int a = lower_bound(numbers.begin(), numbers.end(), k) - numbers.begin();
			int b = lower_bound(numbers.begin(), numbers.end(), x) - numbers.begin();
			
			if(numbers[b] > x) 
				--b;
 
			printf("%d\n", ft.query(b + 1) - ft.query(a));
		}
	}
	
	return 0;
}
