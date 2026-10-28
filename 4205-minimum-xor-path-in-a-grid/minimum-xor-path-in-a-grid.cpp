#include <vector>
#include <bitset>
#include <algorithm>

class Solution {
public:
    int minCost(std::vector<std::vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        // Max possible XOR value is 2047 since grid values are up to 1023
        const int MAX_XOR = 2048; 
        
        // dp[j] stores a bitset of reachable XOR values for column j
        std::vector<std::bitset<MAX_XOR>> dp(n);
        
        // Base case: starting cell (0, 0)
        dp[0][grid[0][0]] = 1;
        
        // Initialize the first row (can only move right)
        for (int j = 1; j < n; ++j) {
            int val = grid[0][j];
            for (int x = 0; x < MAX_XOR; ++x) {
                if (dp[j - 1][x]) {
                    dp[j][x ^ val] = 1;
                }
            }
        }
        
        // Fill the rest of the grid row by row
        for (int i = 1; i < m; ++i) {
            // Update column 0 for the current row (can only move down from previous row)
            std::bitset<MAX_XOR> next_dp0;
            int val0 = grid[i][0];
            for (int x = 0; x < MAX_XOR; ++x) {
                if (dp[0][x]) {
                    next_dp0[x ^ val0] = 1;
                }
            }
            dp[0] = next_dp0;
            
            // Update the remaining columns (can move down or right)
            for (int j = 1; j < n; ++j) {
                std::bitset<MAX_XOR> next_dpj;
                int valj = grid[i][j];
                for (int x = 0; x < MAX_XOR; ++x) {
                    // Check if reachable from top cell (dp[j][x]) or left cell (dp[j-1][x])
                    if (dp[j][x] || dp[j - 1][x]) {
                        next_dpj[x ^ valj] = 1;
                    }
                }
                dp[j] = next_dpj;
            }
        }
        
        // Find the smallest reachable XOR value at the bottom-right cell
        for (int x = 0; x < MAX_XOR; ++x) {
            if (dp[n - 1][x]) {
                return x;
            }
        }
        
        return 0;
    }
};