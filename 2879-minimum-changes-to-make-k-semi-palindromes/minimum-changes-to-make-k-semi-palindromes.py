class Solution(object):
    def minimumChanges(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        n = len(s)
        
        # 1. Precompute valid proper divisors for each possible length L (2 to n)
        divisors = [[] for _ in range(n + 1)]
        for length in range(2, n + 1):
            for d in range(1, length // 2 + 1):
                if length % d == 0:
                    divisors[length].append(d)
                    
        # 2. Precompute minimum changes to make s[i..j] a semi-palindrome
        INF = float('inf')
        cost = [[INF] * n for _ in range(n)]
        
        for i in range(n):
            for j in range(i + 1, n):
                length = j - i + 1
                min_ops = INF
                
                for d in divisors[length]:
                    ops = 0
                    # Check each of the d groups
                    for start in range(d):
                        left = i + start
                        # Last element index in this group
                        right = i + start + ((length - 1 - start) // d) * d
                        while left < right:
                            if s[left] != s[right]:
                                ops += 1
                            left += d
                            right -= d
                    if ops < min_ops:
                        min_ops = ops
                        
                cost[i][j] = min_ops
                
        # 3. DP to partition s[0..i-1] into p substrings
        # dp[p][i] = min changes for prefix of length i using p partitions
        dp = [[INF] * (n + 1) for _ in range(k + 1)]
        dp[0][0] = 0
        
        for p in range(1, k + 1):
            # Each partition needs length >= 2, so i >= 2 * p
            for i in range(2 * p, n + 1):
                # Previous prefix must hold p - 1 partitions, so m >= 2 * (p - 1)
                for m in range(2 * (p - 1), i - 1):
                    if dp[p - 1][m] != INF:
                        dp[p][i] = min(dp[p][i], dp[p - 1][m] + cost[m][i - 1])
                        
        return dp[k][n]
