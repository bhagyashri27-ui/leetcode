#include <vector>
#include <algorithm>

class Solution {
public:
    int minOperations(std::vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 0;

        // Build expected sorted and reversed templates
        std::vector<int> sorted_arr(n);
        for (int i = 0; i < n; ++i) sorted_arr[i] = i;

        std::vector<int> rev_arr(n);
        for (int i = 0; i < n; ++i) rev_arr[i] = n - 1 - i;

        int ans = -1;

        // Helper to check if arr is a cyclic rotation of target
        // Returns the shift count if true, or -1 otherwise
        auto get_shift = [&](const std::vector<int>& target) {
            int shift = -1;
            for (int i = 0; i < n; ++i) {
                // Find where target[0] is in nums
                if (nums[i] == target[0]) {
                    shift = i;
                    break;
                }
            }
            if (shift == -1) return -1;
            // Verify the rest of the rotation
            for (int i = 0; i < n; ++i) {
                if (nums[(shift + i) % n] != target[i]) {
                    return -1;
                }
            }
            return shift;
        };

        // Case A: Check if nums is a rotation of the sorted array (Type 0)
        int shift_sorted = get_shift(sorted_arr);
        if (shift_sorted != -1) {
            // Option 1: Only rotate left `shift_sorted` times
            int cost = shift_sorted;
            
            // Option 2: Reverse (cost 1) -> Rotate left (n - shift_sorted) times -> Reverse (cost 1)
            int alt_cost = 2 + (n - shift_sorted) % n;
            
            int current_min = std::min(cost, alt_cost);
            if (ans == -1 || current_min < ans) ans = current_min;
        }

        // Case B: Check if nums is a rotation of the reversed array (Type 1)
        int shift_rev = get_shift(rev_arr);
        if (shift_rev != -1) {
            // Option 1: Reverse first (cost 1) -> Rotate left `(n - shift_rev) % n` times
            int cost1 = 1 + (n - shift_rev) % n;
            
            // Option 2: Rotate left `shift_rev` times -> Reverse (cost 1)
            int cost2 = shift_rev + 1;
            
            int current_min = std::min(cost1, cost2);
            if (ans == -1 || current_min < ans) ans = current_min;
        }

        return ans;
    }
};