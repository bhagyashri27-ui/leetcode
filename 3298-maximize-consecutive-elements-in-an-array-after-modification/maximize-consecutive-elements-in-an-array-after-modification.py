class Solution(object):
    def maxSelectedElements(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        nums.sort()
        # dp[v] stores the max length of a consecutive sequence ending at value v
        dp = {}
        
        for x in nums:
            # Update x + 1 first so it uses the state from BEFORE x is processed
            dp[x + 1] = dp.get(x, 0) + 1
            dp[x] = dp.get(x - 1, 0) + 1
            
        return max(dp.values())
