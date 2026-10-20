#include <vector>
#include <algorithm>
#include <cmath>

class Solution {
public:
    int sortableIntegers(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<int> divisors;
        
        // Find all divisors of n
        for (int i = 1; i <= std::sqrt(n); ++i) {
            if (n % i == 0) {
                divisors.push_back(i);
                if (i * i != n) {
                    divisors.push_back(n / i);
                }
            }
        }
        
        int ans = 0;
        
        // Check each divisor k
        for (int k : divisors) {
            bool possible = true;
            int prev_max = -1;
            
            for (int i = 0; i < n; i += k) {
                int drop_count = 0;
                int drop_idx = -1;
                
                // Count internal drops within the block
                for (int j = i; j < i + k - 1; ++j) {
                    if (nums[j] > nums[j + 1]) {
                        drop_count++;
                        drop_idx = j;
                        if (drop_count > 1) break;
                    }
                }
                
                if (drop_count > 1) {
                    possible = false;
                    break;
                }
                
                int b_min, b_max;
                
                // Check the wrap-around boundary condition
                if (nums[i + k - 1] > nums[i]) {
                    drop_count++;
                    if (drop_count > 1) {
                        possible = false;
                        break;
                    }
                    b_min = nums[i];
                    b_max = nums[i + k - 1];
                } else {
                    if (drop_count == 0) {
                        b_min = nums[i];
                        b_max = nums[i + k - 1];
                    } else {
                        b_min = nums[drop_idx + 1];
                        b_max = nums[drop_idx];
                    }
                }
                
                // Check global sorted order between blocks
                if (prev_max > b_min) {
                    possible = false;
                    break;
                }
                prev_max = b_max;
            }
            
            if (possible) {
                ans += k;
            }
        }
        
        return ans;
    }
};