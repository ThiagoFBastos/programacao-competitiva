#include "tickets.h"
#include <vector>
#include <algorithm>
#include <tuple>
 
long long find_maximum(int k, std::vector<std::vector<int>> x) {
	int n = x.size();
	int m = x[0].size();
	long long prize = 0;
 
	auto answer = std :: vector<std :: vector<int>>(n, std :: vector<int>(m, -1));
	auto type = std :: vector<std :: vector<int>>(n, std :: vector<int>(m, 0));
	std :: vector<std :: vector<int>> sum(n), sub(n);
 
	std :: vector<std :: tuple<int, int, int>> a;
 
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < k; ++j) a.emplace_back(x[i][m - k + j] + x[i][j], i, j);
		for(int j = m - k; j < m; ++j) {
			type[i][j] = 1;
			prize += x[i][j];
		}
	}
 
	std :: sort(a.begin(), a.end());
 
	for(int i = 0; i < n * k / 2; ++i) {
		auto [v, x, y] = a[i];
		prize -= v;
		type[x][y + m - k] = 0; 
		type[x][y] = -1;
	}
 
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(type[i][j] == -1) sub[i].push_back(j);
			else if(type[i][j] == 1) sum[i].push_back(j);
		}
	}
 
	while(--k >= 0) {
		int L = 0, R = 0;
		for(int i = 0; i < n; ++i) {
			if(!sum[i].empty() && !sub[i].empty()) continue;
			else if(!sum[i].empty()) {
				++R;
				answer[i][sum[i].back()] = k;
				sum[i].pop_back();
			} else {
				++L;
				answer[i][sub[i].back()] = k;
				sub[i].pop_back();
			}
		}
		for(int i = 0; i < n; ++i) {
			if(sum[i].empty() || sub[i].empty()) continue;
			if(L < n / 2) {
				++L;
				answer[i][sub[i].back()] = k;
				sub[i].pop_back();
			} else {
				++R;
				answer[i][sum[i].back()] = k;
				sum[i].pop_back();
			}
		}
	}
 
	allocate_tickets(answer);
 
	return prize;
}
