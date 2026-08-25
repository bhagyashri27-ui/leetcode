class Solution:
    def missingMultiple(self, nums: List[int], k: int) -> int:
        # Convert nums to a set for O(1) lookups
        num_set = set(nums)
        
        # Start checking multiples from 1 * k, 2 * k, 3 * k...
        multiple = k
        while multiple in num_set:
            multiple += k
            
        return multiple
