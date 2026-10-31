import heapq
from collections import defaultdict

class Solution(object):
    def shortestPath(self, n, edges, labels, k):
        """
        :type n: int
        :type edges: List[List[int]]
        :type labels: str
        :type k: int
        :rtype: int
        """
        # Step 1: Build the adjacency list
        adj = defaultdict(list)
        for u, v, w in edges:
            adj[u].append((v, w))
            
        # Step 2: Initialize distance table
        # dist[u][c] stores the shortest distance to node u 
        # with exactly 'c' consecutive identical characters ending at u.
        # Since c goes up to k, we use an array of size k + 1.
        INF = float('inf')
        dist = [[INF] * (k + 1) for _ in range(n)]
        
        # Priority queue stores tuples of: (current_weight, node, consecutive_count)
        # We start at node 0, which has its own label counting as 1 consecutive character.
        pq = [(0, 0, 1)]
        dist[0][1] = 0
        
        while pq:
            d, u, count = heapq.heappop(pq)
            
            # If we reached the target node, since it's a min-heap, 
            # this is guaranteed to be the shortest valid path.
            if u == n - 1:
                return d
                
            # If we found a shorter path to this state already, skip processing
            if d > dist[u][count]:
                continue
                
            curr_char = labels[u]
            
            # Explore outgoing edges
            for v, w in adj[u]:
                v_char = labels[v]
                
                if v_char == curr_char:
                    next_count = count + 1
                else:
                    next_count = 1
                    
                # The path is only valid if consecutive characters do not exceed k
                if next_count <= k:
                    if d + w < dist[v][next_count]:
                        dist[v][next_count] = d + w
                        heapq.heappush(pq, (d + w, v, next_count))
                        
        return -1
