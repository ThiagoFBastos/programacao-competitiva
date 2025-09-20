#include <iostream>
#include <concepts>
#include <algorithm>
#include <vector>
#include <exception>

template<typename T>
struct Node
{
    T sum,
    prefix,
    suffix,
    max_sum;

    Node() = default;

    Node(T value):
        sum {value},
        prefix {value},
        suffix {value},
        max_sum {value}
    {

    }
};

template<typename T>
struct Combinator
{
    Node<T> operator()(Node<T>& left, Node<T>& right)
    {
        Node<T> merged;

        merged.sum = left.sum + right.sum;
        merged.prefix = std::max(left.prefix, left.sum + right.prefix);
        merged.suffix = std::max(left.suffix + right.sum, right.suffix);
        merged.max_sum = std::max({left.max_sum, right.max_sum, left.suffix + right.prefix});

        return merged;
    }
};

template<typename T, typename Fn>
requires ((std::integral<T> || std::floating_point<T>) && std::move_constructible<Node<T>> && std::invocable<Fn, Node<T>&, Node<T>&>)
class SegTree
{
public:

    SegTree(const std::vector<T>& arr):
        _length {arr.size()}        
    {
        _data.resize(4 * _length);

        build(arr, 0, _length - 1);
    }

    T query(std::size_t l, std::size_t r) const
    {
        if(l > r)
            throw std::invalid_argument("o intervalo não corresponde a um segmento");
        else if(r >= _length)
            throw std::out_of_range("o intervalo esta fora dos limites");

        return std::max(T{}, query(l, r, 0, _length - 1).max_sum);
    }

private:
    std::vector<Node<T>> _data;
    std::size_t _length;

    void build(const std::vector<T>& arr, std::size_t lo, std::size_t hi, std::size_t p = 1)
    {
        if(lo == hi)
        {
            _data[p] = Node(arr[lo]);
            return;
        }

        auto mid = (lo + hi) / 2;

        build(arr, lo, mid, 2 * p);
        build(arr, mid + 1, hi, 2 * p + 1);

        _data[p] = Fn()(_data[2 * p], _data[2 * p + 1]);
    }

    auto query(std::size_t l, std::size_t r, std::size_t lo, std::size_t hi, std::size_t p = 1) const
    {
        if(lo >= l && hi <= r)
            return _data[p];

        auto mid = (lo + hi) / 2;

        if(r <= mid)
            return query(l, r, lo, mid, 2 * p);
        else if(l > mid)
            return query(l, r, mid + 1, hi, 2 * p + 1);
        
        auto left = query(l, r, lo, mid, 2 * p);
        auto right = query(l, r, mid + 1, hi, 2 * p + 1);

        return Fn()(left, right);
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::size_t n, m;

    std::cin >> n >> m;

    std::vector<long long> arr(n);

    for(auto& val : arr)
        std::cin >> val;

    SegTree<long long, Combinator<long long>> st(arr);

    for(std::size_t i = 0; i < m; ++i)
    {
        std::size_t l, r;

        std::cin >> l >> r;

        std::cout << st.query(l - 1, r - 1) << std::endl;
    }

    return 0;
}