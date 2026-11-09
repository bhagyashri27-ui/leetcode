import heapq
import bisect

class Solution(object):
    def busiestServers(self, k, arrival, load):
        """
        :type k: int
        :type arrival: List[int]
        :type load: List[int]
        :rtype: List[int]
        """
        busy = []  # Min-heap storing tuples of (free_time, server_id)
        available = list(range(k))  # Sorted list of available server IDs
        req_count = [0] * k
        
        for i, (arr_time, l) in enumerate(zip(arrival, load)):
            # Free up servers whose job finish time <= current arrival time
            while busy and busy[0][0] <= arr_time:
                _, free_server = heapq.heappop(busy)
                bisect.insort(available, free_server)
            
            if not available:
                continue  # All servers are busy, drop the request
            
            # Find the first available server index >= (i % k)
            target = i % k
            idx = bisect.bisect_left(available, target)
            
            if idx == len(available):
                # Wrap around to the start of the available list
                chosen_server = available.pop(0)
            else:
                chosen_server = available.pop(idx)
                
            heapq.heappush(busy, (arr_time + l, chosen_server))
            req_count[chosen_server] += 1
            
        max_reqs = max(req_count)
        return [id for id, count in enumerate(req_count) if count == max_reqs]
