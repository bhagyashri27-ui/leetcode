class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
        int countLessThanTarget = 0;
        int countTarget = 0;
        
        for (int num : nums) {
            if (num < target) {
                countLessThanTarget++;
            } else if (num == target) {
                countTarget++;
            }
        }
        
        vector<int> result;
        for (int i = 0; i < countTarget; i++) {
            result.push_back(countLessThanTarget + i);
        }
        
        return result;
    }
};