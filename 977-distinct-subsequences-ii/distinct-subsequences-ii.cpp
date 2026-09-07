class Solution {
public:
    int distinctSubseqII(string s) {
        int MOD = 1e9 + 7;
        vector<long long> endsWith(26, 0);
        long long total = 0;

        for (char c : s) {
            int idx = c - 'a';
            long long old_endsWith = endsWith[idx];
            
            // The new subsequences ending with 'c' can be formed by appending 'c' 
            // to all existing distinct subsequences, plus the subsequence "c" itself.
            endsWith[idx] = (total + 1) % MOD;
            
            // Update total by removing the old count for this character and adding the new one.
            // Add MOD before applying modulo to prevent negative results in C++.
            total = (total - old_endsWith + endsWith[idx] + MOD) % MOD;
        }

        return total;
    }
};