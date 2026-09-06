class Solution:
    def numDistinct(self, s: str, t: str) -> int:
        # Get lengths of both strings
        m, n = len(s), len(t)
        
        # If t is longer than s, t cannot be a subsequence of s
        if n > m:
            return 0
            
        # dp[j] stores the number of distinct subsequences matching t[:j]
        # Base case: There is 1 way to form an empty string t (by deleting all characters)
        dp = [1] + [0] * n
        
        # Iterate over each character in string s
        for i in range(1, m + 1):
            # Traverse t backwards to avoid using updated values from the same row
            for j in range(n, 0, -1):
                if s[i - 1] == t[j - 1]:
                    # Current count is the sum of excluding s[i-1] and including s[i-1]
                    dp[j] = dp[j] + dp[j - 1]
                # If characters do not match, dp[j] remains unchanged (excludes s[i-1])
                    
        return dp[n]
