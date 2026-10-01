#include <stack>
#include <string>

class Solution {
public:
    bool isValid(std::string s) {
        // If the length is odd, it cannot be valid
        if (s.length() % 2 != 0) return false;
        
        std::stack<char> st;
        
        for (char c : s) {
            // Push opening brackets onto the stack
            if (c == '(' || c == '{' || c == '[') {
                st.push(c);
            } 
            // Handle closing brackets
            else {
                // If stack is empty, there is no opening bracket to match
                if (st.empty()) return false;
                
                char top = st.top();
                
                // Check if the top of the stack matches the closing bracket
                if ((c == ')' && top == '(') || 
                    (c == '}' && top == '{') || 
                    (c == ']' && top == '[')) {
                    st.pop();
                } else {
                    return false;
                }
            }
        }
        
        // If the stack is empty, all brackets were matched correctly
        return st.empty();
    }
};