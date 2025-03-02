#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <bitset>
#include <numeric>
#include <cmath>
#include <cstdlib>
#include <random>
#include <chrono>

using namespace std;

struct Point {
	int x;
	int y;
};

Point subVector(Point A, Point B) {
	return {B.x - A.x, B.y - A.y};
}

long long crossVector(Point A, Point B) {
	return 1LL * A.x * B.y - 1LL * A.y * B.x;
}

bool collinear(Point A, Point B, Point C) {
	return crossVector(subVector(A, B), subVector(A, C)) == 0;
}

int maxPointsLine(vector<Point>& points, Point A, Point B) {
	int ans = 0;
	for(Point C: points) {
		if(collinear(A, B, C))
			++ans;
	}
	return ans;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(nullptr);
	
	mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
	
	int t;
	
	cin >> t;
	
	for(int i = 1; i <= t; ++i) {
		int n;
		
		cin >> n;
		
		vector<Point> point(n);
		
		for(auto& p : point)
			cin >> p.x >> p.y;
		
		int lineSize = 0;
		
		if(n <= 100) {
			for(int i = 0; i < n; ++i)
				for(int j = i + 1; j < n; ++j)
					lineSize = max(lineSize, maxPointsLine(point, point[i], point[j]));
		} else {
			uniform_int_distribution<int> uid(0, n - 1);
			
			for(int i = 0; i < 15; ) {
				int k = uid(rng);
				int j = uid(rng);
				
				if(k == j) continue;
				
				lineSize = max(lineSize, maxPointsLine(point, point[k], point[j]));
				
				++i;
			}
		}
		
		cout << "Case #" << i << ": " << n - lineSize << '\n';
	}
}