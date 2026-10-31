class Solution(object):
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        # Map to store the value and its corresponding index
        num_to_index = {}
        
        for index, num in enumerate(nums):
            complement = target - num
            
            # If the complement is already in the map, return the pair of indices
            if complement in num_to_index:
                return [num_to_index[complement], index]
            
            # Otherwise, store the index of the current number
            num_to_index[num] = index
            
        return []
