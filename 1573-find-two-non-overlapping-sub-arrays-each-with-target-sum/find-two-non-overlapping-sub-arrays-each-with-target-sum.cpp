#include <vector>
#include <algorithm>

class Solution {
public:
    int minSumOfLengths(std::vector<int>& arr, int target) {
        int n = arr.size();
        std::vector<int> best_till(n, INT_MAX / 2); // Stores min length seen so far
        
        int left = 0;
        int current_sum = 0;
        int min_sum_len = INT_MAX / 2;
        int min_len_so_far = INT_MAX / 2;
        
        for (int right = 0; right < n; ++right) {
            current_sum += arr[right];
            
            // Shrink window if sum exceeds target
            while (current_sum > target && left <= right) {
                current_sum -= arr[left];
                left++;
            }
            
            // Valid subarray found
            if (current_sum == target) {
                int curr_len = right - left + 1;
                
                // If there's a valid non-overlapping subarray before `left`
                if (left > 0 && best_till[left - 1] != INT_MAX / 2) {
                    min_sum_len = std::min(min_sum_len, curr_len + best_till[left - 1]);
                }
                
                min_len_so_far = std::min(min_len_so_far, curr_len);
            }
            
            // Carry forward the best (minimum) length found so far
            best_till[right] = min_len_so_far;
        }
        
        return min_sum_len >= INT_MAX / 2 ? -1 : min_sum_len;
    }
};