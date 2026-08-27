from collections import Counter

class Solution:
    def lexGreaterPermutation(self, s: str, target: str) -> str:
        n = len(s)
        s_counts = Counter(s)
        
        # Helper to construct the smallest remaining string from a frequency map
        def get_smallest_tail(counts):
            return "".join(sorted(counts.elements()))
        
        # Track the characters used in the current matching prefix
        current_counts = Counter(s_counts)
        
        # Track the best branching point found so far
        best_prefix_len = -1
        best_next_char = None
        
        # Step 1: Find the longest matching prefix with target
        # that can be extended to form a strictly greater string.
        for i in range(n):
            t_char = target[i]
            
            # Check if we can branch off at position i with a character > target[i]
            # We loop upwards, so the FIRST one we find is the smallest valid character
            for next_char_code in range(ord(t_char) + 1, ord('z') + 1):
                char = chr(next_char_code)
                if current_counts[char] > 0:
                    best_prefix_len = i
                    best_next_char = char
                    break  # <--- CRITICAL FIX: Stop at the smallest character greater than t_char
            
            # Try to match the current character of target to keep going deeper
            if current_counts[t_char] > 0:
                current_counts[t_char] -= 1
            else:
                break
                
        # If no valid branch point was found, it's impossible
        if best_prefix_len == -1:
            return ""
            
        # Step 2: Reconstruct the optimal string using the best branch point found
        final_counts = Counter(s_counts)
        final_prefix = []
        
        # Re-create the matching prefix up to the optimal branch index
        for i in range(best_prefix_len):
            t_char = target[i]
            final_prefix.append(t_char)
            final_counts[t_char] -= 1
            
        # Place the strictly greater character at the branch position
        final_prefix.append(best_next_char)
        final_counts[best_next_char] -= 1
        
        # Append all remaining characters sorted in ascending order
        return "".join(final_prefix) + get_smallest_tail(final_counts)

