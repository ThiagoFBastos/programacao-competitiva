#include <bits/stdc++.h>

using namespace std;

struct point {
	int x, y;
	point() {x = y = 0;}
	point(int _x, int _y) : x {_x}, y {_y} {}
	point operator-(point other) {
		return {x - other.x, y - other.y};
	}
    bool operator<(const point& other) const {
        if(x != other.x) return x < other.x; 
        return y < other.y;
    }
    bool operator==(const point& other) const {
        return x == other.x && y == other.y;
    }
};

int64_t cross(point a, point b) {
	return (int64_t)a.x * b.y - (int64_t)a.y * b.x;
}

bool ccw(point p, point q, point r) {
	return cross(q - p, r - p) >= 0;
}

bool cw(point p, point q, point r) {
	return cross(q - p, r - p) <= 0;
}

vector<point> convexHull(vector<point>& a) {
	int n = a.size();
	vector<point> upper, lower;
	
	auto p = a;
	sort(p.begin(), p.end());
	
	upper.push_back(p[0]);
	lower.push_back(p[0]);
	
	for(int i = 1; i < n; ++i) {
		while((int)upper.size() >= 2) {
			int n = upper.size();
			if(cw(upper[n - 2], upper[n - 1], p[i])) break;
			upper.pop_back();
		}
		
		while((int)lower.size() >= 2) {
			int n = lower.size();
			if(ccw(lower[n - 2], lower[n - 1], p[i])) break;
			lower.pop_back();
		}
		
		upper.push_back(p[i]);
		lower.push_back(p[i]);
	}
	
	for(int k = (int)lower.size() - 2; k > 0; --k) upper.push_back(lower[k]);
	return upper;
}

void solve(int test) {
    int n;

    cin >> n;

    vector<point> p, q;

    for(int i = 1; i <= n; ++i) {
        int x, y;
        cin >> x >> y;
        q.push_back({x, y});
    }

    p = q;

    auto hull = convexHull(p);
    
    sort(hull.begin(), hull.end());

    for(int i = 0; i < n; ++i) {
        if(binary_search(hull.begin(), hull.end(), p[i]))
            cout << i + 1 << ' ';
    }
    
    cout << '\n';
}

int main() {
    int t = 1;
    //cin >> t;
    for(int i = 1; i <= t; ++i) solve(i);
    return 0;
}


