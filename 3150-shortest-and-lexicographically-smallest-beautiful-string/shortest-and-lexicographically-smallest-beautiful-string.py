class Solution:
    def shortestBeautifulSubstring(self, s: str, k: int) -> str:
        min_len = float('inf')
        ans = ""
        n = len(s)
        
        # Check every possible substring
        for i in range(n):
            ones_count = 0
            for j in range(i, n):
                if s[j] == '1':
                    ones_count += 1
                
                # If we have exactly k ones
                if ones_count == k:
                    current_len = j - i + 1
                    current_sub = s[i:j+1]
                    
                    # Update if it's shorter, or same length but lexicographically smaller
                    if current_len < min_len:
                        min_len = current_len
                        ans = current_sub
                    elif current_len == min_len:
                        if current_sub < ans:
                            ans = current_sub
                    break # Any further extension will have more than k ones
                    
        return ans
