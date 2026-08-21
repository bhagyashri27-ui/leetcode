import math
from typing import List

class Solution:
    def findKthSmallest(self, coins: List[int], k: int) -> int:
        n = len(coins)
        max_ans = min(coins) * k
        lcm_lists = []
        
        # Precompute the LCM for all valid non-empty combinations of coins
        for i in range(1, 1 << n):
            current_lcm = 1
            bits = 0
            for j in range(n):
                if i & (1 << j):
                    bits += 1
                    current_lcm = math.lcm(current_lcm, coins[j])
            
            # If the LCM exceeds our maximum possible answer, it will never contribute
            if current_lcm <= max_ans:
                sign = 1 if bits % 2 == 1 else -1
                lcm_lists.append((current_lcm, sign))
                
        # Binary search for the answer
        left = 1
        right = max_ans
        
        while left < right:
            mid = (left + right) // 2
            
            # Count how many valid amounts are <= mid using Inclusion-Exclusion
            count = 0
            for l, sign in lcm_lists:
                count += sign * (mid // l)
                
            if count >= k:
                right = mid
            else:
                left = mid + 1
                
        return left