class Solution:
    def stoneGameIX(self, stones: List[int]) -> bool:
        # Count the frequency of each remainder modulo 3
        count = [0] * 3
        for stone in stones:
            count[stone % 3] += 1
            
        # Case 1: If the number of 0-remainder stones is even
        if count[0] % 2 == 0:
            return count[1] > 0 and count[2] > 0
            
        # Case 2: If the number of 0-remainder stones is odd
        return abs(count[1] - count[2]) > 2
