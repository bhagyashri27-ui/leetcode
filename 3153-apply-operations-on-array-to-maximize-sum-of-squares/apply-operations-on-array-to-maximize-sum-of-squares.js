/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var maxSum = function(nums, k) {
    const MOD = 1000000007n;
    const bitCount = new Array(31).fill(0);
    
    // Count the frequency of each bit across all numbers
    for (const num of nums) {
        for (let i = 0; i < 31; i++) {
            if ((num & (1 << i)) !== 0) {
                bitCount[i]++;
            }
        }
    }
    
    let totalSumOfSquares = 0n;
    
    // Form the k largest numbers possible
    for (let i = 0; i < k; i++) {
        let currentNum = 0n;
        for (let j = 0; j < 31; j++) {
            if (bitCount[j] > 0) {
                currentNum |= (1n << BigInt(j));
                bitCount[j]--; // Consume the bit
            }
        }
        // Add the square of the formed number to the total sum
        totalSumOfSquares = (totalSumOfSquares + currentNum * currentNum) % MOD;
    }
    
    return Number(totalSumOfSquares);
};
