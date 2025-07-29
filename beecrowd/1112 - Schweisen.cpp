#include <bits/stdc++.h>

using namespace std;

class BIT2D 
{

public:

	BIT2D(int rows, int columns): 
		_data {vector<vector<int>>(rows + 1, vector<int>(columns + 1, 0))},
		_rows {rows},
		_columns {columns}
	{
		
	}

	void update(int x, int y, int value)
	{
		++x;
		++y;

		for(; x <= _rows; x += x & -x)
			for(int k = y; k <= _columns; k += k & -k)
				_data[x][k] += value;
	}

	int query(int x, int y)
	{
		int answer {};

		++x;
		++y;

		for(; x > 0; x -= x & -x)
			for(int k = y; k > 0; k -= k & -k)
				answer += _data[x][k];

		return answer;
	}

	int query(int x0, int y0, int x1, int y1)
	{
		return query(x1, y1) - query(x1, y0 - 1) - query(x0 - 1, y1) + query(x0 - 1, y0 - 1);
	}	

private:
	vector<vector<int>> _data;
	int _rows;
	int _columns;
};

int main() 
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	while(true)
	{
		int rows, columns, p, queries;

		cin >> rows >> columns >> p;

		if(rows + columns + p == 0)
			break;

		cin >> queries;

		BIT2D bit(rows, columns);

		while(queries--)
		{
			char type;

			cin >> type;

			if(type == 'A')
			{
				int n, x, y;
		
				cin >> n >> x >> y;

				bit.update(x, y, n);
			}
			else
			{
				int x0, y0, x1, y1;

				cin >> x0 >> y0 >> x1 >> y1;

				if(x0 > x1) swap(x0, x1);
				if(y0 > y1) swap(y0, y1);

				cout << p * bit.query(x0, y0, x1, y1) << '\n';
			}
		}

		cout << '\n';
	}
	return 0;
}