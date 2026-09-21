from typing import List

class Solution:
    def resultArray(self, nums: List[int], k: int) -> List[int]:
        result = [0] * k
        # dp[v] stores the number of subarrays ending at the previous index 
        # that have a product modulo k equal to v
        dp = [0] * k
        
        for num in nums:
            next_dp = [0] * k
            val = num % k
            
            # Start a new subarray with the current element
            next_dp[val] += 1
            
            # Extend existing subarrays ending at the previous index
            for v in range(k):
                if dp[v] > 0:
                    next_dp[(v * val) % k] += dp[v]
            
            # Update dp for the next iteration and accumulate to result
            dp = next_dp
            for v in range(k):
                result[v] += dp[v]
                
        return result
