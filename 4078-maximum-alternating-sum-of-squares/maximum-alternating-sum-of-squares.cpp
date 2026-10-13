class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        
        // Take absolute values so we can sort by magnitude
        vector<long long> absNums(n);
        for (int i = 0; i < n; ++i) {
            absNums[i] = 1LL * abs(nums[i]);
        }
        
        // Sort the values in ascending order
        sort(absNums.begin(), absNums.end());
        
        long long score = 0;
        int mid = n / 2;
        
        // Subtract the squares of the smallest half (odd positions)
        for (int i = 0; i < mid; ++i) {
            score -= absNums[i] * absNums[i];
        }
        
        // Add the squares of the largest half (even positions)
        for (int i = mid; i < n; ++i) {
            score += absNums[i] * absNums[i];
        }
        
        return score;
    }
};