class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        const auto n = static_cast<int>(heights.size());
        vector<int> low(n), high(n);
        vector<pair<int, int>> min_queue;

        constexpr int NINF = numeric_limits<int>::min();

        min_queue.emplace_back(NINF, -1);

        for(int i = 0; i < n; ++i) {
            while(min_queue.back().first >= heights[i])
                min_queue.pop_back();

            low[i] = min_queue.back().second + 1;

            min_queue.emplace_back(heights[i], i);
        }

        min_queue.clear();

        min_queue.emplace_back(NINF, n);

        for(int i = n - 1; i >= 0; --i) {
            while(min_queue.back().first >= heights[i])
                min_queue.pop_back();

            high[i] = min_queue.back().second - 1;

            min_queue.emplace_back(heights[i], i);
        }

        int max_area = NINF;

        for(int i = 0; i < n; ++i)
            max_area = max(max_area, (high[i] - low[i] + 1) * heights[i]);

        return max_area;
    }
};