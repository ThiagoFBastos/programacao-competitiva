#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int N = 1e3 + 10;
 
int permutation[N], n;
 
string question() {
	string answer;
	cin >> answer;
	return answer;
}
 
bool ask(int i, int j) {
	cout << "? " << i << ' ' << j << '\n';
	cout.flush();
	return question() == "YES";
}
 
void merge(int l, int r) {
	int tmp[N], mid = (l + r) / 2, i = l, j = mid + 1, k = 0;
 
	while(i <= mid && j <= r) {
		if(ask(permutation[i], permutation[j]))
			tmp[k++] = permutation[i++];
		else
			tmp[k++] = permutation[j++];
	}
 
	while(i <= mid) tmp[k++] = permutation[i++];
	while(j <= r) tmp[k++] = permutation[j++];
	for(int i = l; i <= r; ++i) permutation[i] = tmp[i - l];
}
 
void merge_sort(int l, int r) {
	if(l == r) return;
 
	int mid = (l + r) / 2;
 
	merge_sort(l, mid);
	merge_sort(mid + 1, r);
	merge(l, r);
}
 
void answer() {
	int pos[N];
 
	for(int i = 0; i < n; ++i)
		pos[permutation[i]] = i + 1;
 
	cout << "!";
	for(int i = 1; i <= n; ++i)
		cout << ' ' << pos[i];
	cout << '\n';
	cout.flush();
}
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	cin >> n;
 
	iota(permutation, permutation + n, 1);
	merge_sort(0, n - 1);
	answer();
 
	return 0;
}
