class Solution(object):
    def minimumCost(self, cost1, cost2, costBoth, need1, need2):
        """
        :type cost1: int
        :type cost2: int
        :type costBoth: int
        :type need1: int
        :type need2: int
        :rtype: int
        """
        # Strategy 1: Buy only separate items for each requirement
        separate_only = need1 * cost1 + need2 * cost2
        
        # Strategy 2: Buy type 3 items up to the smaller need, then cover the rest separately
        common = min(need1, need2)
        rem1 = need1 - common
        rem2 = need2 - common
        mixed_strategy = common * costBoth + rem1 * cost1 + rem2 * cost2
        
        # Strategy 3: Buy only type 3 items to cover the larger need
        both_only = max(need1, need2) * costBoth
        
        return min(separate_only, mixed_strategy, both_only)
