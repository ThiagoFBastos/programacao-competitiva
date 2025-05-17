#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
 
using namespace std;
using namespace __gnu_pbds;
 
template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;
 
enum EventType {
	VALUE,
	LEFT,
	RIGHT
};
 
struct Event {
	EventType type;
	int value;
	int position;
 
	Event() = default;
 
	Event(EventType type, int value, int position): type {type}, value {value}, position {position} {} 
 
	bool operator<(Event other) {
		if(value != other.value)
			return value < other.value;
		return (int)type < (int)other.type;
	}
};
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int n, q;
	vector<Event> event;
	ordered_set<int> st;
 
	cin >> n >> q;
 
	vector<pair<int, int>> interval(q);
	vector<int> answer(q, 0);
 
	event.reserve(n + 2 * q);
 
	for(int i = 0; i < n; ++i) {
		int x;
 
		cin >> x;
 
		event.emplace_back(VALUE, x, i);
	}
 
	for(int i = 0; i < q; ++i) {
		int l, r, c, d;
 
		cin >> l >> r >> c >> d;
 
		interval[i] = {l - 1, r - 1};
		event.emplace_back(LEFT, c - 1, i);
		event.emplace_back(RIGHT, d, i);
	}
 
	sort(event.begin(), event.end());
 
	auto query = [&st](int l, int r) {
		return (int)st.order_of_key(r + 1) - (int)st.order_of_key(l);
	};
 
	for(auto [type, value, position] : event) {
		if(type == VALUE)
			st.insert(position);
		else if(type == LEFT) {
			auto [l, r] = interval[position];
			answer[position] -= query(l, r);
		} else {
			auto [l, r] = interval[position];
			answer[position] += query(l, r);
		}
	}
 
	for(int ans : answer) cout << ans << '\n';
 
	return 0;
}