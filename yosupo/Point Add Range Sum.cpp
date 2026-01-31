#include <bits/stdc++.h>

using namespace std;

template <typename T, typename Op>
requires std::regular_invocable<Op&, const T&, const T&>
&& std::convertible_to<std::invoke_result_t<Op&, const T&, const T&>, T>
&& std::copy_constructible<T>
class SegTree
{
public:

	using value_type = T;

	SegTree(std::size_t n, Op&& op, T identity_value):
		_len(n),
		_op(std::forward<Op>(op)),
		_identity_value(identity_value)
	{
		if(n == 0)
			throw std::invalid_argument("the size must be greater than zero");

		_container.assign(2 * n, identity_value);
	}

	template<typename It, typename Sent>
	SegTree(It begin, Sent sent, Op&& op, T identity_value):
		SegTree(std::ranges::distance(begin, sent), std::forward<Op>(op), identity_value)
	{
		std::copy(begin, sent, _container.begin() + _len);

		for(size_t i = _len - 1; i > 0; --i)
			_container[i] = _op(_container[i << 1], _container[(i << 1) | 1]);
	}

	T query(std::size_t l, std::size_t r) const
	{
		T result_left = _identity_value;
		T result_right = _identity_value;

		if(l > r)
			throw std::invalid_argument("the range is degenerated");
		else if(r >= _len)
			throw std::out_of_range("range out of bounds");

		for(l += _len, r += _len; l <= r; l >>= 1, r >>= 1)
		{
			if(l & 1) result_left = _op(result_left, _container[l++]);
			if(~r & 1) result_right = _op(_container[r--], result_right);
		}

		return _op(result_left, result_right);
	}

	void update(std::size_t k, T value)
	{
		if(k >= _len)
			throw std::out_of_range("index out of bounds");

		k += _len;

		_container[k] = value;

		for(k >>= 1; k; k >>= 1)
			_container[k] = _op(_container[k << 1], _container[(k << 1) | 1]);
	}

	std::size_t size() const noexcept
	{
		return _len;
	}

private:

	std::size_t _len;

	std::vector<T> _container;

	Op _op;

	T _identity_value;
};

template<typename T, typename Op>
auto make_segment_tree(std::size_t n, Op&& op, T identity_value)
{
	return SegTree<T, std::decay_t<Op>>(n, std::forward<Op>(op), identity_value);
}

template<typename T, typename It, typename Sent, typename Op>
auto make_segment_tree(It it, Sent sent, Op&& op, T identity_value)
{
	return SegTree<T, std::decay_t<Op>>(it, sent, std::forward<Op>(op), identity_value);
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	int n, q;

	cin >> n >> q;

	auto values = views::iota(0, n) | views::transform([](auto) {
		long long val;

		cin >> val;

		return val;
	});

	auto st = make_segment_tree(ranges::begin(values), ranges::end(values), plus<>{}, 0ll);

	while(q-- > 0) {
		int t;

		cin >> t;

		if(t == 0) {
			size_t k;
			long long value;

			cin >> k >> value;

			st.update(k, st.query(k, k) + value);
		} else {
			size_t l, r;

			cin >> l >> r;

			auto sum = st.query(l, r - 1);

			cout << sum << '\n';
		}
	}

	return 0;
}