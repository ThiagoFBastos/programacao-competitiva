#include <bits/stdc++.h>

using namespace std;

using sudoku = array<array<int, 9>, 9>;

bool is_valid_row_sudoku(const sudoku& matrix) {
    for(size_t i = 0; i < 9; ++i) {
        array<int, 9> cnt {};

        for(size_t j = 0; j < 9; ++j) {
            auto number = matrix[i][j];

            if(number <= 0 || number > 9)
                return false;

            ++cnt[number - 1];
        }

        if(!ranges::all_of(cnt, [](int v) { return v == 1;}))
            return false;
    }

    return true;
}

bool is_valid_column_sudoku(const sudoku& matrix) {
    for(size_t j = 0; j < 9; ++j) {
        array<int, 9> cnt {};

        for(size_t i = 0; i < 9; ++i) {
            auto number = matrix[i][j];

            if(number <= 0 || number > 9)
                return false;

            ++cnt[number - 1];
        }

        if(!ranges::all_of(cnt, [](int v) { return v == 1;}))
            return false;
    }

    return true;
}

bool is_valid_subgrid_sudoku(const sudoku& matrix) {
    for(size_t dx = 0; dx < 3; ++dx) {
        for(size_t dy = 0; dy < 3; ++dy) {
            array<int, 9> cnt {};

            for(size_t i = 0; i < 3; ++i) {
                for(size_t j = 0; j < 3; ++j) {
                    auto number = matrix[3 * dx + i][3 * dy + j];

                    if(number <= 0 || number > 9)
                        return false;

                    ++cnt[number - 1];
                }
            }

            if(!ranges::all_of(cnt, [](int v) { return v == 1;}))
                return false;
        }
    }

    return true;
}

bool is_valid_sudoku(const sudoku& matrix) {
    return is_valid_row_sudoku(matrix) &&
    is_valid_column_sudoku(matrix) &&
    is_valid_subgrid_sudoku(matrix);
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

    size_t t;

    cin >> t;

    ranges::for_each(views::iota(size_t {1}, t + 1), [](auto test) {
        sudoku matrix;

        for(size_t i = 0; i < 9; ++i)
            for(size_t j = 0; j < 9; ++j)
                cin >> matrix[i][j];

        cout << "Instancia " << test << '\n';

        if(is_valid_sudoku(matrix))
            cout << "SIM\n";
        else
            cout << "NAO\n";

        cout << "\n";
    });

	return 0;
}
 