class Solution {
public:
    bool checkDivisibility(int n) {
        int temp = n;
        int digitSum = 0;
        int digitProduct = 1;
        
        // Extract digits to calculate the sum and product
        while (temp > 0) {
            int digit = temp % 10;
            digitSum += digit;
            digitProduct *= digit;
            temp /= 10;
        }
        
        // Check if n is divisible by the combined total
        return n % (digitSum + digitProduct) == 0;
    }
};