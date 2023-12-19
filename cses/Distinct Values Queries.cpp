#include <bits/stdc++.h>
 
using namespace std;
 
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
 
struct Query {
 
	int a, b, k;
};
 
bool operator<(Query q1, Query q2) {
 
	return q1.a < q2.a || (q1.a == q2.a && q1.b < q2.b);
}
 
static vi preffix, lazy;
static int n;
 
static int query(int node, int k, int low, int high);
static void update(int node, int v, int l, int r, int low, int high);
static void push(int node, int L, int R);
 
int query(int node, int k, int low, int high) {
 
	if(low == high)
		return preffix[k];
 
	int mid = (low + high) >> 1;
 
	push(node, low, high);
	
	if(k <= mid)
		return query((node << 1) + 1, k, low, mid);
 
	return query((node << 1) + 2, k, mid + 1, high);
}
 
void update(int node, int v, int l, int r, int low, int high) {
 
	if(l > r)
		return;
 
	else if(l == low && r == high) {
 
		lazy[node] += v;
 
		if(l == r)
			preffix[l] += v;
	}
 
	else {
 
		int mid = (low + high) >> 1;
 
		push(node, low, high);
 
		update((node << 1) + 1, v, l, min(r, mid), low, mid);
		update((node << 1) + 2, v, max(l, mid + 1), r, mid + 1, high);
	}
}
 
void push(int node, int L, int R) {
 
	if(lazy[node]) {
 
		lazy[(node << 1) + 1] += lazy[node];
		lazy[(node << 1) + 2] += lazy[node];
 
		if(R - L == 1)
			preffix[L] += lazy[node], preffix[R] += lazy[node];
 
		else if(R - L == 2)
			preffix[R] += lazy[node];
 
		lazy[node] = 0;
	}
}
 
int main() {
 
	int q, count = 0;
	map<int, int> hash;
	vi x, h;
	vii sx;
	deque<int> *p;
 
	ios_base :: sync_with_stdio(false);
	cin.tie(nullptr);
 
	cin >> n >> q;
 
	x.resize(n);
	sx.resize(n);
	h.resize(n);
 
	p = new deque<int>[n];
 
	for(int k = 0; k < n; ++k) {
 
		cin >> x[k];
		sx[k] = make_pair(x[k], k);
	}
 
	sort(sx.begin(), sx.end());
 
	h[sx[0].second] = hash[sx[0].first] = count++;
 
	p[0].push_back(sx[0].second);
 
	for(int k = 1; k < n; ++k) {
 
		if(sx[k].first > sx[k - 1].first)
			h[sx[k].second] = hash[sx[k].first] = count++;
 
		else
			h[sx[k].second] = h[sx[k - 1].second];
 
		p[h[sx[k].second]].push_back(sx[k].second);
	}
 
	preffix.resize(n);
	lazy.assign((1 << (int)ceil(log2(n)) + 1) - 1, 0);
 
	preffix[0] = 1;
 
	for(int k = 1; k < n; ++k) {
 
		int H = h[k];
 
		if(p[H][0] == k)
			preffix[k] = 1 + preffix[k - 1];
 
		else
			preffix[k] = preffix[k - 1];
	}
 
	vector<Query> queries(q);
	vi answers(q);
 
	for(int k = 0; k < q; ++k) {
 
		cin >> queries[k].a >> queries[k].b;
 
		--queries[k].a;
		--queries[k].b;
 
		queries[k].k = k;
	}
 
	sort(queries.begin(), queries.end());
 
	for(int k = 0, j = 0; k < n && j < q; ++k) {
 
		while(j < q && queries[j].a == k) {
 
			answers[queries[j].k] = query(0, queries[j].b, 0, n - 1);
			++j;
		}
 
		int H = h[k];
 
		p[H].pop_front();
 
		if(!p[H].empty())
			update(0, 1, p[H][0], n - 1, 0, n - 1);
		
		update(0, -1, k + 1, n - 1, 0, n - 1);
	}
 
	for(int ans : answers)
		cout << ans << '\n';
 
	return 0;
}
