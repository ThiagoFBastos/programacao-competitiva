#include <bits/stdc++.h>

using namespace std;

template <typename T, typename Op>
requires std::regular_invocable<Op, T, T> && std::convertible_to<std::invoke_result_t<Op&, const T&, const T&>, T>
class FenwickTree
{
public:
    FenwickTree(std::size_t n, const Op& op, T initial):
        _ft(n + 1, initial),
        _op(op),
        _initial(initial)
    {

    }

    void update(std::size_t k, T value)
    {
        assert(k >= 1 && k < _ft.size());

        for(int i = k; i < (int)_ft.size(); i += i & -i)
            _ft[i] = _op(_ft[i], value);
    }

    T query(std::size_t k) const
    {
        T answer = _initial;

        assert(k < _ft.size());

        for(int i = k; i > 0; i -= i & -i)
            answer = _op(answer, _ft[i]);

        return answer;
    }
private:
    std::vector<T> _ft;

    Op _op;

    T _initial;
};

template<typename T, typename Op>
auto make_fenwick_tree(std::size_t n, Op&& op, T initial)
{
    return FenwickTree<T, std::decay_t<Op>>(n, std::forward<Op>(op), initial);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int n, q;

	cin >> n >> q;

	auto ft = make_fenwick_tree(n, plus<int>(), 0);

	while(q-- > 0) {
		int t;

		cin >> t;

		if(t == 1) {
			int pos, cnt;

			cin >> pos >> cnt;

			ft.update(pos, cnt);
		} else {
			int l1, r1, l2, r2;

			cin >> l1 >> r1 >> l2 >> r2;

			if(max(l1, l2) <= min(r1, r2))
				cout << ft.query(max(r1, r2)) - ft.query(min(l1, l2) - 1) << '\n';
			else
				cout << ft.query(r1) - ft.query(l1 - 1) + ft.query(r2) - ft.query(l2 - 1) << '\n';
		}
	}

	return 0;
}