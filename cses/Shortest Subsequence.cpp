#include <bits/stdc++.h>
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string DNA;
	int n;
	vector<int> pos[4];
	cin >> DNA;
	n = DNA.size();
	vector<int> dp(n, 0);
	for(int k = 0; k < n; ++k) {
		if(DNA[k] == 'G') DNA[k] = 'B';
		else if(DNA[k] == 'T') DNA[k] = 'D';
		pos[DNA[k] - 'A'].push_back(k);
	}
	for(int k = n - 1; k >= 0; --k) {
		int minS = n + 1;
		for(int i = 0; i < 4; ++i) {
			auto j = upper_bound(pos[i].begin(), pos[i].end(), k);
			if(j != pos[i].end())
				minS = min(dp[*j], minS);
			else
				minS = 0;
		}
		if(minS == n + 1) dp[k] = 1;
		else dp[k] = minS + 1;
	}
	int ssub = n + 1, i = 0;
	for(int k = 0; k < 4; ++k) {
		if(pos[k].empty()) {
			if(k == 1) cout << "G\n";
			else if(k == 3) cout << "T\n";
			else cout << char(k + 'A') << '\n';
			return 0;
		}
		else if(ssub > dp[pos[k][0]]) {
			i = pos[k][0];
			ssub = dp[i];
		}
	}
	string answer;
	do 
	{
		if(DNA[i] == 'B') answer.push_back('G');
		else if(DNA[i] == 'D') answer.push_back('T');
		else answer.push_back(DNA[i]);
		for(int k = 0; k < 4; ++k) {
			auto j = upper_bound(pos[k].begin(), pos[k].end(), i);
			if(j != pos[k].end() && dp[*j] == ssub - 1) {
				i = *j;
				break;
			}
		}
		--ssub;
	} while(ssub > 0);
	for(int k = 0; k < 4; ++k) {
		if(pos[k].empty() || i >= pos[k].back()) {	
			if(k == 1) answer += 'G';
			else if(k == 3) answer += 'T';
			else answer += 'A' + k;
			break;
		}
	}
	cout << answer<< '\n';
	return 0;
}
