import math

class Solution:
    def numberOfSets(self, n: int, k: int) -> int:
        # The combinatorial formula to find the number of ways 
        # to choose k non-overlapping segments from n points.
        return math.comb(n + k - 1, 2 * k) % (10**9 + 7)
