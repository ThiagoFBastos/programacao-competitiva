#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	
	size_t n, q;

	cin >> n >> q;

	ordered_set<int> st;

	ranges::for_each(views::iota(size_t {0}, n), [&st](auto idx) {
		int val;

		cin >> val;

		st.insert(val);
	});

	for(size_t i = 0; i < q; ++i) {
		int t, x;
		
		cin >> t >> x;

		switch(t) {
			case 0:
				st.insert(x);
			break;
			case 1:
				st.erase(x);
			break;
			case 2:
			{
				if(x > (int)st.size())
					cout << "-1\n";
				else
					cout << *st.find_by_order(x - 1) << '\n';
				break;
			}
			case 3:
			{
				cout << st.order_of_key(x + 1) << '\n';
				break;
			}
			case 4:
			{
				auto it = st.upper_bound(x);

				if(it == st.begin())
					cout << "-1\n";
				else
					cout << *prev(it) << '\n';

				break;
			}
			case 5:
			{
				auto it = st.lower_bound(x);

				if(it == st.end())
					cout << "-1\n";
				else
					cout << *it << '\n';
				break;
			}
			default:
				throw exception();
		}
	}

	return 0;
}