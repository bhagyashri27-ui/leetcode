#include <string>
using namespace std;

class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.length();
        int count = 0;
        int last_end = -1;

        for (int i = 0; i < n; ++i) {
            // Check odd-length palindromes (center at i)
            // Check even-length palindromes (center between i and i+1)
            for (int len : {k, k + 1}) {
                int left = i - (len - 1) / 2;
                int right = i + len / 2;

                if (left > last_end && right < n && isPalindrome(s, left, right)) {
                    count++;
                    last_end = right;
                    break; // Greedily take the first valid palindrome found ending earliest
                }
            }
        }

        return count;
    }

private:
    bool isPalindrome(const string& s, int l, int r) {
        while (l < r) {
            if (s[l] != s[r]) return false;
            l++;
            r--;
        }
        return true;
    }
};