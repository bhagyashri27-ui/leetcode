from typing import List

class Solution:
    def longestSubsequence(self, nums: List[int]) -> int:
        total_xor = 0
        has_nonzero = False
        
        # Calculate the XOR sum of the entire array
        for num in nums:
            total_xor ^= num
            if num > 0:
                has_nonzero = True
                
        # Case 1: Total XOR is already non-zero
        if total_xor != 0:
            return len(nums)
            
        # Case 2: Total XOR is 0, but we can remove 1 non-zero element
        if has_nonzero:
            return len(nums) - 1
            
        # Case 3: All elements are 0, no non-zero subsequence is possible
        return 0
