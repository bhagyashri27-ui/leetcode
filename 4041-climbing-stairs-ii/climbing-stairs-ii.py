class Solution(object):
    def climbStairs(self, n, costs):
        """
        :type n: int
        :type costs: List[int]
        :rtype: int
        """
        # Track the minimum costs to reach steps (j - 3), (j - 2), and (j - 1)
        prev3 = float('inf')
        prev2 = float('inf')
        prev1 = 0  # Starting at step 0 with cost 0

        for j in range(1, n + 1):
            # Minimum jump cost to reach step j (note: costs is 0-indexed in Python)
            curr = costs[j - 1] + min(
                prev1 + 1,  # Jump of 1 step: (1)^2 = 1
                prev2 + 4,  # Jump of 2 steps: (2)^2 = 4
                prev3 + 9   # Jump of 3 steps: (3)^2 = 9
            )
            prev3, prev2, prev1 = prev2, prev1, curr

        return prev1
