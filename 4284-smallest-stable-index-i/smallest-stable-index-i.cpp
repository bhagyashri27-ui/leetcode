class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> suffMin(n);
        
        // Precompute the minimums from right to left
        suffMin[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suffMin[i] = min(suffMin[i + 1], nums[i]);
        }
        
        int currentMax = nums[0];
        
        // Iterate left to right to check the instability score
        for (int i = 0; i < n; ++i) {
            currentMax = max(currentMax, nums[i]);
            
            if (currentMax - suffMin[i] <= k) {
                return i; // First index that satisfies the condition
            }
        }
        
        return -1;
    }
};