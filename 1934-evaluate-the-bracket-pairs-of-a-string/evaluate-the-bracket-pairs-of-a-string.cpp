#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        // Step 1: Store the knowledge pairs inside a hash map for O(1) lookups
        unordered_map<string, string> dict;
        for (const auto& pair : knowledge) {
            dict[pair[0]] = pair[1];
        }

        string result = "";
        string current_key = "";
        bool inside_bracket = false;

        // Step 2: Traverse the string in a single linear pass
        for (char c : s) {
            if (c == '(') {
                inside_bracket = true;
            } else if (c == ')') {
                inside_bracket = false;
                // Fetch value if key exists, otherwise use "?"
                if (dict.count(current_key)) {
                    result += dict[current_key];
                } else {
                    result += "?";
                }
                current_key = ""; // Reset key for the next bracket pair
            } else {
                if (inside_bracket) {
                    current_key += c;
                } else {
                    result += c;
                }
            }
        }

        return result;
    }
};