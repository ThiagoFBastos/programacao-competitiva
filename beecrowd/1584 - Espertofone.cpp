#include <bits/stdc++.h>

using namespace std;

template<int MOD>
class mod_matrix {
public:

	mod_matrix() = delete;
	mod_matrix(size_t r, size_t c)
		: _rows(r)
		, _columns(c)
		, _container(r, vector<int>(c, 0))
	{

	}

	size_t rows() const { return _rows; }
	size_t columns() const { return _columns; }
	int& at(size_t i, size_t j) { return _container[i][j]; }

	mod_matrix operator*(mod_matrix& rhs) {
		assert(columns() == rhs.rows());
		mod_matrix<MOD> result(rows(), rhs.columns());

		for(size_t i = 0; i < rows(); ++i)
			for(size_t j = 0; j < rhs.columns(); ++j)
				for(size_t k = 0; k < columns(); ++k)
					result.at(i, j) = (result.at(i, j) + static_cast<long long>(at(i, k)) * rhs.at(k, j)) % MOD;

		return result;
	}

	static mod_matrix identity(size_t rows, size_t columns) {
		mod_matrix<MOD> result(rows, columns);

		for(size_t i = 0; i < rows; ++i)
			for(size_t j = 0; j < columns; ++j)
				result.at(i, j) = static_cast<int>(i == j);

		return result;
	}

	mod_matrix pow(long long k) {
		auto answer = mod_matrix<MOD>::identity(rows(), columns());
		auto mat = *this;

		for(; k > 0; k >>= 1) {
			if(k & 1)
				answer = answer * mat;

			mat = mat * mat;
		}

		return answer;
	}

private:

	size_t _rows;
	size_t _columns;
	vector<vector<int>> _container;
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	constexpr int MOD = 1e9 + 7;

	size_t n;
	long long k;


	while(cin >> n >> k) {
		mod_matrix<MOD> rec(n * n, n * n);

		for(size_t x0 = 0; x0 < n; ++x0) {
			for(size_t y0 = 0; y0 < n; ++y0) {
				for(size_t x1 = 0; x1 < n; ++x1) {
					for(size_t y1 = 0; y1 < n; ++y1) {
						if(make_pair(x0, y0) == make_pair(x1, y1))
							continue;

						int dx = abs(static_cast<int>(x0) - static_cast<int>(x1));
						int dy = abs(static_cast<int>(y0) - static_cast<int>(y1));

						if(gcd(dx, dy) == 1)
							rec.at(x0 * n + y0, x1 * n + y1) = 1;
					}
				}
			}
		}

		auto transformed = rec.pow(k);

		long long answer {};

		for(size_t i = 0; i < transformed.rows(); ++i)
			for(size_t j = 0; j < transformed.columns(); ++j)
				answer = (answer + transformed.at(i, j)) % MOD;

		cout << answer << '\n';
	}

	return 0;
}