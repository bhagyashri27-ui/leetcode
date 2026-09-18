#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int checkSubstr(const string& s, int i, vector<int>& left, vector<int>& right) {
        int r = right[s[i] - 'a'];
        for (int j = i; j <= r; ++j) {
            // If a nested character's first occurrence is before our starting index 'i',
            // this substring is invalid as a standalone start point.
            if (left[s[j] - 'a'] < i) {
                return -1; 
            }
            // Expand the right boundary if nested characters appear later
            r = max(r, right[s[j] - 'a']);
        }
        return r;
    }

    vector<string> maxNumOfSubstrings(string s) {
        vector<int> left(26, s.length()), right(26, -1);
        
        // Step 1: Record first and last occurrences of each character
        for (int i = 0; i < s.length(); ++i) {
            left[s[i] - 'a'] = min(left[s[i] - 'a'], i);
            right[s[i] - 'a'] = max(right[s[i] - 'a'], i);
        }

        vector<string> res;
        int last_right = -1;
        
        // Step 2 & 3: Find valid intervals and greedily select them
        for (int i = 0; i < s.length(); ++i) {
            if (i == left[s[i] - 'a']) {
                int new_right = checkSubstr(s, i, left, right);
                if (new_right != -1) {
                    // If it starts after the last added interval, add a new placeholder
                    if (i > last_right) {
                        res.push_back("");
                    }
                    last_right = new_right;
                    // Overwrite the last interval (this acts as an append for new ones, 
                    // or a replacement for nested ones to minimize length)
                    res.back() = s.substr(i, last_right - i + 1);
                }
            }
        }
        return res;
    }
};