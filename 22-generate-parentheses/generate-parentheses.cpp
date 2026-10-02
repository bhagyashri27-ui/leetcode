#include <vector>
#include <string>

class Solution {
public:
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> result;
        backtrack(result, "", 0, 0, n);
        return result;
    }

private:
    void backtrack(std::vector<std::string>& result, std::string current_string, int open_count, int close_count, int n) {
        // Base case: if the string length is exactly 2*n, a valid combination is formed
        if (current_string.length() == 2 * n) {
            result.push_back(current_string);
            return;
        }
        
        // Add an opening parenthesis if we haven't used all 'n' of them
        if (open_count < n) {
            backtrack(result, current_string + "(", open_count + 1, close_count, n);
        }
        
        // Add a closing parenthesis if there is an unmatched opening parenthesis available
        if (close_count < open_count) {
            backtrack(result, current_string + ")", open_count, close_count + 1, n);
        }
    }
};