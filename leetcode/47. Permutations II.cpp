class Solution {
    vector<bool> in_use;
    vector<vector<int>> p;
    vector<int> ord;
    
    void backtrack(vector<int>& a, int k) {
        int n = a.size();
        if(k == n) p.emplace_back(ord);
        else {
            for(int i = 0; i < n; ++i) {
                if(in_use[i] || i && a[i] == a[i - 1] && !in_use[i - 1]) continue;
                in_use[i] = true;
                ord[k] = a[i];
                backtrack(a, k + 1);
                in_use[i] = false;
            }
        }
    }
    
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
      int n = nums.size();
      in_use.assign(n, false);
      ord.resize(n);
      sort(nums.begin(), nums.end());
      backtrack(nums, 0);
      return p;
    }
};