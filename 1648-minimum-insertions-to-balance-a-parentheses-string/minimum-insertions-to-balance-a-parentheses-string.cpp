class Solution {
public:
    int minInsertions(string s) {
        int insertions = 0;
        int needed_right = 0;

        for (char c : s) {
            if (c == '(') {
                // If we need an odd number of ')', we have a single ')' waiting.
                // Insert one ')' to complete the pair.
                if (needed_right % 2 != 0) {
                    insertions++;
                    needed_right--; // Completes the pair for a previous '('
                }
                needed_right += 2; // Current '(' needs '))'
            } else { // c == ')'
                needed_right--;
                // If needed_right becomes -1, we encountered a ')' without a '('
                if (needed_right < 0) {
                    insertions++;     // Insert a '('
                    needed_right += 2; // The inserted '(' needs '))', minus current ')' = 1
                }
            }
        }

        return insertions + needed_right;
    }
};