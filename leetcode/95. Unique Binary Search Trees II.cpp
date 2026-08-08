/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
    
   vector<TreeNode*> rec(int l, int r) {
   		if(l > r) return {nullptr};
   		else if(l == r) return {new TreeNode(r)};
   		vector<TreeNode*> t;
   		for(int k = l; k <= r; ++k) {
   			auto L = rec(l, k - 1);
   			auto R = rec(k + 1, r);
   			for(auto left : L)
   				for(auto right : R)
   					t.emplace_back(new TreeNode(k, left, right));
   		}
   		return t;
   }
    
public:
    vector<TreeNode*> generateTrees(int n) {
  		return rec(1, n);	      
    }
};