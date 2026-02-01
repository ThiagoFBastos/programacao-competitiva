#include <bits/stdc++.h>

using namespace std;

template<typename T>
requires std::copy_constructible<T>
class SegTreeTraits
{
public:

    using value_type = T;

    static constexpr value_type neutral()
    {
        return {};
    }

    static value_type merge(const T& lhs, const T& rhs)
    {
        return lhs + rhs;
    }
};

template <typename Traits>
class SegTree
{
public:

	using value_type = typename Traits::value_type;

	SegTree(std::size_t n):
		_len(n)
	{
		if(n == 0)
			throw std::invalid_argument("the size must be greater than zero");

		_container.assign(2 * n, Traits::neutral());
	}

	template<std::ranges::range R>
	SegTree(R&& r):
		SegTree(std::ranges::distance(r))
	{
		std::copy(std::ranges::begin(r), std::ranges::end(r), _container.begin() + _len);

		for(size_t i = _len - 1; i > 0; --i)
			_container[i] = Traits::merge(_container[i << 1], _container[(i << 1) | 1]);
	}

	value_type query(std::size_t l, std::size_t r) const
	{
		value_type result_left = Traits::neutral();
		value_type result_right = Traits::neutral();

		if(l > r)
			throw std::invalid_argument("the range is degenerated");
		else if(r >= _len)
			throw std::out_of_range("range out of bounds");

		for(l += _len, r += _len; l <= r; l >>= 1, r >>= 1)
		{
			if(l & 1) result_left = Traits::merge(result_left, _container[l++]);
			if(~r & 1) result_right = Traits::merge(_container[r--], result_right);
		}

		return Traits::merge(result_left, result_right);
	}

	void update(std::size_t k, value_type value)
	{
		if(k >= _len)
			throw std::out_of_range("index out of bounds");

		k += _len;

		_container[k] = value;

		for(k >>= 1; k; k >>= 1)
			_container[k] = Traits::merge(_container[k << 1], _container[(k << 1) | 1]);
	}

	std::size_t size() const noexcept
	{
		return _len;
	}

private:

	std::size_t _len;

	std::vector<value_type> _container;
};

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	int n, q;

	cin >> n >> q;

	auto values = views::iota(0, n) | views::transform([](auto) {
		long long val;

		cin >> val;

		return val;
	}) | ranges::to<vector<long long>>();

    using Traits = SegTreeTraits<long long>;
	SegTree<Traits> st(values);

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