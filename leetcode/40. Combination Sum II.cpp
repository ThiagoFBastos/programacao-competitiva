class Solution {
    bool noS[100][31], in_use[100];
    int frq[51];
    vector<vector<int>> output; 
 
    bool backtracking(vector<int>& v, int k, int S) {
        
        if(S == 0) {
        	output.push_back({});
        	auto& u = output.back();
        	for(int i = 0; i < (int)v.size();++i) if(in_use[i]) u.push_back(v[i]);
        	return true;
        } else if(k == (int)v.size() || noS[k][S]) return false;
       	  
        bool ok = false;
      	
      	
      	++frq[v[k]];
      	ok = backtracking(v, k + 1, S) || ok;
      	--frq[v[k]];
      	
      	if(S - v[k] >= 0 && !frq[v[k]]) {
      		in_use[k] = true;
      		ok = backtracking(v, k + 1, S - v[k]) || ok;
      		in_use[k] = false;
      	}
      	
      	if(frq[v[k]] == 0) noS[k][S] = !ok;

     	return ok; 	
    }
    
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        int n = candidates.size();
        
        for(int i = 0; i < n; ++i) {
        	in_use[i] = false;
		    for(int j = 0; j <= target; ++j)
		    	noS[i][j] = false;
        }
        
        memset(frq, 0, sizeof frq);
  		sort(candidates.begin(),candidates.end());
  		backtracking(candidates, 0, target);
  		
  		return output;
    }
};