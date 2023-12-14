#include <bits/stdc++.h>
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int q;
	string s;
	set<int> pos;
	multiset<int> S;
	cin >> s >> q;
	pos.insert(0);
	for(int i = 1; i < s.size(); ++i) {
		if(s[i] != s[i - 1]) {
			S.insert(i - *pos.rbegin());
			pos.insert(i);
		}
	}
	S.insert((int)s.size() - *pos.rbegin());
	pos.insert((int)s.size());
	while(q--) {
		int k;
		set<int> :: iterator low, high;
		cin >> k;
		--k;
		low = pos.lower_bound(k);
		if(*low > k) low = prev(low);
		high = pos.upper_bound(k);
		S.erase(S.find(*high - *low));
		if(k) {
			if(s[k] != s[k - 1]) {
				auto low = pos.lower_bound(k - 1);
				if(*low > k - 1) low = prev(low);
				S.erase(S.find(k - *low));
				pos.erase(k);
			}
			else {
				S.insert(k - *low);
				pos.insert(k);
			}
		}
		if(k + 1 < s.size() && s[k] != s[k + 1]) {
			S.erase(S.find(*pos.upper_bound(k + 1) - k - 1));
			pos.erase(k + 1);
		}
		else if(s[k] == s[k + 1]) {
			S.insert(*pos.upper_bound(k + 1) - k - 1);
			pos.insert(k + 1);
		}
		low = pos.lower_bound(k);
		if(*low > k) low = prev(low);
		high = pos.upper_bound(k);
		S.insert(*high - *low);
		cout << *S.rbegin() << ' ';
		s[k] ^= 1;
	}
	cout << '\n';
	return 0;
}
