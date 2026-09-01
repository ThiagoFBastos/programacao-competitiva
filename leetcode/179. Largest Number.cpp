class Solution {
public:
    string largestNumber(vector<int>& nums) {
        auto str_nums = nums | views::transform([](const auto& s) {
            return to_string(s);
        }) | ranges::to<vector<string>>();

        sort(str_nums.begin(), str_nums.end(), [](const auto& a, const auto& b) {
            return a + b > b + a;
        });

        auto answer = accumulate(str_nums.begin(), str_nums.end(), ""s, plus<string>());

        if(answer.front() == '0')
            answer = "0";

        return answer;
    }
};