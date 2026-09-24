/**
 * @param {number[]} nums
 * @return {number}
 */
var smallestIndex = function(nums) {
    // Helper function to calculate the sum of digits of a number
    const getDigitSum = (num) => {
        let sum = 0;
        while (num > 0) {
            sum += num % 10;
            num = Math.floor(num / 10);
        }
        return sum;
    };

    // Iterate through the array from the first element to the last
    for (let i = 0; i < nums.length; i++) {
        // Special case handling for 0 since the while loop requires num > 0
        let digitSum = nums[i] === 0 ? 0 : getDigitSum(nums[i]);
        
        // Return the first index that matches the condition
        if (digitSum === i) {
            return i;
        }
    }

    // Return -1 if no such index is found
    return -1;
};
