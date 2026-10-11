/**
 * @param {number[]} nums
 * @return {number}
 */
var sumOfSquares = function(nums) {
    const n = nums.length;
    let totalSum = 0;

    // Loop through the array using 1-based indexing
    for (let i = 1; i <= n; i++) {
        // Check if the 1-based index 'i' divides the array length 'n'
        if (n % i === 0) {
            // Convert to 0-based index (i - 1) to get the element from nums
            totalSum += nums[i - 1] * nums[i - 1];
        }
    }

    return totalSum;
};
