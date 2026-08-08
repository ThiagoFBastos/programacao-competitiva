class Solution {
    bool noS[30][501];
    int cnt[30];
    vector<vector<int>> output; 
 
    bool backtracking(vector<int>& v, int k, int S) {
        
        if(S == 0) {
        	output.push_back({});
        	auto& u = output.back();
        	for(int i = 0; i < (int)v.size();++i)
        	for(int j = 0; j < cnt[i]; ++j)
        		u.push_back(v[i]);
        	return true;
        } else if(k == (int)v.size() || noS[k][S]) return false;
       	  
        bool ok = false;
        
        for(int i = 0; S - v[k] * i >= 0; ++i) {
		   	cnt[k] = i;
		    ok = backtracking(v, k + 1, S - i * v[k]) || ok;
            cnt[k] = 0;
		}
	
      	noS[k][S] = !ok;
      	
     	return ok; 	
    }
    
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        int n = candidates.size();
        
        for(int i = 0; i < n; ++i) {
        	cnt[i] = 0;
		    for(int j = 0; j <= target; ++j)
		    	noS[i][j] = false;
        }
  		
  		backtracking(candidates, 0, target);
  		
  		return output;
    }
};