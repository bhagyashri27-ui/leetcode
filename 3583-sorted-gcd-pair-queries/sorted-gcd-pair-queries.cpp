#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        // Step 1: Find the maximum element in nums to define our constraints boundary
        int max_val = 0;
        for (int num : nums) {
            max_val = max(max_val, num);
        }
        
        
        vector<long long> count(max_val + 1, 0);
        for (int num : nums) {
            count[num]++;
        }
        
      
        vector<long long> gcd_count(max_val + 1, 0);
        
        // Step 2: Iterate backward from max_val down to 1 to compute pair counts
        for (int g = max_val; g >= 1; --g) {
            long long total_multiples = 0;
            
            
            for (int multiple = g; multiple <= max_val; multiple += g) {
                total_multiples += count[multiple];
            }
            
            
            long long pairs_with_common_divisor_g = (total_multiples * (total_multiples - 1)) / 2;
            
            
            for (int multiple = 2 * g; multiple <= max_val; multiple += g) {
                pairs_with_common_divisor_g -= gcd_count[multiple];
            }
            
            gcd_count[g] = pairs_with_common_divisor_g;
        }
        
        // Step 3: Compute the prefix sums of the pair counts to handle cumulative queries
        vector<long long> prefix_sums(max_val + 1, 0);
        for (int i = 1; i <= max_val; ++i) {
            prefix_sums[i] = prefix_sums[i - 1] + gcd_count[i];
        }
        
        // Step 4: For each query, binary search the prefix sum to find the matching element value
        vector<int> answer;
        answer.reserve(queries.size());
        for (long long q : queries) {
            
            auto it = upper_bound(prefix_sums.begin(), prefix_sums.end(), q);
            answer.push_back(distance(prefix_sums.begin(), it));
        }
        
        return answer;
    }
};
