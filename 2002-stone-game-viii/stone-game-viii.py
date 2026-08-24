from typing import List

class Solution:
    def stoneGameVIII(self, stones: List[int]) -> int:
        n = len(stones)
        
        # Compute prefix sums
        pref = stones[:]
        for i in range(1, n):
            pref[i] += pref[i - 1]
            
        # Base case: if forced to take up to the last stone
        dp = pref[-1]
        
        # Iterate backwards from n-2 down to 1
        for i in range(n - 2, 0, -1):
            dp = max(dp, pref[i] - dp)
            
        return dp
