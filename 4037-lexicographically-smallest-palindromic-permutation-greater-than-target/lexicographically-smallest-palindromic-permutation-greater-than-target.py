from collections import Counter

class Solution:
    def lexPalindromicPermutation(self, s: str, target: str) -> str:
        n = len(s)
        counts = Counter(s)
        
        # Check if a palindrome is possible
        odd_chars = [c for c, count in counts.items() if count % 2 == 1]
        if len(odd_chars) > 1:
            return ""
        
        mid_char = odd_chars[0] if odd_chars else ""
        
        # Available characters for the first half
        half_counts = {c: count // 2 for c, count in counts.items() if count // 2 > 0}
        
        # Unique sorted characters available
        chars = sorted(half_counts.keys())
        
        half_len = n // 2
        ans = [""]
        
        def construct_full_palindrome(first_half_list):
            first_half = "".join(first_half_list)
            if n % 2 == 1:
                return first_half + mid_char + first_half[::-1]
            else:
                return first_half + first_half[::-1]

        def dfs(idx, is_greater):
            if idx == half_len:
                full_pal = construct_full_palindrome(current_half)
                if full_pal > target:
                    ans[0] = full_pal
                    return True
                return False
            
            # If we are already strictly greater in the prefix, 
            # we should greedily take the smallest possible remaining characters
            if is_greater:
                for c in chars:
                    if half_counts[c] > 0:
                        half_counts[c] -= 1
                        current_half.append(c)
                        if dfs(idx + 1, True):
                            return True
                        current_half.pop()
                        half_counts[c] += 1
                return False
            
            # Otherwise, we are still matching the target prefix
            target_char = target[idx]
            for c in chars:
                if half_counts[c] > 0 and c >= target_char:
                    half_counts[c] -= 1
                    current_half.append(c)
                    
                    next_greater = is_greater or (c > target_char)
                    if dfs(idx + 1, next_greater):
                        return True
                        
                    current_half.pop()
                    half_counts[c] += 1
            return False

        current_half = []
        dfs(0, False)
        return ans[0]

