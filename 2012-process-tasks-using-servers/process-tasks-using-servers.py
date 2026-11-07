import heapq

class Solution(object):
    def assignTasks(self, servers, tasks):
        """
        :type servers: List[int]
        :type tasks: List[int]
        :rtype: List[int]
        """
        # free_servers heap stores: (weight, original_index)
        free_servers = []
        for i, weight in enumerate(servers):
            heapq.heappush(free_servers, (weight, i))
            
        # busy_servers heap stores: (free_time, weight, original_index)
        busy_servers = []
        
        ans = []
        current_time = 0
        
        for j, task_time in enumerate(tasks):
            # The current time cannot be behind the arrival second of the task
            current_time = max(current_time, j)
            
            # If no servers are free, we must fast-forward time to when the next server frees up
            if not free_servers:
                current_time = max(current_time, busy_servers[0][0])
                
            # Release all servers that have finished their tasks by the current_time
            while busy_servers and busy_servers[0][0] <= current_time:
                free_time, weight, idx = heapq.heappop(busy_servers)
                heapq.heappush(free_servers, (weight, idx))
                
            # Assign the task to the best available free server
            weight, idx = heapq.heappop(free_servers)
            ans.append(idx)
            
            # Put the server into the busy heap with its new completion time
            heapq.heappush(busy_servers, (current_time + task_time, weight, idx))
            
        return ans
