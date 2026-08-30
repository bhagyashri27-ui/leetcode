class Solution:
    def minimumDeletions(self, nums: List[int]) -> int:
        n = len(nums)
        if n <= 2:
            return n
            
        # Find the indices of the minimum and maximum elements
        min_idx = nums.index(min(nums))
        max_idx = nums.index(max(nums))
        
        # Ensure i is the smaller index and j is the larger index
        i = min(min_idx, max_idx)
        j = max(min_idx, max_idx)
        
        # Calculate the 3 possible strategies
        delete_both_front = j + 1
        delete_both_back = n - i
        delete_mixed = (i + 1) + (n - j)
        
        # Return the minimum deletions required
        return min(delete_both_front, delete_both_back, delete_mixed)
