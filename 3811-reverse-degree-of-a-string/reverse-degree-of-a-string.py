class Solution:
    def reverseDegree(self, s: str) -> int:
        total_degree = 0
        
        # Iterate over the string using 1-indexed positions
        for i, c in enumerate(s, 1):
            # Calculate the position in the reversed alphabet ('a' -> 26, 'z' -> 1)
            rev_alpha_pos = 26 - (ord(c) - ord('a'))
            
            # Add the product of the reversed alphabet position and the string position
            total_degree += rev_alpha_pos * i
            
        return total_degree
