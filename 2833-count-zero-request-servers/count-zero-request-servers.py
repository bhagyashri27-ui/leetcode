class Solution(object):
    def countServers(self, n, logs, x, queries):
        """
        :type n: int
        :type logs: List[List[int]]
        :type x: int
        :type queries: List[int]
        :rtype: List[int]
        """
        # Sort logs based on time
        logs.sort(key=lambda log: log[1])
        
        # Pair each query with its original index and sort by query time
        sorted_queries = sorted(enumerate(queries), key=lambda q: q[1])
        
        ans = [0] * len(queries)
        server_counts = {}
        active_servers = 0
        
        left = 0
        right = 0
        m = len(logs)
        
        for original_idx, q_time in sorted_queries:
            # 1. Expand the window on the right: include all logs with time <= q_time
            while right < m and logs[right][1] <= q_time:
                server_id = logs[right][0]
                if server_counts.get(server_id, 0) == 0:
                    active_servers += 1
                server_counts[server_id] = server_counts.get(server_id, 0) + 1
                right += 1
                
            # 2. Shrink the window from the left: remove all logs with time < q_time - x
            while left < m and logs[left][1] < q_time - x:
                server_id = logs[left][0]
                if server_counts.get(server_id, 0) == 1:
                    active_servers -= 1
                server_counts[server_id] = server_counts.get(server_id, 0) - 1
                left += 1
                
            # 3. The answer is the total servers minus the active servers in the current window
            ans[original_idx] = n - active_servers
            
        return ans
