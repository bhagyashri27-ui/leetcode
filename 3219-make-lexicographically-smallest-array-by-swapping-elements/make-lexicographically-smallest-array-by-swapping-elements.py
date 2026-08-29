from typing import List

class Solution:
    def lexicographicallySmallestArray(self, nums: List[int], limit: int) -> List[int]:
        # Pair each number with its original index and sort by the values
        sorted_pairs = sorted(enumerate(nums), key=lambda x: x[1])
        
        ans = [0] * len(nums)
        
        # Two pointers to find groups of connected components
        i = 0
        n = len(nums)
        
        while i < n:
            j = i + 1
            # Find the boundary of the current connected group
            while j < n and sorted_pairs[j][1] - sorted_pairs[j - 1][1] <= limit:
                j += 1
            
            # Extract the original indices for this group and sort them
            group_indices = sorted(sorted_pairs[k][0] for k in range(i, j))
            
            # The values are already sorted in sorted_pairs from index i to j - 1
            # Place the sorted values into the sorted positions
            for k in range(i, j):
                ans[group_indices[k - i]] = sorted_pairs[k][1]
                
            # Move to the next group
            i = j
            
        return ans
