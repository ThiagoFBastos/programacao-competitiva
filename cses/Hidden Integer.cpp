#include <bits/stdc++.h>
 
using namespace std;
 
string question() {
	string answer;
	cin >> answer;
	return answer;
}
 
bool ask(int x) {
	cout << "? " << x << '\n';
	cout.flush();
	return question() == "YES";
}
 
void answer(int x) {
	cout << "! " << x << '\n';
	cout.flush();
}
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int lo = 1, hi = 1e9;
 
	while(lo < hi) {
		int mid = (lo + hi) / 2;
 
		if(!ask(mid))
			hi = mid;
		else
			lo = mid + 1;
	}
 
	answer(hi);
 
	return 0;
}
