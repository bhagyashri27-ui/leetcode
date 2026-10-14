class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        string ans = "";
        for (int i = 0; i < num; ++i) {
            int cur = min(9, sum);
            ans += to_string(cur);
            sum -= cur;
        }
        
        // If there is still remaining sum that couldn't be placed, it's impossible
        if (sum > 0) {
            return "";
        }
        
        return ans;
    }
};