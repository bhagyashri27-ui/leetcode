#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();
        
        // Step 1: Precalculate the cost of making each subarray of size x equal.
        // We use two multisets to maintain the sliding window median dynamically.
        multiset<long long> left_half;  // stores the smaller half (max element at left_half.rbegin())
        multiset<long long> right_half; // stores the larger half (min element at right_half.begin())
        
        long long sum_left = 0;
        long long sum_right = 0;
        
        auto balance = [&]() {
            if (left_half.size() > right_half.size() + 1) {
                auto it = prev(left_half.end());
                sum_left -= *it;
                right_half.insert(*it);
                sum_right += *it;
                left_half.erase(it);
            } else if (right_half.size() > left_half.size()) {
                auto it = right_half.begin();
                sum_right -= *it;
                left_half.insert(*it);
                sum_left += *it;
                right_half.erase(it);
            }
        };
        
        auto add = [&](long long val) {
            if (left_half.empty() || val <= *left_half.rbegin()) {
                left_half.insert(val);
                sum_left += val;
            } else {
                right_half.insert(val);
                sum_right += val;
            }
            balance();
        };
        
        auto remove = [&](long long val) {
            auto it = left_half.find(val);
            if (it != left_half.end()) {
                left_half.erase(it);
                sum_left -= val;
            } else {
                it = right_half.find(val);
                if (it != right_half.end()) {
                    right_half.erase(it);
                    sum_right -= val;
                }
            }
            balance();
        };
        
        vector<long long> cost(n - x + 1, 0);
        
        // Initialize the first window of size x
        for (int i = 0; i < x; ++i) {
            add(nums[i]);
        }
        
        // Helper to calculate cost for the current window median
        auto get_cost = [&]() {
            long long median = *left_half.rbegin();
            // Total operations = (sum of elements in right_half - count_right * median) + 
            //                    (count_left * median - sum of elements in left_half)
            long long right_cost = sum_right - (long long)right_half.size() * median;
            long long left_cost = (long long)left_half.size() * median - sum_left;
            return left_cost + right_cost;
        };
        
        cost[0] = get_cost();
        
        // Slide the window across the rest of the array
        for (int i = 1; i <= n - x; ++i) {
            remove(nums[i - 1]);
            add(nums[i + x - 1]);
            cost[i] = get_cost();
        }
        
        // Step 2: Dynamic Programming to select k non-overlapping windows.
        // dp[j][i] = min cost using j windows up to index i.
        // Since k is small (k <= 15) and n <= 10^5, we optimize state representation.
        // Let dp[j] be the minimum cost using j windows.
        const long long INF = 1e15; // Safe large number avoiding JavaScript serialization overflow
        
        // We will maintain DP table across the sliding indices:
        // dp[j] represents the min cost using j windows up to the current position.
        vector<long long> dp(k + 1, INF);
        vector<long long> next_dp(k + 1, INF);
        
        dp[0] = 0;
        
        // To transition efficiently:
        // When we are at index `i` (representing window ending or starting), 
        // we can either skip `i` or take window `cost[i]` starting at `i`.
        // Standard DP for choosing non-overlapping segments of length x:
        // Let's build a clean 1D rolling array DP or standard vector DP.
        
        // A direct approach for DP with interval selection:
        // dp_table[i][j]: min cost using j windows from the first i elements.
        vector<vector<long long>> dp_table(n + 1, vector<long long>(k + 1, INF));
        for (int i = 0; i <= n; ++i) {
            dp_table[i][0] = 0;
        }
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= k; ++j) {
                // Option 1: Do not start a window at index i-1
                dp_table[i][j] = dp_table[i - 1][j];
                
                // Option 2: Start a window of size x at index i - x (if valid)
                if (i >= x) {
                    dp_table[i][j] = min(dp_table[i][j], dp_table[i - x][j - 1] + cost[i - x]);
                }
            }
        }
        
        return dp_table[n][k];
    }
};