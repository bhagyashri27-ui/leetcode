class Solution(object):
    def minimizeSum(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        nums.sort()
        
        # 1. Change the two smallest elements to match nums[2]
        # 2. Change the smallest and largest elements to match nums[1]
        # 3. Change the two largest elements to match nums[-3]
        return min(
            nums[-1] - nums[2],
            nums[-2] - nums[1],
            nums[-3] - nums[0]
        )
