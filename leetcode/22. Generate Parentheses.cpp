
class Solution {
    char str[20];
    vector<string> s;
        
    void backtracking(int n, int a, int b) {
       if(a + b == 2 * n) {
           str[2 * n] = '\0';
           s.push_back(str);
       } else {
           if(a < n) {
               str[a + b] = '(';
               backtracking(n, a + 1, b);
           }
           if(a - b > 0) {
               str[a + b] = ')';
               backtracking(n, a, b + 1);
           }
       }
    }
    
public:
    vector<string> generateParenthesis(int n) {
        backtracking(n, 0, 0);
        return s;
    }
};