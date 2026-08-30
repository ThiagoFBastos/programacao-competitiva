class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        map<int, int> frequency;

        auto add = [](auto& container, int key) {
            ++container[key];
        };

        auto rem = [](auto& container, int key) {
            if(auto it = container.find(key); it != container.end() && --it->second == 0)
                container.erase(it);
        };

        const auto window_size = static_cast<size_t>(indexDiff + 1);

        for(size_t i = 0; i < nums.size(); ++i) {
            
            if(i >= window_size)
                rem(frequency, nums[i - window_size]);

            auto it = frequency.lower_bound(nums[i]);

            if(it != frequency.end()) {
                int key = it->first;

                if(key - nums[i] <= valueDiff)
                    return true;
            }

            if(it != frequency.begin()) {
                int key = prev(it)->first;

                if(nums[i] - key <= valueDiff)
                    return true;
            }

            add(frequency, nums[i]);
        }

        return false;
    }
};