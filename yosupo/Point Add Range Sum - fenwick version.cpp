#include <bits/stdc++.h>

using namespace std;

template <typename T, typename Op>
requires std::regular_invocable<Op&, const T&, const T&> 
&& std::convertible_to<std::invoke_result_t<Op&, const T&, const T&>, T>
class FenwickTree
{
public:
    /**
     * @brief Initialize the fenwick tree data structure
     * @param n the number of elements
     * @param op the binary operator that calculates the result
     * @param identity_value the neutral value
     */
    FenwickTree(std::size_t n, Op&& op, T identity_value):
        _ft(n + 1, identity_value),
        _op(std::forward<Op>(op)),
        _identity_value(identity_value)
    {

    }

    /**
     * @brief Update the fenwick tree data structure
     * @param k the index of a element in the fenwick data structure
     * @param value the value that will be applied to the element
     */
    void update(std::size_t k, T value)
    {
        if(k < 1 || k >= _ft.size())
			throw std::out_of_range("interval out of bounds");

        for(int i = k; i < (int)_ft.size(); i += i & -i)
            _ft[i] = _op(_ft[i], value);
    }

    /**
     * @brief Find the result of an operation of first k elements
     * @param k the number of the first elements for which we want to find the result
     */
    T query(std::size_t k) const
    {
        T answer = _identity_value;

        if(k >= _ft.size())
			throw std::out_of_range("index out of bounds");

        for(int i = k; i > 0; i -= i & -i)
            answer = _op(answer, _ft[i]);

        return answer;
    }
private:
    /* The fenwick tree data structure */
    std::vector<T> _ft;

    /* The binary operator that calculates the answer */
    Op _op;

    /* The neutral value */
    T _identity_value;
};

/**
  * @brief Factory of the FenwickTree
  * @param n the number of elements
  * @param op the binary operator that calculates the result
  * @param identity_value the neutral value
  * @return The FenwickTree data structure
 */
template<typename T, typename Op>
auto make_fenwick_tree(std::size_t n, Op&& op, T identity_value)
{
    return FenwickTree<T, std::decay_t<Op>>(n, std::forward<Op>(op), identity_value);
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	int n, q;

	cin >> n >> q;

	auto ft = make_fenwick_tree(n, plus<> {}, 0LL);

	for(int i = 1; i <= n; ++i) {
		long long val;

		cin >> val;

		ft.update(i, val);
	}

	while(q-- > 0) {
		int t;

		cin >> t;

		if(t == 0) {
			size_t k;
			long long value;

			cin >> k >> value;

			ft.update(k + 1, value);
		} else {
			size_t l, r;

			cin >> l >> r;

			auto sum = ft.query(r) - ft.query(l);

			cout << sum << '\n';
		}
	}

	return 0;
}