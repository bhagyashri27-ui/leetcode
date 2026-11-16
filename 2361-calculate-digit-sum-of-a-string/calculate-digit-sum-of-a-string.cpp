#include <string>
#include <iostream>

class Solution {
public:
    std::string digitSum(std::string s, int k) {
        while (s.length() > k) {
            std::string next_round = "";
            
            for (int i = 0; i < s.length(); i += k) {
                int sum = 0;
                // Sum up digits in the current group of size up to k
                int end = std::min((int)s.length(), i + k);
                for (int j = i; j < end; ++j) {
                    sum += s[j] - '0';
                }
                // Append the string representation of the sum
                next_round += std::to_string(sum);
            }
            
            s = next_round;
        }
        return s;
    }
};