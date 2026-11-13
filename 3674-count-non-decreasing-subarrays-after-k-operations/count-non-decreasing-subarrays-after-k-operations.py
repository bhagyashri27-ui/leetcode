from collections import deque

class Solution(object):
    def countNonDecreasingSubarrays(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        # Deque stores [value, count_of_elements_raised_to_this_value]
        dq = deque()
        curr_cost = 0
        ans = 0
        r = n - 1
        
        for l in range(n - 1, -1, -1):
            val = nums[l]
            count = 1
            
            # Merge all blocks to the right that are smaller than nums[l]
            while dq and dq[0][0] < val:
                prev_val, prev_count = dq.popleft()
                # Every element in that block must be raised to 'val'
                curr_cost += (val - prev_val) * prev_count
                count += prev_count
                
            dq.appendleft([val, count])
            
            # Shrink the window from the right if the cost exceeds k
            while curr_cost > k:
                # The rightmost element in the window belongs to the block at dq[-1]
                curr_cost -= (dq[-1][0] - nums[r])
                dq[-1][1] -= 1
                if dq[-1][1] == 0:
                    dq.pop()
                r -= 1
                
            # All subarrays starting at l and ending at any index from l to r are valid
            ans += (r - l + 1)
            
        return ans
