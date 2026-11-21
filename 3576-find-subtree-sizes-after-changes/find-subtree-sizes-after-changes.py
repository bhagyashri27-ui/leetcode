class Solution(object):
    def findSubtreeSizes(self, parent, s):
        """
        :type parent: List[int]
        :type s: str
        :rtype: List[int]
        """
        n = len(parent)
        adj = [[] for _ in range(n)]
        for i in range(1, n):
            adj[parent[i]].append(i)

        new_parent = list(parent)
        last_seen = {}

        # Iterative DFS to avoid recursion limit on deep trees (n up to 10^5)
        stack = [(0, 0)]  # (node, state: 0 = enter, 1 = exit)
        history = []

        while stack:
            u, state = stack.pop()
            ch = s[u]
            if state == 0:
                prev = last_seen.get(ch, -1)
                if prev != -1:
                    new_parent[u] = prev
                history.append((ch, prev))
                last_seen[ch] = u

                stack.append((u, 1))
                for v in adj[u]:
                    stack.append((v, 0))
            else:
                ch_restore, prev_restore = history.pop()
                last_seen[ch_restore] = prev_restore

        # Build the updated tree
        new_adj = [[] for _ in range(n)]
        for i in range(1, n):
            new_adj[new_parent[i]].append(i)

        # Iterative post-order traversal to compute subtree sizes
        answer = [1] * n
        order = []
        dfs_stack = [0]
        while dfs_stack:
            u = dfs_stack.pop()
            order.append(u)
            for v in new_adj[u]:
                dfs_stack.append(v)

        for u in reversed(order):
            for v in new_adj[u]:
                answer[u] += answer[v]

        return answer
