class Solution {
public:
    long long countCommas(long long n) {
        long long commas = 0;
        long long powerOf1000 = 1000;
        
        while (n >= powerOf1000) {
            commas += (n - powerOf1000 + 1);
            powerOf1000 *= 1000;
        }
        
        return commas;
    }
};