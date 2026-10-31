class Solution(object):
    def uniquePaths(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        m, n = len(grid), len(grid[0])
        MOD = 10**9 + 7
        
        # Memoization table for reflections: memo_reflect[r][c][direction]
        # direction: 0 = entered moving right, 1 = entered moving down
        memo_reflect = {}
        
        def get_destination(r, c, direction):
            state = (r, c, direction)
            if state in memo_reflect:
                return memo_reflect[state]
            
            if direction == 0:  # Entered moving right -> turns down
                nr, nc = r + 1, c
                next_dir = 1
            else:               # Entered moving down -> turns right
                nr, nc = r, c + 1
                next_dir = 0
                
            # If reflection goes out of bounds, the path becomes invalid
            if nr >= m or nc >= n:
                memo_reflect[state] = None
                return None
                
            if grid[nr][nc] == 0:
                memo_reflect[state] = (nr, nc)
                return (nr, nc)
            else:
                # Recursively follow the next mirror reflection
                res = get_destination(nr, nc, next_dir)
                memo_reflect[state] = res
                return res

        # dp[r][c] will store the number of unique valid paths from (r, c) to (m-1, n-1)
        dp = [[0] * n for _ in range(m)]
        dp[m - 1][n - 1] = 1  # Base case: Destination reached
        
        # Fill the DP table backwards from bottom-right to top-left
        for r in range(m - 1, -1, -1):
            for c in range(n - 1, -1, -1):
                if grid[r][c] == 1 or (r == m - 1 and c == n - 1):
                    continue
                
                ways = 0
                
                # Option 1: Try moving Right
                if c + 1 < n:
                    if grid[r][c + 1] == 0:
                        ways = (ways + dp[r][c + 1]) % MOD
                    else:
                        dest = get_destination(r, c + 1, 0)
                        if dest:
                            ways = (ways + dp[dest[0]][dest[1]]) % MOD
                            
                # Option 2: Try moving Down
                if r + 1 < m:
                    if grid[r + 1][c] == 0:
                        ways = (ways + dp[r + 1][c]) % MOD
                    else:
                        dest = get_destination(r + 1, c, 1)
                        if dest:
                            ways = (ways + dp[dest[0]][dest[1]]) % MOD
                            
                dp[r][c] = ways
                
        return dp[0][0]
