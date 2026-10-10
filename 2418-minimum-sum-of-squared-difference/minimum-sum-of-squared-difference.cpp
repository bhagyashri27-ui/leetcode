class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        // Frequency array for absolute differences (max difference is 10^5)
        vector<int> diffCount(100001, 0);
        
        for (int i = 0; i < nums1.size(); i++) {
            diffCount[abs(nums1[i] - nums2[i])]++;
        }
        
        long long left = (long long)k1 + k2;
        
        // Greedily reduce the largest differences
        for (int i = 100000; i > 0; i--) {
            if (diffCount[i] > 0) {
                long long take = min(left, (long long)diffCount[i]);
                diffCount[i] -= take;
                diffCount[i - 1] += take;
                left -= take;
                
                if (left == 0) break;
            }
        }
        
        // Calculate the final minimum sum of squared difference
        long long ans = 0;
        for (int i = 1; i <= 100000; i++) {
            if (diffCount[i] > 0) {
                ans += (long long)diffCount[i] * i * i;
            }
        }
        
        return ans;
    }
};